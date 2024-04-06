
#include "esphome/core/log.h"
#include "max17048.h"

namespace esphome
{
    namespace max17048
    {

        static const char *const TAG = "max17048";

        constexpr uint16_t REG_PCT = 0x4;

        void MAX17048Component::setup()
        {
            ESP_LOGCONFIG(TAG, "Setting up max17048");
        }

        void MAX17048Component::dump_config()
        {
            ESP_LOGCONFIG(TAG, "MAX17048:");
            LOG_I2C_DEVICE(this);
            LOG_SENSOR("  ", "Percentage", this->percentage_sensor_);
        }

        void MAX17048Component::update()
        {
            uint16_t perentage_raw;
            if (!read_byte_16(REG_PCT, &perentage_raw))
            {
                ESP_LOGW(TAG, "'%s' - unable to read percentage register", this->name_.c_str());
                return;
            }
            float percentage = perentage_raw / 256.0f;
            this->percentage_sensor_->publish_state(percentage);
        }

    } // namespace max17048
} // namespace esphome
