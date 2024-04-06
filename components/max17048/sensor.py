import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    CONF_BATTERY_LEVEL,
    CONF_ID,
    DEVICE_CLASS_BATTERY,
    UNIT_PERCENT,
    STATE_CLASS_MEASUREMENT,
)

DEPENDENCIES = ["i2c"]

max17048_ns = cg.esphome_ns.namespace("max17048")
MAX17048Component = max17048_ns.class_(
    "MAX17048Component", cg.PollingComponent, i2c.I2CDevice
)

MAX17048BatteryLevelDevice = max17048_ns.class_("MAX17048BatteryLevelDevice", i2c.I2CDevice)


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(MAX17048Component),
            cv.Required(CONF_BATTERY_LEVEL): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                accuracy_decimals=2,  # Resolution: 0.04
                device_class=DEVICE_CLASS_BATTERY,
                state_class=STATE_CLASS_MEASUREMENT,
            )
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x36))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    
    battery_level_sensor = await sensor.new_sensor(config[CONF_BATTERY_LEVEL])
    cg.add(var.set_battery_level_sensor(battery_level_sensor))