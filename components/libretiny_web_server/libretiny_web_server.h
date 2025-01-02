#pragma once

#include "esphome.h"
#include <WebServer.h>
#include <HTTP_Method.h>
#include <Uri.h>
#include <functional>
#include <memory>

namespace esphome {
namespace libretiny_web_server {

class LibreTinyWebServer : public Component {
 public:
  void setup() override;
  void loop() override;
  void set_port(uint16_t port) { port_ = port; }
  void on(const char* path, HTTPMethod method, WebServer::THandlerFunction handler);

 protected:
  uint16_t port_;
  WebServer *server_;
};

} // namespace libretiny_web_server
} // namespace esphome
