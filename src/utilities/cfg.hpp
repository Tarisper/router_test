#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace vmx {

struct Config {
  struct Router {
    std::vector<std::string> backend_types;
    std::string backend;

    struct File {
      std::string w_path;
      std::string r_path;
    } file;

    struct Postgres {
      std::string host;
      int port;
      std::string user;
      std::string password;
      std::string dbname;
    } postgres;

    struct Webapi {
      std::string host;
      int port;
      std::vector<std::string> address;
      int timeout_ms;
      std::string ssl_verify_file;
    } webapi;

    struct Tcpsocket_client {
      std::string host;
      int port;
      bool asynchronous;
    } tcpsocket_client;
  } router;

  struct Log {
    std::string basename;
    std::vector<std::string> level_enum;
    std::string level;
    std::string path;
  } log;
};

void to_json(nlohmann::json& j, const Config::Router::File& f);
void from_json(const nlohmann::json& j, Config::Router::File& f);

void to_json(nlohmann::json& j, const Config::Router::Postgres& p);
void from_json(const nlohmann::json& j, Config::Router::Postgres& p);

void to_json(nlohmann::json& j, const Config::Router::Webapi& w);
void from_json(const nlohmann::json& j, Config::Router::Webapi& w);

void to_json(nlohmann::json& j, const Config::Router::Tcpsocket_client& t);
void from_json(const nlohmann::json& j, Config::Router::Tcpsocket_client& t);

void to_json(nlohmann::json& j, const Config::Router& r);
void from_json(const nlohmann::json& j, Config::Router& r);

void to_json(nlohmann::json& j, const Config::Log& l);
void from_json(const nlohmann::json& j, Config::Log& l);

void to_json(nlohmann::json& j, const Config& c);
void from_json(const nlohmann::json& j, Config& c);

bool ParseCfg(const std::string& content, Config& cfg);
bool ParseCfg(const std::filesystem::path& file, Config& cfg);

}  // namespace vmx
