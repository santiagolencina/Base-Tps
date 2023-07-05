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
#include "my_constants.h"
#include "my_watch.h"
#include <stdbool.h>
#include "my_watch.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */


/// @brief Función que genera el efecto visual de parpadeo
/// @param _dot variable que indica que punto decimal sera el que se encienda
/// @param displays_off variable que indica que conjunto de display 7seg se apagaran
/// @param blink_timer_f variable que setea periodo de tiempo de parpadeo
void blink_display(uint8_t _dot, uint8_t displays_off, unsigned int blink_timer_f);

/// @brief Función que testea pulsador 
/// @param button recibe pulsador a testear de la placa
/// @param timer variable que indica por cuanto tiempo se debe mantener pulsado "button" para devolver "true"
/// @param button_test constante que filtra el pulsador se debe testear
/// @return "true" -> se mantuvo pulsado por el tiempo indicado , "false" -> no se pulso correctamente 
bool button_test (digital_input_t button , unsigned int timer, unsigned int button_test);

/// @brief Función que maneja valor a setear en los display al momento de la configuracion del tiempo
/// @param count_state indica si se debe incrementar o decrementar la cuenta
/// @param display_select indica que conjunto de displays 7seg se esta configurando (minutos u horas)
void decimal_to_seg (int count_state, int display_select);

/// @brief Función que copia tiempo del reloj en variable auxiliar para luego pegarla nuevamente en variable principal, esto se hace al momento de generar el efecto de parpadeo 
/// @param copy_paste "true" -> copy, "false" -> paste
void copy_paste_watch_time (bool copy_paste);



/* === Public variable definitions ============================================================= */



const struct board_s* board;
struct my_watch_s* watch;

/// @brief variable principal de tiempo
uint8_t watch_time [6];              
/// @brief variable auxiliar de tiempo que contiene el valor del nuevo tiempo al momento de la configuración
uint8_t watch_time_new [6]; 
/// @brief variable auxiliar donde se guarda tiempo al momento de configurar (usado para guardar "watch_time_new" al momento de generar efecto visual)
uint8_t watch_time_saved [6];
/// @brief variable principal de tiempo (alarma)
uint8_t watch_time_alarm [6];
/// @brief variable de maquina de estado
uint8_t state=init;

/// @brief contador utilizado para determinar tiempo de inactividad
unsigned int time=0;
/// @brief variable auxiliar que controla si se pulsan los pulsadores por el timepo previamente especificado
unsigned int pressed_timer=0;
/// @brief variable auxiliar que controla tiempo de parpadeo 
unsigned int blink_timer=BLINK_TIME_PERIOD;
/// @brief indica si se debe incrementar o decrementar la cuenta al momento de configurar la hora (alarma o reloj)
unsigned int count_status=0;
/// @brief variable de tipo decimal que lleva la cuenta de el tiempo a setear, que luego se traduce a cada uno de los display 7seg
signed int reg_time=0;

/// @brief "[F1,F2,F3,F4,Aceptar,Cancelar]"arreglo  que indica que pulsadores se pueden testear, al momento de empezar a testear uno en particular se ponen en 0 los demas, al finalizar el testeo se vuelve al valor de inicialización.
bool testing_buttons[]={1,1,1,1,1,1}; 
/// @brief indica que se esta configurando el tiempo
bool setting_up_flag=true;
/// @brief indica que se ejecuto una vez la rutina de interrupción
bool inc_time=false;
/// @brief watch dog timer que indica inactividad en los pulsadores al momento de configurar el tiempo
bool wdt=false;
/// @brief indica que un pulsado se comenzo a testear
bool new_button_tested=true;
/// @brief indica que punto debe ser encendido
uint8_t dot=0;



/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */



