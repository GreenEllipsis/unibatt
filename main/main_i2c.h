/* 
application-specific I2C functions 
*/
// C and C++ libraraies
// #include <stdio.h>

// FreeRTOS
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// ESP-IDF libraries
#include "esp_system.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

// static const char *TAG_I2C = "unibattI2C";

#define I2C_CLIENT_SCL_IO  GPIO_NUM_16 /*!< GPIO number used for I2C client clock */
#define I2C_CLIENT_SDA_IO  GPIO_NUM_17 /*!< GPIO number used for I2C client data  */
i2c_port_t i2c_client_num = I2C_NUM_0;                        /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
// TEST #define I2C_CLIENT_FREQ_HZ 400000               /*!< I2C master clock frequency */
#define I2C_CLIENT_FREQ_HZ 50000               /*!< I2C master clock frequency */ //320000 too fast for the AIP display
#define I2C_CLIENT_TX_BUF_DISABLE 0             /*!< I2C master doesn't need buffer */
#define I2C_CLIENT_RX_BUF_DISABLE 0             /*!< I2C master doesn't need buffer */
#define I2C_CLIENT_TIMEOUT_MS 1000


/**
 * @brief i2c client initialization
 */
static esp_err_t i2c_client_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_CLIENT_SDA_IO,
        .scl_io_num = I2C_CLIENT_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_DISABLE, //.sda_pullup_en
        .scl_pullup_en = GPIO_PULLUP_DISABLE, //.scl_pullup_en
        .master = {.clk_speed = I2C_CLIENT_FREQ_HZ}, //.master.clk_speed
        .clk_flags = 0//  =  default clock TEST
    };

    ESP_ERROR_CHECK(i2c_param_config(i2c_client_num, &conf));

    return i2c_driver_install(i2c_client_num, conf.mode, I2C_CLIENT_RX_BUF_DISABLE, I2C_CLIENT_TX_BUF_DISABLE, 0);
}
