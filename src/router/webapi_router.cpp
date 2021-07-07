#ifdef WITH_SROUTER_WEBAPI

#include "webapi_router.hpp"

#include <httplib/httplib.h>

#include <srouter/types.hpp>

using namespace std;

httplib::Client* client;

namespace vmx {

WebapiRouter::WebapiRouter(const Config& cfg) : RouterEngine(cfg), kCfg(cfg) {}

bool WebapiRouter::initialize() {
  client =
      new httplib::Client(kCfg.router.webapi.host, kCfg.router.webapi.port);

  return true;
}

void* WebapiRouter::set(const char* str, void* array, size_t& count, int& code,
                        int apiId) {
  if (auto response = client->Post(kCfg.router.webapi.address[apiId].c_str(),
                                   str, "application/json")) {
    code = response->status;
    //! if (response->status == 200) {
    if (true) {
      // We do something, if necessary.
      count = 1;
      Record* result = new Record[count];
      const size_t length = response->body.size() + 1;
      result[0].length = length;
      result[0].string = new char[length];
      strcpy(result[0].string, response->body.c_str());
      return static_cast<void*>(result);
    }
    //! if (response->status != 200) {
    //! // We do something, if necessary.
    //! if (!response->body.empty()) {
    //! // std::cout << "\n" << response->body << std::endl;
    //! response->body.clear();
    //! }
    //! }
  }
  return nullptr;
}

void* WebapiRouter::get(const char* str, void* array, size_t& count, int& code,
                        int apiId) {
  if (auto response = client->Get(kCfg.router.webapi.address[apiId].c_str())) {
    code = response->status;
    if (response->status == 200) {
      count = 1;
      Record* result = new Record[count];
      if (!response->body.empty()) {
        const size_t length = response->body.size();
        result[0].length = length;
        result[0].string = new char[length];
        strcpy(result[0].string, response->body.c_str());
      }
      return static_cast<void*>(result);
    }
    if (response->status != 200) return nullptr;
  }
  return nullptr;
}

bool WebapiRouter::deinitialize() {
  if (client) client->stop();
  if (client) delete client;
  return true;
}

}  // namespace vmx

#endif
