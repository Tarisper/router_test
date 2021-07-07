#ifdef WITH_SROUTER_TCPSOCKET_CLIENT

#include "tcpsocket_client_router.hpp"

#include <srouter/types.hpp>

using namespace std;

namespace vmx {

TcpSocketRouter::TcpSocketRouter(const Config& cfg)
    : RouterEngine(cfg), kCfg(cfg) {}

bool TcpSocketRouter::initialize() {
  if (!service) {
    // Create a new Asio service
    service = std::make_shared<CppServer::Asio::Service>();
    // Start the Asio service
    service->Start();
    // Create a new TCP chat client
    client = std::make_shared<CppServer::Asio::TCPClient>(
        service, kCfg.router.tcpsocket_client.host,
        kCfg.router.tcpsocket_client.port);
    return true;
  } else
    return false;
}

void* TcpSocketRouter::set(const char* str, void* array, size_t& count,
                           int& code, int apiId) {
  if (kCfg.router.tcpsocket_client.asynchronous) {
    client->ConnectAsync();
    client->SendAsync(str);
    client->DisconnectAsync();
  } else {
    client->Connect();
    client->Send(str);
    client->Disconnect();
  }
  return nullptr;
}

void* TcpSocketRouter::get(const char* str, void* array, size_t& count,
                           int& code, int apiId) {
  return nullptr;
}

bool TcpSocketRouter::deinitialize() {
  if (kCfg.router.tcpsocket_client.asynchronous && client->IsConnected())
    client->DisconnectAsync();
  else if (client->IsConnected())
    client->Disconnect();
  if (service) service->Stop();
  return true;
}

}  // namespace vmx

#endif
