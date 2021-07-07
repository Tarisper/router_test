#include "router_engine.hpp"

#include "file_router.hpp"
#include "postgres_router.hpp"
#include "webapi_router.hpp"
#include "tcpsocket_client_router.hpp"

namespace vmx {

RouterEngine *RouterEngine::create(const Config &cfg) {
  if (find(kRouterBackend.begin(), kRouterBackend.end(), cfg.router.backend) ==
      kRouterBackend.end())
    return nullptr;

  if (cfg.router.backend == kRouterBackend.at(RouterBackend::FILE))
#ifndef WITH_SROUTER_FILE
    return nullptr;
#else
    return new FileRouter(cfg);
#endif
  else if (cfg.router.backend == kRouterBackend.at(RouterBackend::POSTGRES))
#ifndef WITH_SROUTER_POSTGRES
    return nullptr;
#else
    return new PostgreRouter(cfg);
#endif
  else if (cfg.router.backend == kRouterBackend.at(RouterBackend::WEBAPI))
#ifndef WITH_SROUTER_WEBAPI
    return nullptr;
#else
    return new WebapiRouter(cfg);
#endif
  else if (cfg.router.backend ==
           kRouterBackend.at(RouterBackend::TCPSOCKETCLIENT))
#ifndef WITH_SROUTER_TCPSOCKET_CLIENT
    return nullptr;
#else
    return new TcpSocketRouter(cfg);
#endif
  else
    return nullptr;
}

RouterEngine::RouterEngine(const Config &cfg) : kCfg(cfg) {}

}  // namespace vmx
