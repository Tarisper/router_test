#ifdef WITH_SROUTER_POSTGRES

#include "postgres_router.hpp"

#include <fmt/format.h>

#include <pqxx/pqxx>
#include <srouter/types.hpp>

using namespace std;

pqxx::connection* Conn;

namespace vmx {

PostgreRouter::PostgreRouter(const Config& cfg)
    : RouterEngine(cfg),
      kCfg(cfg),
      kConnectionString(
          fmt::format("host={} port={} user={} password={} dbname={}",
                      cfg.router.postgres.host, cfg.router.postgres.port,
                      cfg.router.postgres.user, cfg.router.postgres.password,
                      cfg.router.postgres.dbname)) {}

PostgreRouter::~PostgreRouter() {
  if (Conn) deinitialize();
}

bool PostgreRouter::initialize() {
  if (Conn) deinitialize();
  Conn = new pqxx::connection(kConnectionString);
  return true;
}

void* PostgreRouter::query(const char* str, size_t& count) {
  // pqxx::connection C(kConnectionString);
  pqxx::work W(*Conn);
  pqxx::result R = W.exec(str);
  W.commit();

  vector<string> recordset;
  if (!R.empty()) {
    for (pqxx::result_size_type r = 0; r < R.size(); r++) {
      string record;
      for (pqxx::row_size_type c = 0; c < R.columns(); c++) {
        record.append(R[r][c].c_str());
        record.append(";");
      }
      recordset.push_back(record);
    }
  }

  R.clear();

  // Build result.
  count = recordset.size();
  if (count == 0) return nullptr;

  Record* result = new Record[count];
  for (size_t i = 0; i < count; i++) {
    const size_t length = recordset[i].size();
    result[i].length = length;
    result[i].string = new char[length];
    strcpy(result[i].string, recordset[i].c_str());
  }

  return static_cast<void*>(result);
}

void* PostgreRouter::set(const char* str, void* array, size_t& count, int& code,
                         int apiId) {
  return *static_cast<void**>(array) = query(str, count);
}

void* PostgreRouter::get(const char* str, void* array, size_t& count, int& code,
                         int apiId) {
  return *static_cast<void**>(array) = query(str, count);
}

bool PostgreRouter::deinitialize() {
  if (Conn) {
    Conn->close();
    delete Conn;
  }
  return true;
}

}  // namespace vmx

#endif
