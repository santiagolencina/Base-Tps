#include <stdint.h>
#ifndef __PANTALLA_H
#define __PANTALLA_H

#define SEGMENT_A (1 << 0)
#define SEGMENT_B (1 << 1)
#define SEGMENT_C (1 << 2)
#define SEGMENT_D (1 << 3)
#define SEGMENT_E (1 << 4)
#define SEGMENT_F (1 << 5)
#define SEGMENT_G (1 << 6)
#define SEGMENT_P (1 << 7)

typedef struct display_s *display_t;

typedef void (*display_screen_off_t) (void);

typedef void(*display_segment_on_t)(uint8_t segments);

typedef void(*display_digit_on_t)(uint8_t digit);

/// @brief Se define esta estructura para cargar los punteros a las funciones que permiten darle funcionalidad a la pantalla
typedef struct display_driver_s{
    display_screen_off_t ScreenTurnOff;
    display_segment_on_t SegmentsTurnOn;
    display_digit_on_t   DigitTurnOn;
}const *const display_driver_t;

/// @brief Crear Display
/// @param digits Pumero entero de digitos que posee el display 
/// @param driver Puntero que maneja la pantalla
/// @return  
display_t DisplayCreate(uint8_t digits,display_driver_t driver);


/// @brief Funcion que permite cambiar valor de Display
/// @param display Puntero al display a modificar
/// @param number Puntero al arreglo donde se encuentra la informacion que se ingresara al display
/// @param size Cantiadad de digitos que posee el display
void DisplayWriteBCD(display_t display,uint8_t *number,uint8_t size);

/// @brief Funcion de barrido de pantalla 
/// @param display Puntero al display a multiplexar
void DisplayRefresh(display_t display);

#endif