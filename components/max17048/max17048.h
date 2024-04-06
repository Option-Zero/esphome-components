#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

namespace esphome
{
    namespace max17048
    {
        class MAX17048Sensor : public PollingComponent, public sensor::Sensor, public i2c::I2CDevice
        {
        public:
            void setup() override;
            void dump_config() override;
            void update() override;

            void set_percentage_sensor(sensor::Sensor *percentage_sensor) { this->percentage_sensor_ = percentage_sensor; }

        protected:
            sensor::Sensor *percentage_sensor_;
        };
    } // namespace max17048
} // namespace esphome