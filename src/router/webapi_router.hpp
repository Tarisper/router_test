#pragma once

#ifdef WITH_SROUTER_WEBAPI

#include <memory>
#include <utilities/cfg.hpp>

#include "router_engine.hpp"

namespace vmx {

class WebapiRouter final : public RouterEngine {
 public:
  explicit WebapiRouter(const Config& cfg);
  ~WebapiRouter() override = default;

  bool initialize() override;
  void* set(const char* str, void* array, size_t& count, int& code,
            int apiId = 0) override;
  void* get(const char* str, void* array, size_t& count, int& code,
            int apiId = 0) override;
  bool deinitialize() override;

 private:
  const Config kCfg;
  bool sslClient = false;
};

}  // namespace vmx

#endif
