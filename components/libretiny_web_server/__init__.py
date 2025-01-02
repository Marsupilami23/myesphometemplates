import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import web_server_base
from esphome.const import CONF_ID, CONF_PORT

AUTO_LOAD = ["web_server_base"]
DEPENDENCIES = []

CONF_LIBRETINY_WEB_SERVER_ID = "libretiny_web_server_id"
CONF_LIBRETINY_WEB_SERVER_PORT = "port"

libretiny_web_server_ns = cg.esphome_ns.namespace("libretiny_web_server")
LibreTinyWebServer = libretiny_web_server_ns.class_(
    "LibreTinyWebServer", cg.Component
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(LibreTinyWebServer),
        cv.Optional(
            CONF_LIBRETINY_WEB_SERVER_PORT, default=80
        ): web_server_base.port,
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_port(config[CONF_LIBRETINY_WEB_SERVER_PORT]))

    cg.add_library("ArduinoJson", None)

    cg.add_header("my_web_server.h")
