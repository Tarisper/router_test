#ifdef WITH_SROUTER_FILE

#include "file_router.hpp"

#include <filesystem>
#include <fstream>
#include <srouter/types.hpp>

using namespace std;

namespace vmx {

FileRouter::FileRouter(const Config& cfg) : RouterEngine(cfg), kCfg(cfg) {}

bool FileRouter::initialize() { return true; }

void* FileRouter::write(const char* str, size_t& count) {
  if (std::filesystem::exists(str)) {
    fstream f(kCfg.router.file.w_path, ios::out | ios::app);
    if (!f.is_open()) return nullptr;

    vector<string> fileData;
    f << str << "\n";
    f.close();

    count = 0;
  }
  return nullptr;
}

void* FileRouter::read(const char* str, size_t& count) {
  if (std::filesystem::exists(str)) {
    ifstream f(kCfg.router.file.r_path, ios::in);
    if (!f.is_open()) return nullptr;

    string line;
    vector<string> fileData;
    while (getline(f, line)) fileData.push_back(line);
    f.close();

    // Build result.
    count = fileData.size();
    if (count == 0) return nullptr;

    Record* result = new Record[count];
    for (size_t i = 0; i < count; i++) {
      const size_t length = fileData[i].size();
      result[i].length = length;
      result[i].string = new char[length];
      strcpy(result[i].string, fileData[i].c_str());
    }

    return static_cast<void*>(result);
  }
  return nullptr;
}

void* FileRouter::set(const char* str, void* array, size_t& count, int& code,
                      int apiId) {
  return *static_cast<void**>(array) = write(str, count);
}

void* FileRouter::get(const char* str, void* array, size_t& count, int& code,
                      int apiId) {
  return *static_cast<void**>(array) = read(str, count);
}

bool FileRouter::deinitialize() { return true; }

}  // namespace vmx

#endif
