#include "chip.h"
#include "pantalla.h"
#include "digital.h"
#include <stdbool.h>
#include "poncho.h"
#include <stdint.h>

typedef struct board_s{

    digital_output_t Seg_A,Seg_B,Seg_C,Seg_D,Seg_E,Seg_F,Seg_G;

    digital_output_t Punto;

    digital_output_t Dig_1,Dig_2,Dig_3,Dig_4;

    digital_input_t Aceptar,Cancelar,F1,F2,F3,F4;

    display_t display;

    digital_output_t led_azul;
    digital_output_t led_rojo;
    digital_output_t led_amarillo;
    digital_output_t led_verde;
    digital_output_t led_rojo_rgb;
    digital_output_t led_verde_rgb;

    digital_input_t tecla_1;
    digital_input_t tecla_2;
    digital_input_t tecla_3;
    digital_input_t tecla_4;


}const* const board_t;

board_t BoardCreate(void);