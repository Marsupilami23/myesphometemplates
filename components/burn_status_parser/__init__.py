import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    STATE_CLASS_MEASUREMENT,
    UNIT_NONE,
    ICON_ALERT_OCTAGON,
)

DEPENDENCIES = ["http_request"]
AUTO_LOAD = ["json"]
CODEOWNERS = ["Marsupilami23"]  # Replace with your GitHub username

burn_forecast_ns = cg.esphome_ns.namespace("burn_forecast")
BurnForecast = burn_forecast_ns.class_("BurnForecast", cg.Component, sensor.Sensor)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(BurnForecast),
    cv.Required("url"): cv.url,
}).extend(cv.COMPONENT_SCHEMA).extend(sensor.SENSOR_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.add(var.set_url(config["url"]))
    await sensor.register_sensor(var, config)
    cg.add_global(burn_forecast_ns.using)
