#pragma once

#include <array>
#include <cstddef>
#include <utilities/cfg.hpp>

namespace vmx {

class RouterEngine {
 public:
  enum RouterBackend : int { FILE, POSTGRES, WEBAPI, TCPSOCKETCLIENT };
  static constexpr std::array<const char*, 4> kRouterBackend{
      "FILE", "POSTGRES", "WEBAPI", "TCPSOCKETCLIENT"};

  static RouterEngine* create(const Config& cfg);
  virtual ~RouterEngine() = default;

  virtual bool initialize() = 0;
  virtual void* set(const char* str, void* array, size_t& count, int& code,
                    int apiId = 0) = 0;
  virtual void* get(const char* str, void* array, size_t& count, int& code,
                    int apiId = 0) = 0;
  virtual bool deinitialize() = 0;

 protected:
  explicit RouterEngine(const Config& cfg);

 private:
  const Config kCfg;
};

}  // namespace vmx
