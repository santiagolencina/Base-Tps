#include "calculadora.h"

typedef struct operacion_s *operacion_t;

typedef struct operacion_s{

    char operador;
    funcion_t funcion;
    operacion_t siguiente;

}*operacion_t;

struct calculadora_s{

    operacion_t operaciones;

};

calculadora_t CrearCalculadora(void){

    calculadora_t puntero= malloc(sizeof(struct calculadora_s));
    
    if(puntero){
        memset(puntero,0,sizeof(struct calculadora_s));
    }
    
return puntero;
}



operacion_t BuscarOperacion(calculadora_t calculadora,char operador){
    operacion_t result=NULL;
    for(operacion_t actual=calculadora->operaciones;actual!=NULL;actual=actual->siguiente){
        if(actual->operador==operador) {
            result=actual; 
            break;
            }
    }
    return result;
}



bool AgregarOperacion(calculadora_t calculadora,char operador,funcion_t funcion){

    operacion_t operacion = malloc(sizeof(struct operacion_s));
    
    if((operacion)&& !BuscarOperacion(calculadora,operador)){
        operacion->operador=operador;
        operacion->funcion=funcion;
        operacion->siguiente=calculadora->operaciones;
        calculadora->operaciones=operacion;
    }
    return (operacion!=NULL);
}

int Calcular(calculadora_t calculadora,char *cadena){
    int a,b;
    char operador;
    int result=0;

    for(int indice=0;indice<strlen(cadena);indice++){
        if(cadena[indice]<'0'){
            operador=cadena[indice];
            a=atoi(cadena);
            b=atoi(cadena+indice+1);
            break;
        }
    }
    operacion_t operacion=BuscarOperacion(calculadora,operador);
    if(operacion){
        result=operacion->funcion(a,b);
    }
    return result;
}