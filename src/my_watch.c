/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Lencina Martínez Luis Santiago
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

//--------------------------------------------------------------------------------//

#include "my_watch.h"
#include <string.h>

//--------------------------------------------------------------------------------//

struct my_watch_s {

    uint8_t current_time[6];
    uint8_t alarm[6]; 
    uint8_t snooze_time;
    uint32_t clock_sec;    
    uint32_t clock_current; 
    bool time_ok;
    bool alarm_is_on;
    bool alarm_is_activated;

};

bool is_time_ok(const uint8_t * time);
void repeat_sec(uint8_t * current_time, my_watch_t my_watch);

//--------------------------------------------------------------------------------//

my_watch_t CreateWatch(uint32_t clock_s) {
    static struct my_watch_s self[1];
    memset(self, 0, sizeof(self));
    self->clock_sec=clock_s;
    return self;
}

bool SetUpTime(my_watch_t my_watch, const uint8_t * time, uint32_t size){
    bool select = true;

    if (!is_time_ok(time)) {
        memcpy(my_watch->current_time, time, size);
        my_watch->time_ok = true;
    } else {
        select = false;
    }
    return select;    
}

bool GetTime(my_watch_t my_watch, uint8_t * time, uint8_t size){
    memcpy(time, my_watch->current_time, size);
    return my_watch->time_ok;    
}

void RefreshTime(my_watch_t my_watch){
    uint8_t time[6];

    my_watch->clock_current++;

    if (my_watch->clock_current == my_watch->clock_sec) {
        GetTime(my_watch, time, 6);
        
        repeat_sec(time,my_watch);

        SetUpTime(my_watch, time, 6);

        my_watch->clock_current = 0;

        if (my_watch->alarm_is_on) { 
            AlarmRinging(my_watch);
        }
    }   
}

//--------------------------------------------------------------------------------//

void SetUpClock(my_watch_t my_watch){
    my_watch->clock_current= 0;
}

void IncreaseClock(my_watch_t my_watch){ 
    my_watch->clock_current++;
}

//--------------------------------------------------------------------------------//


bool SetUpAlarm(my_watch_t my_watch, const uint8_t * time, uint8_t size){

    bool retornar=false;
    if(time[5]>9||time[4]>5||time[3]>9||time[2]>5)retornar=true;
    if(time[0]>1&&time[1]>3)retornar=true;
    if(time[0]>2)retornar=true;
    if(time[1]>9)retornar=true;

    if(!retornar){
        memcpy(my_watch->alarm, time, size);
        my_watch->alarm_is_on = true;
    }

    return retornar;
}

bool GetAlarmTime(my_watch_t my_watch, uint8_t * time, uint32_t size){
    memcpy(time, my_watch->alarm, size);
    return my_watch->alarm_is_on;
}

bool EnableAlarm(my_watch_t my_watch, bool estado){
    my_watch->alarm_is_on = estado;
    return my_watch->alarm_is_on;
}

bool AlarmStatus(my_watch_t my_watch){
        return my_watch->alarm_is_on;
}

bool SnoozeAlarm(my_watch_t my_watch, uint8_t no_active){
    my_watch->snooze_time = no_active;
    return my_watch->snooze_time;    
}

bool AlarmRinging(my_watch_t my_watch) {
    uint8_t time[6];
    uint8_t alarm[6];

    memcpy(time, my_watch->current_time, 6);
    memcpy(alarm, my_watch->alarm, 6);

    if (!memcmp(time, alarm, 6)){
        my_watch->alarm_is_activated = true;
    }

    return ((my_watch->alarm_is_activated) && (!my_watch->snooze_time)&&(my_watch->alarm_is_on));
}

//--------------------------------------------------------------------------------//

bool is_time_ok(const uint8_t * time){
    bool retornar=false;
    if(time[5]>9||time[4]>5||time[3]>9||time[2]>5)retornar=true;
    if(time[0]>1&&time[1]>3)retornar=true;
    if(time[0]>2)retornar=true;
    if(time[1]>9)retornar=true;
    return retornar;
}

void repeat_sec(uint8_t * current_time, my_watch_t my_watch) {

    current_time[5]++;
                             
    if (current_time[5]>9){
        current_time[5]=0;
        current_time[4]++;
    }
    if (current_time[4]>5){
        current_time[4]=0;
        current_time[3]++;
    }
    if (current_time[3]>9){
        current_time[3]=0;
        current_time[2]++;
    }
    if (current_time[2]>5){
        current_time[2]=0;
        current_time[1]++;
    }
    if (current_time[1]>9){
        current_time[1]=0;
        current_time[0]++;
    }
    if ((current_time[0]>=2)&&(current_time[1]>=4)){
        current_time[0]=0;
        current_time[1]=0;
    }
    if (my_watch->snooze_time > 0) {
        my_watch->snooze_time--;
    }
    
}