#if !defined(EXPLORE_BASE_CALLBACK_H)
#define EXPLORE_BASE_CALLBACK_H

#include <functional>
#include <memory>

namespace explore {
namespace base {

class TcpConnection;    // forward declaration
class Buffer;           // forward declaration

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

/// @code Object-Based (for async service)
using OnConnectCallback_t   = std::function<bool(const TcpConnectionPtr& conn)>;
using OnSendCallback_t      = std::function<bool(const TcpConnectionPtr& conn)>;
using OnMessageCallback_t   = std::function<bool(const TcpConnectionPtr& conn, Buffer* buf)>;
using OnCloseCallback_t     = std::function<bool(const TcpConnectionPtr& conn)>;
using OnErrorCallback_t     = std::function<void(const TcpConnectionPtr& conn, const std::string&)>;
/// @endcond

} // namespace base 
} // namespace explore 

#endif // EXPLORE_BASE_CALLBACK_H
