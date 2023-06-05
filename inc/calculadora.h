#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/// @brief estructura para crear objeto calculadora
typedef struct calculadora_s *calculadora_t;

/// @brief Para pasar punteros a funciones 
typedef int (*funcion_t)(int,int);

/// @brief Crea el objeto calculadora
/// @param  
/// @return 
calculadora_t CrearCalculadora(void);

/// @brief Agrega operaciones a la calculadora
/// @param calculadora Objeto al cual quiero asignar una operacion
/// @param operador Operador con el cual se identificara el llamado a la funcion
/// @param funcion Puntero a la funcion que se desea ejecutar
/// @return 
bool AgregarOperacion(calculadora_t calculadora,char operador,funcion_t funcion);

/// @brief Esta funcion se llama para realizar la operacion
/// @param calculadora Calculadora con la cual se desea realizar la operacion
/// @param cadena Se introduce un texto con la operacion que se desea realizar por ej "2*5"
/// @return 
int Calcular(calculadora_t calculadora,char *cadena);