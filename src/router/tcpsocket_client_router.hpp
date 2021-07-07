#pragma once

#ifdef WITH_SROUTER_TCPSOCKET_CLIENT

#include <memory>
#include <utilities/cfg.hpp>
#include <server/asio/tcp_client.h>

#include "router_engine.hpp"

namespace vmx {

class TcpSocketRouter final : public RouterEngine {
 public:
  explicit TcpSocketRouter(const Config& cfg);
  ~TcpSocketRouter() override = default;

  bool initialize() override;
  void* set(const char* str, void* array, size_t& count, int& code,
            int apiId = 0) override;
  void* get(const char* str, void* array, size_t& count, int& code,
            int apiId = 0) override;
  bool deinitialize() override;

 private:
  const Config kCfg;
  bool sslClient = false;
  std::shared_ptr<CppServer::Asio::TCPClient> client;
  std::shared_ptr<CppServer::Asio::Service> service;
};

}  // namespace vmx

#endif