int main(void) {

    SysTick_Init(1000);
    board = BoardCreate();
    watch=CreateWatch(10);  //1000 es el valor para que la base de tiempo sea de 1 segundo

    watch_time[0]= 1;
    watch_time[1]= 2;
    watch_time[2]= 0;
    watch_time[3]= 0; 

    watch_time_alarm[0]= 1;
    watch_time_alarm[1]= 2;
    watch_time_alarm[2]= 1;
    watch_time_alarm[3]= 0; 

    SetUpTime(watch,watch_time,sizeof(watch_time));                     //watch time = 12:00
    SetUpAlarm(watch,watch_time_alarm,sizeof(watch_time_alarm));        //watch time alar = 12:10
    GetTime(watch,watch_time_new,sizeof(watch_time_new));               //watch time new = 12:00
    GetTime(watch,watch_time_saved,sizeof(watch_time_saved));           //watch time saved = 12:00


    while (true) {

        if(inc_time){   
            
            inc_time=false;

            if (AlarmStatus(watch)){
                if(AlarmRinging(watch)) DigitalOutPutActivate(board->led_azul);
                else                    DigitalOutPutDesactivate(board->led_azul);                    
            } 
            else{
                DigitalOutPutDesactivate(board->led_azul);
            }                        

            switch (state)
            {
            case init:
                    EnableAlarm(watch, false);
                    blink_display(DOT_2_ON,ALL_DISPLAY_OFF,BLINK_TIME_PERIOD);               // borra y escribe watch time new

                    if(testing_buttons[0]==1) if(button_test(board->F1,F1_TIMER,F1_)) {               
                        reg_time = (watch_time_saved[2]*10) + watch_time_saved[3];           // reg_time = ultimo valor de minutos mostrados por display antes de entrar en configuracion
                        setting_up_flag=true;                                                // entra en modo configuración
                        state = set_up_minute;                                               // configurar minutos 
                    }
                    if(testing_buttons[4]==1) if(button_test(board->Aceptar,DEBOUNCE_TIME,ACEPTAR_)){   
                        SetUpTime(watch,watch_time,sizeof(watch_time));
                        state = show_watch_time;
                        setting_up_flag=false; 
                        EnableAlarm(watch, true);                   
                    }

                break;

            case set_up_minute:

                    decimal_to_seg(count_status,MINUTES_SELECTED);                                  // redefine valores de display en base a cambios en reg_time si es que los hubo                    
                    blink_display(DOT_0_ON,MINUTES_OFF,BLINK_TIME_PERIOD);                          // borra y escribe watch time new

                    if(testing_buttons[4]==1) if(button_test(board->Aceptar,DEBOUNCE_TIME,ACEPTAR_)){
                        reg_time = (watch_time_saved[0]*10) + watch_time_saved[1];
                        setting_up_flag=true;
                        state = set_up_hour;  
                    }
                    if(testing_buttons[5]==1) if(button_test(board->Cancelar,DEBOUNCE_TIME,CANCELAR_)){
                        state = show_watch_time;
                        setting_up_flag=false;
                    } 
                    if(testing_buttons[3]==1) if(button_test(board->F4,DEBOUNCE_TIME,F4_)) count_status=INC_COUNT;
                    if(testing_buttons[2]==1) if(button_test(board->F3,DEBOUNCE_TIME,F3_)) count_status=DEC_COUNT;  
                    if(wdt) {               
                        state = show_watch_time;
                        setting_up_flag=false;
                        wdt=false;
                        time=0;                                              
                    }

                break;

            case set_up_hour:

                    decimal_to_seg(count_status,HOURS_SELECTED);
                    blink_display(DOT_2_ON,HOURS_OFF,BLINK_TIME_PERIOD); 
                    
                    if(testing_buttons[4]==1) if(button_test(board->Aceptar,DEBOUNCE_TIME,ACEPTAR_)){
                        SetUpTime(watch,watch_time_saved,sizeof(watch_time_saved));
                        state = show_watch_time;
                        setting_up_flag=false;
                    }
                    if(testing_buttons[5]==1) if(button_test(board->Cancelar,DEBOUNCE_TIME,CANCELAR_)){
                        state = show_watch_time;
                        setting_up_flag=false;                        
                    }
                    if(testing_buttons[3]==1) if(button_test(board->F4,DEBOUNCE_TIME,F4_)) count_status=INC_COUNT;
                    if(testing_buttons[2]==1) if(button_test(board->F3,DEBOUNCE_TIME,F3_)) count_status=DEC_COUNT;
                    if(wdt) {               
                        state = show_watch_time;
                        setting_up_flag=false;
                        wdt=false;
                        time=0;                                              
                    }

                break;

            case show_watch_time:

                    blink_display(DOT_2_ON,All_DISPLAY_ON,BLINK_TIME_PERIOD); 

                    if(testing_buttons[0]==1) if(button_test(board->F1,F1_TIMER,F1_)) {
                        GetTime(watch,watch_time_new,sizeof(watch_time_new));
                        copy_paste_watch_time(true);
                        reg_time = (watch_time_new[2]*10) + watch_time_new[3];
                        state = set_up_minute; 
                        setting_up_flag=true;
                    }

                    if(testing_buttons[1]==1) if(button_test(board->F2,F1_TIMER,F2_)) {               
                        GetAlarmTime(watch,watch_time_new,sizeof(watch_time_new));
                        copy_paste_watch_time(true);
                        reg_time = (watch_time_new[2]*10) + watch_time_new[3];           
                        setting_up_flag=true;                   
                        state = set_up_alarm_minute;                            
                    }

                    if(testing_buttons[4]==1) if(button_test(board->Aceptar,DEBOUNCE_TIME,ACEPTAR_)){ 

                        if (AlarmRinging(watch))    SnoozeAlarm(watch,5);
                        else                        EnableAlarm(watch, true);      

                    }

                    if(testing_buttons[5]==1) if(button_test(board->Cancelar,DEBOUNCE_TIME,CANCELAR_)){ 

                        if (!AlarmRinging(watch))    EnableAlarm(watch, false); 
                        SnoozeAlarm_24hs(watch);                   
                    
                    }

                break;

            case set_up_alarm_minute:

                    decimal_to_seg(count_status,MINUTES_SELECTED);                                                     
                    blink_display(ALL_DOT_ON,MINUTES_OFF,BLINK_TIME_PERIOD);                  

                    if(testing_buttons[4]==1) if(button_test(board->Aceptar,DEBOUNCE_TIME,ACEPTAR_)){
                        reg_time = (watch_time_saved[0]*10) + watch_time_saved[1];
                        setting_up_flag=true;
                        state = set_up_alarm_hour;  
                    }
                    if(testing_buttons[5]==1) if(button_test(board->Cancelar,DEBOUNCE_TIME,CANCELAR_)){
                        state = show_watch_time;
                        setting_up_flag=false;
                    } 
                    if(testing_buttons[3]==1) if(button_test(board->F4,DEBOUNCE_TIME,F4_)) count_status=INC_COUNT;
                    if(testing_buttons[2]==1) if(button_test(board->F3,DEBOUNCE_TIME,F3_)) count_status=DEC_COUNT;  
                    if(wdt) {               
                        state = show_watch_time;
                        setting_up_flag=false;
                        wdt=false;
                        time=0;                                              
                    }

                break;

            case set_up_alarm_hour:

                    decimal_to_seg(count_status,HOURS_SELECTED);
                    blink_display(ALL_DOT_ON,HOURS_OFF,BLINK_TIME_PERIOD); 
                    
                    if(testing_buttons[4l]==1) if(button_test(board->Aceptar,DEBOUNCE_TIME,ACEPTAR_)){
                        SetUpAlarm(watch,watch_time_saved,sizeof(watch_time_saved));
                        GetAlarmTime(watch,watch_time_alarm,sizeof(watch_time_alarm));
                        state = show_watch_time;
                        setting_up_flag=false;
                    }
                    if(testing_buttons[5]==1) if(button_test(board->Cancelar,DEBOUNCE_TIME,CANCELAR_)){
                        state = show_watch_time;
                        setting_up_flag=false;                        
                    }
                    if(testing_buttons[3]==1) if(button_test(board->F4,DEBOUNCE_TIME,F4_)) count_status=INC_COUNT;
                    if(testing_buttons[2]==1) if(button_test(board->F3,DEBOUNCE_TIME,F3_)) count_status=DEC_COUNT;
                    if(wdt) {               
                        state = show_watch_time;
                        setting_up_flag=false;
                        wdt=false;
                        time=0;                                              
                    }

                break;

            default:
                break;
            }
        }

    }
}

