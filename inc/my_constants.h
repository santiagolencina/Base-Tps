// SE DEFINEN ESTADOS DE LA MAQUINA

#define init 0                      //ESTADO INICIAL
#define set_up_hour 1               //SETEAR HORA DE RELOJ
#define set_up_minute 2             //SETEAR MINUTOS DE RELOJ
#define show_watch_time 3           //MOSTRAR HORA
#define set_up_alarm_hour 4         //SETEAR HORA DE ALARMA
#define set_up_alarm_minute 5       //SETEAR MINUTOS DE ALARMA

// CONSTANTES PARA MANEJO DE DISPLAY

#define ALL_DOT_OFF 11              //PUNTO DECIMAL APAGADO
#define ALL_DOT_ON  12              //PUNTO DECIMAL ENCENDIDO
#define DOT_0Y2_ON  13              //PUNTO DECIMAL 0 Y 2 ENCENDIDO
#define DOT_0_ON  0                 //PUNTO DECIMAL 0 ENCENDIDO
#define DOT_1_ON  1                 //PUNTO DECIMAL 1 ENCENDIDO
#define DOT_2_ON  2                 //PUNTO DECIMAL 2 ENCENDIDO
#define DOT_3_ON  3                 //PUNTO DECIMAL 3 ENCENDIDO   
#define ONE_DISPLAY_OFF 10          //UN DISPLAY COMPLETO DEL RELOJ APAGADO
#define MINUTES_OFF 20              //APAGAR DISPLAYS DE MINUTOS
#define HOURS_OFF 21                //APAGAR DISPLAYS DE HORAS
#define ALL_DISPLAY_OFF 22          //APAGAR TODOS LOS DISPLAYS
#define All_DISPLAY_ON 23           //ENCENDIDO TODOS LOS DISPLAYS
#define MINUTES_SELECTED 24         //SE SELECCIONO LOS DISPLAY DE MINUTOS 
#define HOURS_SELECTED 25           //SE SELECCIONO LOS DISPLAY DE HORA
#define INC_COUNT 26                //SE INCREMENTO EN UNO LA CUENTA
#define DEC_COUNT 27                //SE DECREMENTO EN UNO LA CUENTA

// CONSTANTES DE TIEMPO

#define F1_TIMER 3000               //TEMPORIZADO DE 3 SEGUNDOS PARA PULSADOR F1
#define F2_TIMER 3000               //TEMPORIZADO DE 3 SEGUNDOS PARA PULSADOR F2
#define DEBOUNCE_TIME 200           //ANTIRREBOTE DE DEBOUNCE TIME (ms)
#define BLINK_TIME_PERIOD 1000      //TIEMPO DE UN CICLO DE PARPADEO

// PULSADORES

#define F1_ 0                      //SE DESEA TESTEAR F1
#define F2_ 1                      //SE DESEA TESTEAR F2
#define F3_ 2                      //SE DESEA TESTEAR F3
#define F4_ 3                      //SE DESEA TESTEAR F4
#define ACEPTAR_ 4                 //SE DESEA TESTEAR ACEPTAR
#define CANCELAR_ 5                //SE DESEA TESTEAR CANCELAR