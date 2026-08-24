import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

knx_ns = cg.esphome_ns.namespace("knx")
KnxComponent = knx_ns.class_("KnxComponent", cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(KnxComponent),
            cv.Optional(
                "startup_time", default="5s"
            ): cv.positive_time_period_milliseconds,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)


cg.add_library("knx", None, "https://github.com/berni2612/knx.git#esphome")
cg.add_build_flag("-D MASK_VERSION=0x07B0")
cg.add_build_flag("-D KNX_FLASH_SIZE=1024")
cg.add_build_flag("-D KNX_NO_PRINT")
cg.add_build_flag("-D KNX_NO_AUTOMATIC_GLOBAL_INSTANCE")


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.startup_time(config["startup_time"]))
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
