/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
// C and C++ libraraies
#include <stdio.h>

// FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ESP-IDF libraries
#include "esp_system.h"
#include "esp_log.h"
#include "esp_timer.h"
// #include "driver/i2c.h"
#include "sdkconfig.h"
#include "Arduino.h"

// 3rd party libraries
#include "SerLCD.h"
#include <LiquidMenu.h>

// main helper functions
#include "main_i2c.h"
#include "main_liquid_menu.h"

static const char *TAG = "unibatt";

extern "C" void app_main(void)
{
   esp_log_level_set("*", ESP_LOG_DEBUG); // set all components to DEBUG level
   ESP_ERROR_CHECK(i2c_client_init());
   ESP_LOGI(TAG, "I2C initialized successfully");
   ESP_LOGI(TAG, "portTICK_PERIOD_MS: %li", (long int)portTICK_PERIOD_MS);

  lcd.begin(i2c_client_num); //Set up the LCD for I2C communication

  lcd.setBacklight(255, 255, 255); //Set backlight to bright white
  lcd.setContrast(0); //Set contrast. Lower to 0 for higher contrast.

  lcd.clear(); //Clear the display - this moves the cursor to home position as well
//   lcd.print("Hello, World!");
    menu.update();

    uint16_t s;
    xTaskCreate(buttonsCheck, "buttonCheck", 2048, NULL, 5, NULL);
    // while(1) {
    //     s =  esp_timer_get_time()/1000000;
    //     printf("%d seconds...\n",s);
    //     lcd.setCursor(0,1);
    //     lcd.print(s);
    //     vTaskDelay(pdMS_TO_TICKS(900));
    // }
}
