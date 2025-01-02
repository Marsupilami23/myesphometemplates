#pragma once

#include <ArduinoJson.h>
#include <HTTPClient.h>

void fetchAndParseBurnData() {
  WiFiClient client; //Create a WiFiClient instance
  HTTPClient http;

  ESP_LOGI("burn_category", "Starting HTTP request...");
  
  //Use the correct begin() method for LibreTiny's HTTPClient
  http.begin(client, "https://sonomatech-production.s3.amazonaws.com/sacramento/airquality_org/cbyb-widget/burncheckForecast.txt");
  http.useHTTP10(true);
  
  ESP_LOGI("burn_category", "Sending HTTP GET request...");
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    ESP_LOGI("burn_category", "HTTP GET request successful.");
  
    int len = http.getSize();
    ESP_LOGI("burn_category", "Content length: %d bytes", len);
  
    String payload;
    WiFiClient *stream = http.getStreamPtr();
  
    // Read the data manually.
    while (stream->available()) {
      payload += (char)stream->read();
    }
  
    ESP_LOGI("burn_category", "Raw response: %s", payload.c_str());
  
    //Remote "burncheckForecastCallback(" and ")" from the response
    payload.remove(0, strlen("burncheckForecastCallback("));
    payload.remove(payload.length() - 1);
    ESP_LOGI("burn_category", "Cleaned response: %s", payload.c_str());
  
    // Adjust JSON doc size based on payload size or use a larger buffer.
    DynamicJsonDocument doc(len + 512); // Add a buffer for extra charactors or use a fixed larger size if needed
    DeserializationError error = deserializeJson(doc, payload);
  
    if (!error) {
      ESP_LOGI("burn_category", "JSON parsing successful.");
  
      int burn_cat = doc["burn_forecast"]["today"]["category"].as<int>();
      ESP_LOGI("burn_category", "Burn category: %d", burn_cat);
      id(burn_category) = burn_cat; // Update the global variable
  
      // Now that burn_category is updated, you need to trigger the update of your text sensor and sensor
      id(burn_status).publish_state(id(burn_status).state);
      id(burn_status_sensor).publish_state(id(burn_status_sensor).state);
    } else {
      ESP_LOGE("burn_category", "JSON deserialization failed: %s", error.c_str());
    }
  } else {
    ESP_LOGE("burn_category", "[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
  }
  http.end();
  ESP_LOGI("burn_category", "HTTP connection closed.");
}
