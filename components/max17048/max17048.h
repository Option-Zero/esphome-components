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

            void set_battery_v_sensor(sensor::Sensor *battery_v_sensor) { this->battery_v_sensor_ = battery_v_sensor; }
            void set_battery_soc_sensor(sensor::Sensor *battery_soc_sensor) { this->battery_soc_sensor_ = battery_soc_sensor; }
            void set_battery_soc_rate_sensor(sensor::Sensor *battery_soc_rate_sensor) { this->battery_soc_rate_sensor_ = battery_soc_rate_sensor; }

        protected:
            sensor::Sensor *battery_v_sensor_;
            sensor::Sensor *battery_soc_sensor_;
            sensor::Sensor *battery_soc_rate_sensor_;
        };
    } // namespace max17048
} // namespace esphome