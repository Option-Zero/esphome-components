
#include "esphome/core/log.h"
#include "max17048.h"

namespace esphome
{
    namespace max17048
    {

        static const char *const TAG = "max17048";

        // Data sheet: https://www.analog.com/media/en/technical-documentation/data-sheets/MAX17048-MAX17049.pdf
        constexpr uint16_t REG_VCELL = 0x2;      // ADC measurement of VCELL. LSB: 78.125µV/cell
        constexpr uint16_t REG_SOC = 0x4;        // Battery state of charge.  LSB: 1%/256
        constexpr uint16_t REG_MODE = 0x6;       // Operating mode
        constexpr uint16_t REG_VERSION = 0x8;    // Version number
        constexpr uint16_t REG_HIBRT = 0xB;      // Hibernate threshold. Read/write.     Default: 0x971C
        constexpr uint16_t REG_CONFIG = 0x0C;    // Configuration register. Read/write. Default: 0x00FF
        constexpr uint16_t REG_VALRT = 0x14;     // Voltage alert threshold. Read/write. Default: 0x00FF
        constexpr uint16_t REG_CRATE = 0x16;     // Current rate. LSB: 0.208%/hr
        constexpr uint16_t REG_VRESET_ID = 0x18; //  VCELL-reset-threshold and chip ID. Read/write. Default: 0x96??
        constexpr uint16_t REG_STATUS = 0x1A;    // Indicates overvoltage, undervoltage, SOC change, SOC low, and reset alerts.
        // constexpr uint16_t REG_TABLE = 0x40 to 0x7F; // Configures battery parameters. Write-only.
        constexpr uint16_t REG_CMD = 0xFE; // Sends Power-On Reset (POR) command

        void MAX17048Component::setup()
        {
            ESP_LOGCONFIG(TAG, "Setting up max17048");
        }

        void MAX17048Component::dump_config()
        {
            ESP_LOGCONFIG(TAG, "MAX17048:");
            LOG_I2C_DEVICE(this);
            LOG_SENSOR("  ", "Voltage (V)", this->battery_v_sensor_);
            LOG_SENSOR("  ", "State of Charge (%)", this->battery_soc_sensor_);
            LOG_SENSOR("  ", "Current (%/hr)", this->battery_current_sensor_);
        }

        void MAX17048Component::update()
        {
            uint16_t voltage_raw;
            if (!read_byte_16(REG_VCELL, &voltage_raw))
            {
                ESP_LOGW(TAG, "'%s' - unable to read voltage register", this->name_.c_str());
                return;
            }
            float voltage = voltage_raw * 78.125f / 1000000.0f; // VCELL lsb is 78.125µV/cell per data sheet
            this->battery_v_sensor_->publish_state(voltage);

            uint16_t percentage_raw;
            if (!read_byte_16(REG_SOC, &percentage_raw))
            {
                ESP_LOGW(TAG, "'%s' - unable to read percentage register", this->name_.c_str());
                return;
            }
            float percentage = percentage_raw / 256.0f; // SoC lsb is 1/256% per data sheet
            this->battery_soc_sensor_->publish_state(percentage);

            uint16_t current_raw;
            if (!read_byte_16(REG_SOC, &current_raw))
            {
                ESP_LOGW(TAG, "'%s' - unable to read current register", this->name_.c_str());
                return;
            }
            float current = current_raw * 0.208f; // Current rate lsb is 0.208%/hr per data sheet
            this->battery_current_sensor_->publish_state(current);
        }

    } // namespace max17048
} // namespace esphome
