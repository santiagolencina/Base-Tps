/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Lencina Martinez Luis Santiago
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS  "
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;  BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdint.h>
#include <stdbool.h>


//! Pulsos por segundo
#define CLOCK_SEC 1000

//! Frecuencia con la que se mantiene actualizada la hora.
#define REFRESH 60

//! Tiempo a posponer en minutos.
#define SNOOZE_TIME_MINUTES 5


//! Definición de reloj
typedef struct my_watch_s *my_watch_t;


/// @brief Funcion que crea un objeto tipo reloj
/// @param Clock_seconds cantidad de ciclos necesarios para incrementar el reloj en un segundo.
/// @return
my_watch_t CreateWatch(uint32_t Clock_seconds);

/// @brief Funcion de carga de hora en reloj.
/// @param watch Objeto de tipo reloj a crear.
/// @param time arreglo de seis (6) elementos que contiene la hora a cargar
/// @param size tamaño de arreglo que contiene la hora
/// @return "true" significa que la carga se realizo con exito
bool SetUpTime(my_watch_t watch, const uint8_t *time, uint32_t size);

/// @brief Funcion de retorno de valor de hora.
/// @param watch Objeto de tipo reloj al cual se le extrae la hora.
/// @param time arreglo de seis (6) elementos que contiene la hora.
/// @param size tamaño de arreglo que contiene la hora.
/// @return "true" significa que la hora es valida
bool GetTime(my_watch_t watch, uint8_t *time, uint8_t size);

/// @brief Funcion de actualizacion de tiempo en objeto reloj.
/// @param watch
void RefreshTime(my_watch_t watch);

/// @brief Funcion utilizada con el fin de setear la cuenta de los pulsos del reloj en 0.
/// @param watch objeto de tipo reloj a setear.
void SetUpClock(my_watch_t watch);

/// @brief Funcion utilizada para incrementar cuenta actual de pulsos del reloj en una unidad.
/// @param watch objeto de tipo reloj a setear.
void IncreaseClock(my_watch_t watch);

/// @brief Funcion que se encarga de setear la hora de la alarma
/// @param watch Objeto de tipo reloj al cual se cargara una alarma
/// @param time arreglo de seis (6) elementos que contiene la hora.
/// @param size tamaño de arreglo que contiene la hora
/// @return si la alarma se pude establecer devuelve un false
bool SetUpAlarm(my_watch_t watch, const uint8_t *time, uint8_t size);

/// @brief Funcion que retorna el valor de la alarma
/// @param watch Objeto de tipo reloj a consultar
/// @param time arreglo de seis (6) elementos que contiene la hora.
/// @param size tamaño de arreglo que contiene la hora
/// @return retorna true pues enciende la alarma
bool GetAlarmTime(my_watch_t watch, uint8_t *time, uint32_t size);

/// @brief Funcion de activacion de Alarma
/// @param watch Objeto de tipo reloj a Activar
/// @param status Indica el estao de la alarma : "false-->desactivada true-->activada"
/// @return
bool EnableAlarm(my_watch_t watch, bool status);

/// @brief Funcion que verifica si la alarma del reloj se encuentra Activada o no.
/// @param watch Objeto de tipo reloj a testear
/// @return "True" significa que la alarma se encuantra Activada, caso contrario, desactivada
bool AlarmStatus(my_watch_t watch);

/// @brief Funcion que pospone la alarma de un reloj tiempo definido.
/// @param watch Objeto de tipo reloj.
/// @param snooze tiempo a posponer
/// @return
bool SnoozeAlarm(my_watch_t watch, uint8_t snooze);

/// @brief Funcion que indica que la alarma esta sonando.
/// @param watch Objeto de tipo reloj
/// @return
bool AlarmRinging(my_watch_t watch);