//---------------------------------------------Rutina de interrupción-------------------------------------------//

void SysTick_Handler(void){

    inc_time=true;

    if(time<30000)  time++; //30000 -> 30 segundos
    if(time>=30000) {       
        time=0;
        wdt=true;           //watch dog timer
    }
    
    if(setting_up_flag){    //rutina en caso de estar en estado de configuracion
        DisplayWriteBCD(board->display,(uint8_t[]){watch_time_new[3],watch_time_new[2],watch_time_new[1],watch_time_new[0]},4,dot);
        copy_paste_watch_time(false);   //se recupera el tiempo guardado antes de ser borrado
    }
    else{                   //rutina en caso de estar en estado de muestra de tiempo
        DisplayWriteBCD(board->display,(uint8_t[]){watch_time[3],watch_time[2],watch_time[1],watch_time[0]},4,dot); 
        GetTime(watch,watch_time,sizeof(watch_time));
    }
    RefreshTime(watch);
    DisplayRefresh(board->display); 

}

//----------------------------------------------Mis Funciones----------------------------------------------------//

void blink_display(uint8_t _dot, uint8_t displays_off, unsigned int blink_timer_f){

    if(blink_timer>0) blink_timer--;
    else blink_timer = blink_timer_f;  

    if(blink_timer>=blink_timer_f/2){    
        if(AlarmStatus(watch) && (state!=set_up_alarm_minute) && (state!=set_up_alarm_hour)) dot = DOT_0Y2_ON; //en caso que la alarma este activada 
        else dot=_dot;
    }
    else{
        
        copy_paste_watch_time(true);         //se guarda valor de tiempo antes de ser borrado

        if(displays_off == ALL_DISPLAY_OFF) for(int i=0; i<4; i++)  {
            if(setting_up_flag)watch_time_new[i] = ONE_DISPLAY_OFF;
        }
        if(displays_off == HOURS_OFF) {
            if(setting_up_flag)watch_time_new[0] = ONE_DISPLAY_OFF;
            if(setting_up_flag)watch_time_new[1] = ONE_DISPLAY_OFF;
        }
        if(displays_off == MINUTES_OFF) {
            if(setting_up_flag)watch_time_new[2] = ONE_DISPLAY_OFF;
            if(setting_up_flag)watch_time_new[3] = ONE_DISPLAY_OFF;
        } 

        if(AlarmStatus(watch) && (state==show_watch_time))
            dot = DOT_0_ON;    
        else
            dot= ALL_DOT_OFF;
    }

}

