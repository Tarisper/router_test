#include "cfg.hpp"

#include <fmt/format.h>

#include <fstream>

using namespace std;
using nlohmann::json;
namespace fs = std::filesystem;

namespace vmx {

void to_json(json& j, const Config::Router::File& f) {
  j = json{{"r_path", f.r_path}, {"w_path", f.w_path}};
}

void from_json(const json& j, Config::Router::File& f) {
  j.at("r_path").get_to(f.r_path);
  j.at("w_path").get_to(f.w_path);
}

void to_json(json& j, const Config::Router::Postgres& p) {
  j = json{{"host", p.host},
           {"port", p.port},
           {"user", p.user},
           {"password", p.password},
           {"dbname", p.dbname}};
}

void from_json(const json& j, Config::Router::Postgres& p) {
  j.at("host").get_to(p.host);
  j.at("port").get_to(p.port);
  j.at("user").get_to(p.user);
  j.at("password").get_to(p.password);
  j.at("dbname").get_to(p.dbname);
}

void to_json(json& j, const Config::Router::Webapi& w) {
  j = json{{"host", w.host},
           {"port", w.port},
           {"address", w.address},
           {"timeout_ms", w.timeout_ms},
           {"ssl_verify_file", w.ssl_verify_file}};
  }

void from_json(const json& j, Config::Router::Webapi& w) {
  j.at("host").get_to(w.host);
  j.at("port").get_to(w.port);
  j.at("address").get_to(w.address);
  j.at("timeout_ms").get_to(w.timeout_ms);
  j.at("ssl_verify_file").get_to(w.ssl_verify_file);
}

void to_json(json& j, const Config::Router::Tcpsocket_client& t) {
  j = json{{"host", t.host},
           {"port", t.port},
           {"asynchronous", t.asynchronous}};
  }

void from_json(const json& j, Config::Router::Tcpsocket_client& t) {
  j.at("host").get_to(t.host);
  j.at("port").get_to(t.port);
  j.at("asynchronous").get_to(t.asynchronous);
}

void to_json(json& j, const Config::Router& r) {
  j = json{{"backend_types", r.backend_types},
           {"backend", r.backend},
           {"file", r.file},
           {"postgres", r.postgres},
           {"webapi", r.webapi},
           {"tcpsocket_client", r.tcpsocket_client}};
}

void from_json(const json& j, Config::Router& r) {
  j.at("backend_types").get_to(r.backend_types);
  j.at("backend").get_to(r.backend);
  j.at("file").get_to(r.file);
  j.at("postgres").get_to(r.postgres);
  j.at("webapi").get_to(r.webapi);
  j.at("tcpsocket_client").get_to(r.tcpsocket_client);
}

void to_json(json& j, const Config::Log& l) {
  j = json{{"basename", l.basename},
           {"level_enum", l.level_enum},
           {"level", l.level},
           {"path", l.path}};
}

void from_json(const json& j, Config::Log& l) {
  j.at("basename").get_to(l.basename);
  j.at("level_enum").get_to(l.level_enum);
  j.at("level").get_to(l.level);
  j.at("path").get_to(l.path);
}

void to_json(json& j, const Config& c) {
  j = json{{"router", c.router}, {"log", c.log}};
}

void from_json(const json& j, Config& c) {
  j.at("router").get_to(c.router);
  j.at("log").get_to(c.log);
}

bool ParseCfg(const string& content, Config& cfg) {
  if (content.empty()) return false;

  try {
    json::parse(content).get_to(cfg);
  } catch (const json::exception& e) {
    fmt::print("{}\n", e.what());
    return false;
  }

  return true;
}

bool ParseCfg(const fs::path& file, Config& cfg) {
  if (!fs::exists(file)) return false;

  ifstream stream(file);
  if (!stream) return false;
  string content((istreambuf_iterator<char>(stream)),
                 istreambuf_iterator<char>());
  stream.close();

  return ParseCfg(content, cfg);
}

}  // namespace vmx
