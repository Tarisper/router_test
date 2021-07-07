#include "srouter/srouter.hpp"

#include <filesystem>
#include <memory>
#include <string>

#include "instance_manager.hpp"

using namespace std;
namespace fs = std::filesystem;

namespace vmx {

static unique_ptr<InstanceManager> gInstanceManager = nullptr;

bool SRouter_Initialize(const char* cfg, const char* log) {
  gInstanceManager = make_unique<InstanceManager>(fs::path(cfg), fs::path(log));

  return gInstanceManager->isInitialized();
}

void* SRouter_Create(unsigned int id, void* params) {
  return gInstanceManager->create(id, params);
}

SROUTER_SET SRouter_Set(void* instance, const char* str, void* array,
                        size_t& count, int& code, int apiId) {
  count = 0;
  return gInstanceManager->set(instance, str, array, count, code, apiId);
}

SROUTER_GET SRouter_Get(void* instance, const char* str, void* array,
                        size_t& count, int& code, int apiId) {
  count = 0;
  return gInstanceManager->get(instance, str, array, count, code, apiId);
}

bool SRouter_ReadConfig(void* instance) {
  return gInstanceManager->readCfg(instance);
}

bool SRouter_Delete(void* instance) {
  return gInstanceManager->release(instance);
}

bool SRouter_Deinitialize() {
  gInstanceManager.reset();
  return true;
}

}  // namespace vmx
