#include "bsp.h"

static struct board_io_s board ={0};

board_io_t BoardCreate(void){



    Chip_SCU_PinMuxSet(LED_RED_PORT, LED_RED_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_RED_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED_RED_GPIO, LED_RED_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, LED_RED_GPIO, LED_RED_BIT, true);

    Chip_SCU_PinMuxSet(LED_GREEN_PORT, LED_GREEN_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_GREEN_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED_GREEN_GPIO, LED_GREEN_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, LED_GREEN_GPIO, LED_GREEN_BIT, true);

    Chip_SCU_PinMuxSet(LED_BLUE_PORT, LED_BLUE_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_BLUE_FUNC);
    board.blue_led=Digital_OutputCreate(LED_BLUE_GPIO, LED_BLUE_BIT);
    /******************/
    Chip_SCU_PinMuxSet(LED_1_PORT, LED_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_1_FUNC);
    board.yellow_led=Digital_OutputCreate(LED_1_GPIO, LED_1_BIT);

    Chip_SCU_PinMuxSet(LED_2_PORT, LED_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_2_FUNC);
    board.red_led=Digital_OutputCreate(LED_2_GPIO, LED_2_BIT);

    Chip_SCU_PinMuxSet(LED_3_PORT, LED_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_3_FUNC);
    board.green_led=Digital_OutputCreate(LED_3_GPIO,LED_3_BIT);
    /******************/
    Chip_SCU_PinMuxSet(BUTTON_1_PORT, BUTTON_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | BUTTON_1_FUNC);
    board.button_1=DigitalInputCreate(BUTTON_1_GPIO,invertir_logica,BUTTON_1_BIT);

    Chip_SCU_PinMuxSet(BUTTON_2_PORT, BUTTON_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | BUTTON_2_FUNC);
    board.button_2=DigitalInputCreate(BUTTON_2_GPIO,invertir_logica, BUTTON_2_BIT);

    Chip_SCU_PinMuxSet(BUTTON_3_PORT, BUTTON_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | BUTTON_3_FUNC);
    board.button_3=DigitalInputCreate(BUTTON_3_GPIO,invertir_logica, BUTTON_3_BIT);

    Chip_SCU_PinMuxSet(BUTTON_4_PORT, BUTTON_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | BUTTON_4_FUNC);
    board.button_4=DigitalInputCreate(BUTTON_4_GPIO,invertir_logica,BUTTON_4_BIT);

    return &board;
}