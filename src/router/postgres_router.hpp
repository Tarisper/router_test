#pragma once

#ifdef WITH_SROUTER_POSTGRES

#include <string>
#include <utilities/cfg.hpp>

#include "router_engine.hpp"

namespace vmx {

class PostgreRouter final : public RouterEngine {
 public:
  explicit PostgreRouter(const Config& cfg);
  ~PostgreRouter() override;

  bool initialize() override;
  void* set(const char* str, void* array, size_t& count, int& code,
            int apiId = 0) override;
  void* get(const char* str, void* array, size_t& count, int& code,
            int apiId = 0) override;
  bool deinitialize() override;

 private:
  void* query(const char* str, size_t& count);

  const Config kCfg;
  const std::string kConnectionString;
};

}  // namespace vmx

#endif
