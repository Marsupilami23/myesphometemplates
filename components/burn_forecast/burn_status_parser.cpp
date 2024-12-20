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
    size_t start = body.find('{');
    size_t end = body.rfind('}');
    if (start == std::string::npos || end == std::string::npos) {
      ESP_LOGW("burn_forecast", "Invalid JSON response format");
      this->publish_state(NAN);
      return;
    }
    std::string json_string = body.substr(start, end - start + 1);

    StaticJsonDocument doc;
    DeserializationError error = deserializeJson(doc, json_string);
    if (error) {
      ESP_LOGW("burn_forecast", "JSON parsing failed: %s", error.c_str());
      this->publish_state(NAN);
      return;
    }

    if (doc.containsKey("burn_forecast") &&
        doc["burn_forecast"].containsKey("today") &&
        doc["burn_forecast"]["today"].containsKey("category")) {
      int category = doc["burn_forecast"]["today"]["category"].as<int>();
      this->publish_state(category);
      return;
    }

    ESP_LOGW("burn_forecast", "Could not find 'category' in JSON");
    this->publish_state(NAN);
  });
}

}  // namespace burn_forecast
}  // namespace esphome
