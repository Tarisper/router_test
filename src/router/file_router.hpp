#pragma once

#ifdef WITH_SROUTER_FILE

#include <utilities/cfg.hpp>

#include "router_engine.hpp"

namespace vmx {

class FileRouter final : public RouterEngine {
 public:
  explicit FileRouter(const Config& cfg);
  ~FileRouter() override = default;

  bool initialize() override;
  void* set(const char* str, void* array, size_t& count, int& code,
            int apiId = 0) override;
  void* get(const char* str, void* array, size_t& count, int& code,
            int apiId = 0) override;
  bool deinitialize() override;

 private:
  void* write(const char* str, size_t& count);
  void* read(const char* str, size_t& count);

  const Config kCfg;
};

}  // namespace vmx

#endif
