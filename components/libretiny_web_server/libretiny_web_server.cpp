#include "my_web_server.h"
#include "esphome/core/log.h"

namespace esphome {
namespace libretiny_web_server {

static const char *const TAG = "libretiny_web_server";

void LibreTinyWebServer::setup() {
  ESP_LOGCONFIG(TAG, "Setting up LibreTiny WebServer...");

  server_ = new WebServer(port_);

  // Set up a handler for the root path
  server_->on("/", HTTP_GET, [this]() {
    handleRoot();
  });

  // Set up a handler for the /data path
  server_->on("/data", HTTP_GET, [this]() {
    handleData();
  });

  // Set up a handler for the /status path
  server_->on(
      "/status", HTTP_GET, [this]() { handleStatus(); });

  server_->begin();
  lt_log(LT_LOG_INFO, "WebServer started on port %d", port_);
}

void LibreTinyWebServer::loop() {
  if (server_) {
    server_->handleClient();
  }
}

void LibreTinyWebServer::handleRoot() {
  ESP_LOGI(TAG, "Serving root");
  std::string response = "<h1>Hello from LibreTiny Web Server on ESPHome!</h1>";
  server_->send(200, "text/html", response.c_str());
}

void LibreTinyWebServer::on(const char* path, HTTPMethod method, WebServer::THandlerFunction handler) {
    if (server_) {
        server_->on(path, method, handler);
    }
}

void LibreTinyWebServer::handleData() {
  lt_log(LT_LOG_INFO, "Serving data");
  String data = "{\"status\":\"ok\"}";
  server_->send(200, "application/json", data.c_str());
}

void LibreTinyWebServer::handleStatus() {
  lt_log(LT_LOG_INFO, "Serving status");
  String status = "{\"status\":\"ok\"}";
  server_->send(200, "application/json", status.c_str());
}

} // namespace libretiny_web_server
} // namespace esphome
