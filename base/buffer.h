/**
 * @note This is a public header file, it must only include public header files.
*/

#if !defined(EXPLORE_BASE_BUFFER_HPP)
#define EXPLORE_BASE_BUFFER_HPP

#include <boost/endian/conversion.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <type_traits>

namespace explore {
namespace base {
    using namespace boost;
class Buffer {
public:
    static const std::size_t kCheapPrepend = 8;
    static const std::size_t kInitialSize = 1024/2;

    Buffer()
        : buf_(kInitialSize, '\0')
        , readIndex_(kCheapPrepend)
        , writeIndex_(kCheapPrepend)
    {

    }

    size_t ReadableBytes() const
    { return writeIndex_ - readIndex_; }

    size_t WriteableBytes() const
    { return buf_.size() - writeIndex_; }
    
    size_t PrependableBytes() const
    { return readIndex_ - 0; }

    /// @brief return first writeable place
    const char* BeginWrite() const
    { return begin() + writeIndex_; }

    /// @brief return first readable place
    const char* peek() const
    { return begin() + readIndex_; }

    void swap(Buffer& another) {
        buf_.swap(another.buf_);
        std::swap(readIndex_, another.readIndex_);
        std::swap(writeIndex_, another.writeIndex_);
    }

    /// @brief search position of "\r\n"
    /// @return if success return a pointer to position of "\r", otherwise return NULL
    const char* FindCrlf() const {
        const char* pos = std::search(peek(), peek()+writeIndex_, kCrlf, kCrlf+2);
        return pos == BeginWrite() ? nullptr : pos;
    }

    const char* FindCrlf(const char* const start) const {
        assert(peek() <= start && start <= BeginWrite());
        const char* pos = std::search(start, peek()+writeIndex_, kCrlf, kCrlf+2);
        return pos == BeginWrite() ? nullptr : pos;
    }

    void RetrieveAll() {
        readIndex_  = kCheapPrepend;
        writeIndex_ = kCheapPrepend;
    }

    void retrieve(const std::size_t len) {
        assert(len <= ReadableBytes());
        if (len < ReadableBytes()) {
            readIndex_ += len;
        } else {    // case: len == ReadableBytes() 
            RetrieveAll();
        }
    }

    std::string RetrieveAsString(const std::size_t len) {
        assert(len <= ReadableBytes());
        std::string res(peek(), len);
        retrieve(len);
        return res;
    }

    std::string RetrieveAllAsString() {
        return RetrieveAsString(ReadableBytes());
    }

    void RetrieveUntil(const char* limit) {
        assert(peek() <= limit && limit <= BeginWrite());
        retrieve(limit - peek());
    }

    void RetrieveInt8()     { retrieve(sizeof(int8_t)); }
    void RetrieveInt16()    { retrieve(sizeof(int16_t)); }
    void RetrieveInt32()    { retrieve(sizeof(int32_t)); }
    void RetrieveInt64()    { retrieve(sizeof(int64_t)); }

    /// @brief ensure writeable space, If not, the function will expand store space
    void EnsureWriteableBytes(const std::size_t target_size) {
        if (target_size > WriteableBytes()) {
            MakeSpace(target_size);
        }
        assert(target_size <= WriteableBytes());
    }

    void append(const char* data, const std::size_t len) {
        EnsureWriteableBytes(len);
        std::copy(data, data+len, BeginWrite());
        writeIndex_ += len;
    }

    void append(const void* const data, const size_t len) {
        append(static_cast<const char*>(data), len);
    }

    /// @brief append a integer using big-endian
    template<typename Integer_t>
    typename std::enable_if<std::is_integral<Integer_t>::value, void>::type AppendInt(Integer_t x) {
        boost::endian::native_to_big_inplace(x);
        append(&x, sizeof x);
    }

    /// @brief peek a integer but not move readable index
    template<typename Integer_t>
    typename std::enable_if_t<std::is_integral<Integer_t>::value, Integer_t> PeekInt() const {
        assert(ReadableBytes() >= sizeof(Integer_t));
        Integer_t BigEndianInteger = 0;
        std::memcpy(&BigEndianInteger, peek(), sizeof(Integer_t));
        return boost::endian::big_to_native(BigEndianInteger);
    }
    
    /// @brief read a integer and move readable index
    template<typename Integer_t>
    typename std::enable_if_t<std::is_integral<Integer_t>::value, Integer_t> ReadInt() {
        assert(ReadableBytes() >= sizeof(Integer_t));
        Integer_t res = PeekInt<Integer_t>();
        readIndex_ += sizeof(Integer_t);
        return res;
    }

    void prepend(const void* data, const std::size_t len) {
        assert(PrependableBytes() >= len);
        readIndex_ -= len;
        const char* tmp = static_cast<const char*>(data);
        /// @note in std::copy() Result may not be contained within [first,last); if is true the copy_backward function should be used instead.
        std::copy(tmp, tmp + len, begin() + readIndex_);
    }

    /// @brief add a big-endian integer to prepend area
    template<typename Integer_t>
    std::enable_if_t<std::is_integral<Integer_t>::value, void> PrependInt(Integer_t x) {
        boost::endian::native_to_big_inplace(x);
        prepend(&x, sizeof x);
    }

    /// @brief shrink to the fit size
    void    shrink()                    { buf_.shrink_to_fit(); }

    size_t  InternalCapacity() const   { return buf_.capacity(); }

    /// @brief synchronous read some data from boost::tcp::socket
    std::size_t SyncRecv(boost::asio::ip::tcp::socket& sock, system::error_code& ec);

    /// @brief asynchronous read some data from boost::tcp::socket
    void AsyncRecv(boost::asio::ip::tcp::socket& sock, const std::function<void(const system::error_code& ec, std::size_t bytes_transferred)>& cb);

private:    /// These are internal use
    const char* begin() const
    { return &(*buf_.begin()); }

    char* begin()
    { return &(*buf_.begin()); }

    /// @brief return first writeable place
    char* BeginWrite()
    { return begin() + writeIndex_; }

    /// @brief allocate store space
    void MakeSpace(const std::size_t target_size);  

    static const char   kCrlf[];

private:
    std::vector<char>   buf_;
    std::size_t         readIndex_;     // initial index of readable position
    std::size_t         writeIndex_;    // initial index of begin writeable position
};

} // namespace base 
    using Buffer = base::Buffer;        // define friendly alias
} // namespace explore 

#endif // EXPLORE_BASE_BUFFER_HPP
