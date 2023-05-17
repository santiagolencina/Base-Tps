#include "chip.h"
#include "digital.h"
#include <stdbool.h>
#include <stdint.h>

#define LED_RED_PORT 2
#define LED_RED_PIN 0
#define LED_RED_FUNC SCU_MODE_FUNC4
#define LED_RED_GPIO 5
#define LED_RED_BIT 0

#define LED_GREEN_PORT 2
#define LED_GREEN_PIN 1
#define LED_GREEN_FUNC SCU_MODE_FUNC4
#define LED_GREEN_GPIO 5
#define LED_GREEN_BIT 1

#define LED_BLUE_PORT 2
#define LED_BLUE_PIN 2
#define LED_BLUE_FUNC SCU_MODE_FUNC4
#define LED_BLUE_GPIO 5
#define LED_BLUE_BIT 2

#define LED_1_PORT 2
#define LED_1_PIN 10
#define LED_1_FUNC SCU_MODE_FUNC0
#define LED_1_GPIO 0
#define LED_1_BIT 14

#define LED_2_PORT 2
#define LED_2_PIN 11
#define LED_2_FUNC SCU_MODE_FUNC0
#define LED_2_GPIO 1
#define LED_2_BIT 11

#define LED_3_PORT 2
#define LED_3_PIN 12
#define LED_3_FUNC SCU_MODE_FUNC0
#define LED_3_GPIO 1
#define LED_3_BIT 12

#define BUTTON_1_PORT 1
#define BUTTON_1_PIN 0
#define BUTTON_1_FUNC SCU_MODE_FUNC0
#define BUTTON_1_GPIO 0
#define BUTTON_1_BIT 4

#define BUTTON_2_PORT 1
#define BUTTON_2_PIN 1
#define BUTTON_2_FUNC SCU_MODE_FUNC0
#define BUTTON_2_GPIO 0
#define BUTTON_2_BIT 8

#define BUTTON_3_PORT 1
#define BUTTON_3_PIN 2
#define BUTTON_3_FUNC SCU_MODE_FUNC0
#define BUTTON_3_GPIO 0
#define BUTTON_3_BIT 9

#define BUTTON_4_PORT 1
#define BUTTON_4_PIN 6
#define BUTTON_4_FUNC SCU_MODE_FUNC0
#define BUTTON_4_GPIO 1
#define BUTTON_4_BIT 9


/// @brief Input and Output to be used
typedef struct board_io_s{

    digital_output_t blue_led;
    digital_output_t red_led;
    digital_output_t yellow_led;
    digital_output_t green_led;

    digital_input_t button_1;
    digital_input_t button_2;
    digital_input_t button_3;
    digital_input_t button_4;

}const* const board_io_t;


/// @brief Create a board
board_io_t BoardCreate(void);
