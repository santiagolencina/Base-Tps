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

typedef struct digital_output_s *digital_output_t;
typedef struct digital_input_s *digital_input_t;

digital_output_t Digital_OutputCreate(uint8_t port,uint8_t pin);
digital_input_t  DigitalInputCreate(uint8_t port,uint8_t invertir,uint8_t pin);

void DigitalOutPutActivate(digital_output_t output);
void DigitalOutPutDesactivate(digital_output_t output);
void DigitalOutPutToggle(digital_output_t output);
bool DigitalInputState(digital_input_t input);
bool DigitalInputhasChanged(digital_input_t input);
bool DigitalInputhasActivated(digital_input_t input);
bool DigitalInputhasDesactivated(digital_input_t input);

#endif