void decimal_to_seg (int count_state, int display_select){
    
    uint8_t max = 59;
    uint8_t display1 = 3;                       
    uint8_t display2 = 2;

    if(display_select==MINUTES_SELECTED){       
        max=59;
        display1=3;                             //unidad minutos
        display2=2;                             //decena minutos
    }
    if(display_select==HOURS_SELECTED){
        max=23;
        display1=1;                             //unidad hora
        display2=0;                             //decena hora
    }

    if(count_state==INC_COUNT) reg_time++;      //suma registro de configuracion de nuevo tiempo 
    if(count_state==DEC_COUNT) reg_time--;      //resta registro de configuracion de nuevo tiempo 

    if(reg_time<0)reg_time=max;                 //control de cuenta
    if(reg_time>max) reg_time=0;
    watch_time_new[display1]=reg_time%10;                               //unidades al display correspondiente
    watch_time_new[display2]=(reg_time - watch_time_new[display1])/10;  //decenas al display correspondiente
    count_status=0;                                                     //se reinicia registro de control de cuenta

}

bool button_test (digital_input_t button , unsigned int timer, unsigned int button_test){

    bool flag=false;                                                    //bandera de retorno
 
    if(DigitalInputState(button)){                                      //se testea pulsador
        if(new_button_tested){                                          //se verifica si se esta testeando un nuevo pulsador o sigue en testeo algun pulsador en particular
            for(int index=0; index<6; index++){                         
                if(button_test==index)   testing_buttons[index]=1;      //1 en la posicion del array que corresponde al pulsador que se encuentra testeando
                else                     testing_buttons[index]=0;      //0 para los demás
            }
            pressed_timer = timer;                                      //se define tiempo de testeo
            new_button_tested=false;                                    //bandera que indica que se encuentra testeando un pulsador en particular 
        }
        pressed_timer--;                                                //descuento de registro de tiempo
    }
    else{
        pressed_timer = timer;                                          //no se detecto pulsacion alguna
        new_button_tested=true;                                         //bandera que indica que se definira nuevo pulsador a testear
        for(int index=0; index<6; index++)  testing_buttons[index]=1;   //todos los pulsadores disponibles para ser testeados
    }  

    if(pressed_timer==0){                                               //se completo el tiempo de testeo
        flag=true;                                                      
        pressed_timer = timer; 
        for(int index=0; index<6; index++)  testing_buttons[index]=1;
        wdt=false;                                                      //desactivar watch dog timer
        time=0;                                                            
    }
    else    flag=false;

    return flag; 

}

void copy_paste_watch_time (bool copy_paste){

    if(copy_paste){                                                 //watch_time_saved = watch_time_new
        for(int index=0;index<sizeof(watch_time_saved);index++){
            watch_time_saved[index] = watch_time_new[index];
        }
    }
    if(!copy_paste){                                                //watch_time_new = watch_time_saved
        for(int index=0;index<sizeof(watch_time_new);index++){
            watch_time_new[index] = watch_time_saved[index];
        }
    }

}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */