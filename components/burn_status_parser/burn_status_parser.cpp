#include "burn_status_parser.h"
#include <ArduinoJson.h>
#inlcude <ESPLogs.h>

std::string extract_json_string(const std::string& body) {
  size_t start = body.find('{');
  size_t end = body.rfind('}');
  if (start == std::string::npos || end == std::string::npos) {
    ESP_LOGW("burn_status", "Invalid JSON response format");
    return "";
  }
  return body.substr(start, end - start + 1);
}

bool parse_json(const std::string&, int& burn_status) {
  StaticJsonDocument doc;
  DeserializationError error = deserializeJson(doc, json_string);
  if (error) {
    ESP_LOGW("burn_status", "deserializeJson() failed: %s", error.c_str());
    return false;
  }

  if (doc.containsKey("burn_forecast") &&
      doc["burn_forecast"].containsKey("today") &&
      doc["burn_forecast"]["today"].containsKey("category")) {
    burn_status = doc["burn_forecast"]["today"]["category"].as<int>();
    ESP_LOGD("burn_status", "Category: %d, burn_status);
    return true;
  }

ESP_LOGD("burn_status", "Could not find 'category' in JSON");
serilizeJson(doc,Serial);
Serial.println("");
return false;
}
