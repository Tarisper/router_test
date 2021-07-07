#include "instance_manager.hpp"

#include <fmt/format.h>

#include <utilities/cfg.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace vmx {

InstanceManager::InstanceManager(const fs::path& cfg, const fs::path& log)
    : kCfgDir(cfg), kLogDir(log) {
  mLog = SetupLogger(PROJECT_NAME);
  mLog->info("{} v{} loaded.", PROJECT_NAME, PROJECT_VERSION);

  if (!fs::exists(cfg) || !fs::is_directory(cfg)) {
    mLog->error("The configuration directory was not found \"{}\".",
                cfg.string());
    return;
  }

  mIsInitialized = true;
}

InstanceManager::~InstanceManager() {
  // Try release active pointers.
  for (auto it = mInstances.begin(); it != mInstances.end(); /*it++*/) {
    if (*it) {
      RouterEngine* ie = static_cast<RouterEngine*>(*it);
      ie->deinitialize();

      delete ie;
      ie = nullptr;

      it = mInstances.erase(it);
    } else
      ++it;
  }

  mIsInitialized = false;
}

bool InstanceManager::isInitialized() const noexcept { return mIsInitialized; }

void* InstanceManager::create(unsigned int id, const void* params) {
  fs::path config = kCfgDir;
  config.append(fmt::format(kCfgPattern, id));

  if (!fs::exists(config) || !fs::is_regular_file(config)) {
    mLog->error("The configuration file was not found \"{}\".",
                config.string());
    return nullptr;
  }

  Config cfg;
  if (!ParseCfg(config, cfg)) {
    mLog->error("Configuration parsing failed.");
    return nullptr;
  }

  mLog = SetupLogger(cfg.log.basename.c_str(), cfg.log.level.c_str(),
                     cfg.log.path.c_str());

  RouterEngine* ie = RouterEngine::create(cfg);
  if (!ie || !ie->initialize()) {
    mLog->error("Inference engine creating failed.");
    return nullptr;
  }

  mInstances.emplace_back(ie);
  return static_cast<void*>(ie);
}

SROUTER_GET InstanceManager::get(void* instance, const char* str, void* array,
                                 size_t& count, int& code, int apiId) {
  mLog->debug("str={}", str);
  if (!str) return SROUTER_GET::SROUTER_GET_INVALID;

  RouterEngine* ie = static_cast<RouterEngine*>(instance);
  if (!ie) return SROUTER_GET::SROUTER_GET_INVALID;

  *static_cast<void**>(array) = ie->get(str, array, count, code, apiId);

  if (!array && count == 0) return SROUTER_GET::SROUTER_GET_EMPTY;

  return SROUTER_GET::SROUTER_GET_EMPTY;
}

SROUTER_SET InstanceManager::set(void* instance, const char* str, void* array,
                                 size_t& count, int& code, int apiId) {
  mLog->debug("str={}", str);
  if (!instance) return SROUTER_SET::SROUTER_SET_INVALID;

  RouterEngine* ie = static_cast<RouterEngine*>(instance);
  if (!ie) return SROUTER_SET::SROUTER_SET_INVALID;
  *static_cast<void**>(array) = ie->set(str, array, count, code, apiId);
  if (!array && count == 0) return SROUTER_SET::SROUTER_SET_EMPTY;
  return SROUTER_SET::SROUTER_SET_EMPTY;
}

bool InstanceManager::readCfg(const void* instance) { return false; }

bool InstanceManager::release(const void* instance) {
  if (!instance) return false;

  const auto& it = find(mInstances.begin(), mInstances.end(), instance);
  if (it != mInstances.end()) {
    RouterEngine* ie = static_cast<RouterEngine*>(*it);
    ie->deinitialize();

    delete ie;
    ie = nullptr;

    mInstances.erase(it);
    return true;
  }

  return true;
}

}  // namespace vmx
