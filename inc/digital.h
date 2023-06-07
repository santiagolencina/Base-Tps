#include <stdbool.h>
#include <stdint.h>

#define numero_entradas 6
#define numero_salidas  14

#ifndef invertir_logica
#define invertir_logica 1
#endif

#ifndef no_invertir_logica
#define no_invertir_logica 0
#endif

#ifndef DIGITAL_H
#define DIGITAL_H

/// @brief Estructura para almacenar output data
typedef struct digital_output_s *digital_output_t;
/// @brief estructura para almacenar input data
typedef struct digital_input_s *digital_input_t;

/// @brief Crear salida digital
digital_output_t Digital_OutputCreate(uint8_t port,uint8_t pin);
/// @brief Crear entrada digital
digital_input_t  DigitalInputCreate(uint8_t port,uint8_t invertir,uint8_t pin);


/// @brief Activar salida
void DigitalOutPutActivate(digital_output_t output);
/// @brief Desactivar salida
void DigitalOutPutDesactivate(digital_output_t output);
/// @brief Conmutar salida
void DigitalOutPutToggle(digital_output_t output);

/// @brief Testear el valor digital de una entrada
bool DigitalInputState(digital_input_t input);
/// @brief Se ha detectado un cambio en la entrada
bool DigitalInputhasChanged(digital_input_t input);
/// @brief Entrada activada
bool DigitalInputhasActivated(digital_input_t input);
/// @brief Entrada desactivada
bool DigitalInputhasDesactivated(digital_input_t input);

#endif