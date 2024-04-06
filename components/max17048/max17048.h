#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

// src/main.cpp:37:11: error: 'MAX17048Component' in namespace 'esphome::max17048' does not name a type
namespace esphome
{
    namespace max17048
    {
        class MAX17048Component : public PollingComponent, public sensor::Sensor, public i2c::I2CDevice
        {
        public:
            void setup() override;
            void dump_config() override;
            void update() override;

            void set_battery_level_sensor(sensor::Sensor *battery_level_sensor) { this->battery_level_sensor_ = battery_level_sensor; }

        protected:
            sensor::Sensor *battery_level_sensor_;
        };
    } // namespace max17048
} // namespace esphome