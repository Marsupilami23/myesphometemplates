#include <string>
#include "burn_forecast.h"
#include "esphome/core/application.h"
#include <ArduinoJson.h>
#include <ESPLogs.h>

namespace esphome {
namespace burn_forecast {

void BurnForecast::setup() {
  this->http_client_ = new http_request::HTTPClient();
}

void BurnForecast::update() {
  this->http_client_->set_url(this->url_);
  this->http_client_->set_method("GET");
  this->http_client_->send([this](http_request::HTTPResponse *response) {
    if (response == nullptr || response->get_code() != 200) {
      ESP_LOGW("burn_forecast", "HTTP request failed");
      this->publish_state(NAN);
      return;
    }

    std::string body = response->get_body();
    ESP_LOGD("burn_forecast", "HTTP Response Body Length: %d", body.length()); // Log the body
    if (body.length() > 0 {
      ESP_LOGD("burn_forecast", "First char: %c", body[0]);
    }
    this->publish_state(0); // Publish a dummy value
});
