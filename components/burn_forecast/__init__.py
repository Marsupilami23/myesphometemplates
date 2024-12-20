import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

DEPENDENCIES = ["http_request"]
AUTO_LOAD = ["json"]
CODEOWNERS = ["Marsupilami23"]  # Replace with your GitHub username

CONF_URL = "url"

burn_forecast_ns = cg.esphome_ns.namespace("burn_forecast")
BurnForecast = burn_forecast_ns.class_("BurnForecast", sensor.Sensor, cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(BurnForecast),
    cv.Required(CONF_URL): cv.url,
}).extend(cv.COMPONENT_SCHEMA).extend(sensor.SENSOR_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.add(var.set_url(config[CONF_URL]))
    await sensor.register_sensor(var, config)
