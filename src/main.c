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

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "chip.h"
#include "digital.h"
#include "poncho.h"
#include "bsp.h"
#include "definiciones.h"
#include <stdbool.h>
#include "my_watch.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */
void delay(void);

/* === Public variable definitions ============================================================= */

const struct board_s* board;
struct my_watch_s* reloj;
uint8_t hora[6],alarma[6];
uint8_t estado=0;
/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

int main(void) {

    SysTick_Init(1000);
    board = BoardCreate();
    reloj=CreateWatch(1000);

    
    
    
    while (true) {

        
        //Consideracion: quiero que la alarma por defecto este activada, este configurada o no
        
    }
}



void SysTick_Handler(void){

    static unsigned int tiempo=0,tiempo1=0;
    static unsigned int temporizador=0;
    static unsigned int delay;
    static unsigned int caso=0;
    static signed int variable_general=0;
    bool botonF4_presionado=false;
    bool botonF3_presionado=false;
    bool botonAceptar_presionado=false;
    bool botonCancelar_presionado=false;
    

    switch (estado)
    {

    case inicio:
        variable_general=0;
        GetTime(reloj, hora, 6);
        
        temporizador++;

        if(temporizador<1000){
        DisplayWriteBCD(board->display,(uint8_t[]){hora[3],hora[2],hora[1],hora[0]},4,2); 
        }
        else{
        DisplayWriteBCD(board->display,(uint8_t[]){SEG_OFF,SEG_OFF,SEG_OFF,SEG_OFF},4,PUNTOS_OFF);
        }
        if (temporizador>=2000) temporizador=0;


        if(DigitalInputState(board->F1)) tiempo++;
        else tiempo=0;
        if(tiempo>=3000) {
            estado=ajuste_minutos;
            tiempo=0;
        }

        if(DigitalInputState(board->F2)) tiempo1++;
        else tiempo1=0;
        if(tiempo1>=3000) {
            estado=configurar_alarma_minutos;
            GetAlarmTime(reloj,hora,6);
            variable_general=hora[2]*10+hora[3];
            tiempo1=0;
        }

        break;

    case ajuste_minutos:
        temporizador++;
        if(temporizador<1000){
        DisplayWriteBCD(board->display,(uint8_t[]){SEG_OFF,SEG_OFF,hora[1],hora[0]},4,PUNTOS_OFF);  
        }
        else{
        DisplayWriteBCD(board->display,(uint8_t[]){hora[3],hora[2],hora[1],hora[0]},4,PUNTOS_OFF);
        }
        if (temporizador>=2000) temporizador=0;


        if(DigitalInputState(board->F4))botonF4_presionado=true;
        if(botonF4_presionado){
            delay++;
            if(delay>=150){
                delay=0;
                botonF4_presionado=false;
                variable_general++;
            }
        }

        if(DigitalInputState(board->F3))botonF3_presionado=true;
        if(botonF3_presionado){
            delay++;
            if(delay>=150){
                delay=0;
                botonF3_presionado=false;
                variable_general--;   
            }
        }
        if(variable_general<0)variable_general=59;
        if(variable_general>59) variable_general=0;
        hora[3]=variable_general%10;
        hora[2]=(variable_general-hora[3])/10;

        if(DigitalInputState(board->Aceptar)){
            variable_general=0;
            delay=0;
            estado=ajuste_horas;
            GetTime(reloj,alarma,6);
            variable_general=alarma[0]*10+alarma[1];
        }
        if(
            DigitalInputState(board->Aceptar)||
            DigitalInputState(board->F1)||
            DigitalInputState(board->F2)||
            DigitalInputState(board->F3)||
            DigitalInputState(board->F4)
            ) tiempo=0;

        tiempo++;
        if (tiempo>30000) {
            estado=caso;
            tiempo=0;
        }
        if(DigitalInputState(board->Cancelar)) estado=caso;


    break;

    case ajuste_horas:
        temporizador++;
        if(temporizador<1000){
        DisplayWriteBCD(board->display,(uint8_t[]){hora[3],hora[2],hora[1],hora[0]},4,PUNTOS_OFF);  
        }
        else{
        DisplayWriteBCD(board->display,(uint8_t[]){hora[3],hora[2],SEG_OFF,SEG_OFF},4,PUNTOS_OFF);
        }
        if (temporizador>=2000) temporizador=0;


        if(DigitalInputState(board->F4))botonF4_presionado=true;
        if(botonF4_presionado){
            delay++;
            if(delay>=150){
                delay=0;
                botonF4_presionado=false;
                variable_general++;
            }
        }

        if(DigitalInputState(board->F3))botonF3_presionado=true;
        if(botonF3_presionado){
            delay++;
            if(delay>=150){
                delay=0;
                botonF3_presionado=false;
                variable_general--;   
            }
        }
        if(variable_general<0)variable_general=23;
        if(variable_general>23) variable_general=0;
        hora[1]=variable_general%10;
        hora[0]=(variable_general-hora[1])/10;

        if(
            DigitalInputState(board->Aceptar)||
            DigitalInputState(board->F1)||
            DigitalInputState(board->F2)||
            DigitalInputState(board->F3)||
            DigitalInputState(board->F4)
            ) tiempo=0;

        tiempo++;
        if (tiempo>30000) {
            estado=caso;
            tiempo=0;
        }
        if(DigitalInputState(board->Cancelar)) estado=caso;


        if(DigitalInputState(board->Aceptar))botonAceptar_presionado=true;
        if(botonAceptar_presionado){
            delay++;
            if(delay>=300){
                delay=0;
                botonAceptar_presionado=false;
                if(DigitalInputState(board->Aceptar)){
                     SetUpTime(reloj,hora,4);
                     estado=mostrar_hora;  
                     EnableAlarm(reloj,false);              
                }
            }
        }

    break;


    case mostrar_hora:
        caso=mostrar_hora;
        variable_general=0;
        GetTime(reloj, hora, 6);

        temporizador++;

        /*
        if(AlarmStatus(reloj))variable_general=5;
        else {variable_general=2;
            SnoozeAlarmDia(reloj);
        }
        */

        if(temporizador<1000){
        DisplayWriteBCD(board->display,(uint8_t[]){hora[3],hora[2],hora[1],hora[0]},4,variable_general);  
        }
        else{
        DisplayWriteBCD(board->display,(uint8_t[]){hora[3],hora[2],hora[1],hora[0]},4,PUNTOS_OFF);
        }
        if (temporizador>=2000) temporizador=0;

        if(DigitalInputState(board->F1)) tiempo++;
        else tiempo=0;
        if(tiempo>=3000) {
            estado=ajuste_minutos;
            tiempo=0;
            GetTime(reloj,hora,6);
            variable_general=hora[2]*10+hora[3];
        }

        if(DigitalInputState(board->F2)) tiempo1++;
        else tiempo1=0;
        if(tiempo1>=3000) {
            estado=configurar_alarma_minutos;
            GetAlarmTime(reloj,hora,6);
            variable_general=hora[2]*10+hora[3];
            tiempo1=0;
        }

        if(AlarmRinging(reloj)){
            DigitalOutPutActivate(board->led_amarillo);
            /*
            if(DigitalInputState(board->Cancelar)){
                DigitalOutPutDesactivate(board->led_amarillo);
                SnoozeAlarmDia(reloj);
                while(DigitalInputState(board->Cancelar))__asm("NOP");
            } 
            */
            if(DigitalInputState(board->Aceptar)){
                DigitalOutPutDesactivate(board->led_amarillo);
                SnoozeAlarm(reloj,10);
            } 
        }

        if(DigitalInputState(board->Aceptar)){
            EnableAlarm(reloj,true);
        }

        if(DigitalInputState(board->Cancelar))botonCancelar_presionado=true;
            if(botonCancelar_presionado){
                delay++;
                if(delay>=300){
                    delay=0;
                    botonCancelar_presionado=false;
                    if(DigitalInputState(board->Cancelar)){
                        EnableAlarm(reloj,false);              
                    }
            }
        }
     

    break;

    case configurar_alarma_minutos:

        temporizador++;
        if(temporizador<1000){
        DisplayWriteBCD(board->display,(uint8_t[]){SEG_OFF,SEG_OFF,hora[1],hora[0]},4,PUNTOS_ON);  
        }
        else{
        DisplayWriteBCD(board->display,(uint8_t[]){hora[3],hora[2],hora[1],hora[0]},4,PUNTOS_ON);
        }
        if (temporizador>=2000) temporizador=0;


        if(DigitalInputState(board->F4))botonF4_presionado=true;
        if(botonF4_presionado){
            delay++;
            if(delay>=150){
                delay=0;
                botonF4_presionado=false;
                variable_general++;
            }
        }

        if(DigitalInputState(board->F3))botonF3_presionado=true;
        if(botonF3_presionado){
            delay++;
            if(delay>=150){
                delay=0;
                botonF3_presionado=false;
                variable_general--;   
            }
        }
        if(variable_general<0)variable_general=59;
        if(variable_general>59) variable_general=0;
        hora[3]=variable_general%10;
        hora[2]=(variable_general-hora[3])/10;

        if(DigitalInputState(board->Aceptar)){
            variable_general=0;
            delay=0;
            estado=configurar_alarma_horas;
            variable_general=hora[0]*10+hora[1];
        }
        if(
            DigitalInputState(board->Aceptar)||
            DigitalInputState(board->F1)||
            DigitalInputState(board->F2)||
            DigitalInputState(board->F3)||
            DigitalInputState(board->F4)
            ) tiempo=0;

        tiempo++;
        if (tiempo>30000) {
            estado=caso;
            tiempo=0;
        }
        if(DigitalInputState(board->Cancelar)) estado=caso;

    break;

    case configurar_alarma_horas:
        temporizador++;
        if(temporizador<1000){
        DisplayWriteBCD(board->display,(uint8_t[]){hora[3],hora[2],hora[1],hora[0]},4,PUNTOS_ON);  
        }
        else{
        DisplayWriteBCD(board->display,(uint8_t[]){hora[3],hora[2],SEG_OFF,SEG_OFF},4,PUNTOS_ON);
        }
        if (temporizador>=2000) temporizador=0;


        if(DigitalInputState(board->F4))botonF4_presionado=true;
        if(botonF4_presionado){
            delay++;
            if(delay>=150){
                delay=0;
                botonF4_presionado=false;
                variable_general++;
            }
        }

        if(DigitalInputState(board->F3))botonF3_presionado=true;
        if(botonF3_presionado){
            delay++;
            if(delay>=150){
                delay=0;
                botonF3_presionado=false;
                variable_general--;   
            }
        }
        if(variable_general<0)variable_general=23;
        if(variable_general>23) variable_general=0;
        hora[1]=variable_general%10;
        hora[0]=(variable_general-hora[1])/10;

        if(
            DigitalInputState(board->Aceptar)||
            DigitalInputState(board->F1)||
            DigitalInputState(board->F2)||
            DigitalInputState(board->F3)||
            DigitalInputState(board->F4)
            ) tiempo=0;

        tiempo++;
        if (tiempo>30000) {
            estado=caso;
            tiempo=0;
        }
        if(DigitalInputState(board->Cancelar)) estado=caso;


        if(DigitalInputState(board->Aceptar))botonAceptar_presionado=true;
        if(botonAceptar_presionado){
            delay++;
            if(delay>=300){
                delay=0;
                botonAceptar_presionado=false;
                if(DigitalInputState(board->Aceptar)){
                     SetUpAlarm(reloj,hora,6);
                     estado=caso;                
                }
            }
        }

    break;


    default:
        break;
    }

    RefreshTime(reloj);
    DisplayRefresh(board->display);

}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */