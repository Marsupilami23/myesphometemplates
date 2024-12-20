#ifndef BURN_FORECAST_H
#define BURN_FORECAST_H

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/http_request/http_request.h"

namespace esphome {
namespace burn_forecast {

class BurnForecast : public Component, public sensor::Sensor {
 public:
  void set_url(const std::string &url) { this->url_ = url; }

  void setup() override;
  void update() override;

 protected:
  std::string url_;
  http_request::HTTPClient *http_client_{nullptr};
};

}  // namespace burn_forecast
}  // namespace esphome

#endif
