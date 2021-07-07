#pragma once

#include <filesystem>
#include <memory>
#include <router/router_engine.hpp>
#include <scvision/utilities/spdlog_manager.hpp>
#include <srouter/types.hpp>
#include <vector>

namespace vmx {

class InstanceManager {
 public:
  InstanceManager(const std::filesystem::path& cfg,
                  const std::filesystem::path& log);
  ~InstanceManager();

  bool isInitialized() const noexcept;

  void* create(unsigned int cfgId, const void* params = nullptr);
  SROUTER_GET get(void* instance, const char* str, void* array, size_t& count,
                  int& code, int apiId = 0);
  SROUTER_SET set(void* instance, const char* str, void* array, size_t& count,
                  int& code, int apiId = 0);
  bool readCfg(const void* instance);
  bool release(const void* instance);

 private:
  const std::filesystem::path kCfgDir;
  const std::filesystem::path kLogDir;
  const char* kCfgPattern = "srouter_{}.json";
  bool mIsInitialized = false;

  std::shared_ptr<spdlog::logger> mLog;

  std::vector<RouterEngine*> mInstances;
};

}  // namespace vmx
