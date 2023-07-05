

#include "bsp.h"



static struct board_s board ={0};



void ScreenTurnOff(void);

void SegmentsTurnOn(uint8_t segments);

void DigitTurnOn(uint8_t digit);



board_t BoardCreate(void){


    /******************/
    Chip_SCU_PinMuxSet(SEGMENT_A_PORT, SEGMENT_A_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_A_FUNC);
    board.Seg_A=Digital_OutputCreate(SEGMENT_A_GPIO, SEGMENT_A_BIT);
    
    Chip_SCU_PinMuxSet(SEGMENT_B_PORT, SEGMENT_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_B_FUNC);
    board.Seg_B=Digital_OutputCreate(SEGMENT_B_GPIO, SEGMENT_B_BIT);

    Chip_SCU_PinMuxSet(SEGMENT_C_PORT, SEGMENT_C_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_C_FUNC);
    board.Seg_C=Digital_OutputCreate(SEGMENT_C_GPIO, SEGMENT_C_BIT);

    Chip_SCU_PinMuxSet(SEGMENT_D_PORT, SEGMENT_D_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_D_FUNC);
    board.Seg_D=Digital_OutputCreate(SEGMENT_D_GPIO, SEGMENT_D_BIT);
    
    Chip_SCU_PinMuxSet(SEGMENT_E_PORT, SEGMENT_E_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_E_FUNC);
    board.Seg_E=Digital_OutputCreate(SEGMENT_E_GPIO, SEGMENT_E_BIT);

    Chip_SCU_PinMuxSet(SEGMENT_F_PORT, SEGMENT_F_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_F_FUNC);
    board.Seg_F=Digital_OutputCreate(SEGMENT_F_GPIO, SEGMENT_F_BIT);

    Chip_SCU_PinMuxSet(SEGMENT_G_PORT, SEGMENT_G_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_G_FUNC);
    board.Seg_G=Digital_OutputCreate(SEGMENT_G_GPIO, SEGMENT_G_BIT);

    Chip_SCU_PinMuxSet(SEGMENT_P_PORT, SEGMENT_P_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_P_FUNC);
    board.Punto=Digital_OutputCreate(SEGMENT_P_GPIO, SEGMENT_P_BIT);
    /******************/

    Chip_SCU_PinMuxSet(DIGIT_1_PORT, DIGIT_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_1_FUNC);
    board.Dig_1=Digital_OutputCreate(DIGIT_1_GPIO, DIGIT_1_BIT);  

    Chip_SCU_PinMuxSet(DIGIT_2_PORT, DIGIT_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_2_FUNC);
    board.Dig_2=Digital_OutputCreate(DIGIT_2_GPIO, DIGIT_2_BIT); 
    
    Chip_SCU_PinMuxSet(DIGIT_3_PORT, DIGIT_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_3_FUNC);
    board.Dig_3=Digital_OutputCreate(DIGIT_3_GPIO, DIGIT_3_BIT); 

    Chip_SCU_PinMuxSet(DIGIT_4_PORT, DIGIT_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_4_FUNC);
    board.Dig_4=Digital_OutputCreate(DIGIT_4_GPIO, DIGIT_4_BIT); 

    /******************/

    Chip_SCU_PinMuxSet(KEY_ACCEPT_PORT, KEY_ACCEPT_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_ACCEPT_FUNC);
    board.Aceptar=DigitalInputCreate(KEY_ACCEPT_GPIO,no_invertir_logica, KEY_ACCEPT_BIT);

    Chip_SCU_PinMuxSet(KEY_CANCEL_PORT, KEY_CANCEL_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_CANCEL_FUNC);
    board.Cancelar=DigitalInputCreate(KEY_CANCEL_GPIO,no_invertir_logica, KEY_CANCEL_BIT);

    Chip_SCU_PinMuxSet(KEY_F1_PORT, KEY_F1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F1_FUNC);
    board.F1=DigitalInputCreate(KEY_F1_GPIO,no_invertir_logica, KEY_F1_BIT);

    Chip_SCU_PinMuxSet(KEY_F2_PORT, KEY_F2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F2_FUNC);
    board.F2=DigitalInputCreate(KEY_F2_GPIO,no_invertir_logica, KEY_F2_BIT);

    Chip_SCU_PinMuxSet(KEY_F3_PORT, KEY_F3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F3_FUNC);
    board.F3=DigitalInputCreate(KEY_F3_GPIO,no_invertir_logica, KEY_F3_BIT);

    Chip_SCU_PinMuxSet(KEY_F4_PORT, KEY_F4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F4_FUNC);
    board.F4=DigitalInputCreate(KEY_F4_GPIO,no_invertir_logica, KEY_F4_BIT);

/////////////

    Chip_SCU_PinMuxSet(LED_B_PORT, LED_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_B_FUNC);
    board.led_azul=Digital_OutputCreate(LED_B_GPIO, LED_B_BIT);
    /******************/
    Chip_SCU_PinMuxSet(LED_1_PORT, LED_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_1_FUNC);
    board.led_amarillo=Digital_OutputCreate(LED_1_GPIO, LED_1_BIT);

    Chip_SCU_PinMuxSet(LED_2_PORT, LED_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_2_FUNC);
    board.led_rojo=Digital_OutputCreate(LED_2_GPIO, LED_2_BIT);

    Chip_SCU_PinMuxSet(LED_3_PORT, LED_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_3_FUNC);
    board.led_verde=Digital_OutputCreate(LED_3_GPIO,LED_3_BIT);

    Chip_SCU_PinMuxSet(LED_RR_PORT, LED_RR_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_RR_FUNC);
    board.led_rojo_rgb=Digital_OutputCreate(LED_RR_GPIO,LED_RR_BIT);

    Chip_SCU_PinMuxSet(LED_GG_PORT, LED_GG_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_GG_FUNC);
    board.led_verde_rgb=Digital_OutputCreate(LED_GG_GPIO,LED_GG_BIT);
    /******************/
    Chip_SCU_PinMuxSet(TEC_1_PORT, TEC_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_1_FUNC);
    board.tecla_1=DigitalInputCreate(TEC_1_GPIO,invertir_logica,TEC_1_BIT);

    Chip_SCU_PinMuxSet(TEC_2_PORT, TEC_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_2_FUNC);
    board.tecla_2=DigitalInputCreate(TEC_2_GPIO,invertir_logica, TEC_2_BIT);

    Chip_SCU_PinMuxSet(TEC_3_PORT, TEC_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_3_FUNC);
    board.tecla_3=DigitalInputCreate(TEC_3_GPIO,invertir_logica, TEC_3_BIT);

    Chip_SCU_PinMuxSet(TEC_4_PORT, TEC_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_4_FUNC);
    board.tecla_4=DigitalInputCreate(TEC_4_GPIO,invertir_logica,TEC_4_BIT);



    

    board.display= DisplayCreate(4,&(struct display_driver_s){
        .ScreenTurnOff=ScreenTurnOff,
        .SegmentsTurnOn=SegmentsTurnOn,
        .DigitTurnOn=DigitTurnOn,
    });




    return &board;
}

void ScreenTurnOff(void){
    Chip_GPIO_ClearValue(LPC_GPIO_PORT,DIGITS_GPIO,DIGITS_MASK);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT,SEGMENTS_MASK,SEGMENTS_MASK);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_P_GPIO,SEGMENT_P_BIT,false);
}

void SegmentsTurnOn(uint8_t segments){
    Chip_GPIO_ClearValue(LPC_GPIO_PORT,SEGMENTS_GPIO,SEGMENTS_MASK);
    Chip_GPIO_SetValue(LPC_GPIO_PORT,SEGMENTS_GPIO,(segments) & SEGMENTS_MASK);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_P_GPIO,SEGMENT_P_BIT, segments & SEGMENT_P);
}

void DigitTurnOn(uint8_t digit){
    Chip_GPIO_SetValue(LPC_GPIO_PORT,DIGITS_GPIO,(1<<(digit)) & DIGITS_MASK);

}

void SysTick_Init(uint16_t ticks){
    __asm volatile ("cpsid i");
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/ticks);
    //NVIC_SetPriotity(SysTick_IRQn,(1<<__NVIC_PRIO_BITS)-1);
    __asm volatile ("cpsie i");
}