
// #include "SerLCD.h"
#define SW_UP GPIO_NUM_32
#define SW_DOWN GPIO_NUM_33

static const char* TAG_LM = "unibatt_Lm";
// There are two types of functions for this example, one that increases some
// value and one that decreases it.

enum FunctionTypes {
	increase = 1,
	decrease = 2,
};

uint8_t led_level = 100;

SerLCD lcd; // Initialize the library with default I2C address 0x72

LiquidLine welcome_line1(1, 0, "LiquidMenu ", LIQUIDMENU_VERSION);
LiquidLine welcome_line2(1, 1, "Functions ex.");
LiquidScreen welcome_screen(welcome_line1, welcome_line2);

LiquidLine ledTitleLine(6, 0, "LED");
LiquidLine led_line(4, 1, "Level: ", led_level);
LiquidScreen led_screen(ledTitleLine, led_line);

LiquidMenu menu(lcd, led_screen);

// The increasing functions are attached with identification of 1.
/*
    * This function can later be called by pressing the 'UP' button
    * when 'led_line' is focused. If some other line is focused it's
    * corresponding function will be called.
*/

void increase_led_level() {
    ESP_LOGD(TAG_LM, "inc");
	if (led_level < 225) {
		led_level += 25;
	} else {
		led_level = 250;
	}
	lcd.setBacklight(led_level, led_level, 255-led_level);
}


void decrease_led_level() {
    ESP_LOGD(TAG_LM, "dec");
	if (led_level > 25) {
		led_level -= 25;
	} else {
		led_level = 0;
	}
	lcd.setBacklight(led_level, led_level, 255-led_level);
}


// Checks all the buttons.
void buttonsCheck(void *) {
    // Configure GPIO32 as input
    ESP_LOGI(TAG_LM, "buttonsCheck started");
    gpio_pad_select_gpio(SW_UP);
    gpio_set_direction(SW_UP, GPIO_MODE_INPUT);
    gpio_pad_select_gpio(SW_DOWN);
    gpio_set_direction(SW_DOWN, GPIO_MODE_INPUT);
    led_line.attach_function(increase, increase_led_level);
    // The decreasing functions are attached with identification of 2.
    led_line.attach_function(decrease, decrease_led_level);
    increase_led_level();
    menu.switch_focus();

    while (1) {
        if (gpio_get_level(SW_UP) == HIGH) {
            // Calls the function identified with
            // increase or 1 for the focused line.
            ESP_LOGI(TAG_LM, "UP");
            menu.call_function(increase);
        }
        if (gpio_get_level(SW_DOWN) == HIGH) {
            ESP_LOGI(TAG_LM, "DOWN");
            menu.call_function(decrease);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}