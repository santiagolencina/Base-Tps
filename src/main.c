#include <stdio.h>
#include "calculadora.h"
 
int suma(int a, int b) {
    return a + b;
}

int resta(int a, int b) {
    return a - b;
}

int multiplicacion(int a, int b) {
    return a * b;
}

int division(int a, int b) {
    if (b != 0) {
        return (float)a / b;
    } else {
        printf("Error: No se puede dividir entre cero.\n");
        return 0;
    }
}


int main() {
    int resultado;
    char cadena[20];

    calculadora_t calculadora = CrearCalculadora();
    resultado=0;
    AgregarOperacion(calculadora,'+',suma);
    AgregarOperacion(calculadora,'-',resta);
    AgregarOperacion(calculadora,'*',multiplicacion);
    AgregarOperacion(calculadora,'/',division);//devuelve un numero entero, asi que si divido 2/4 por ej devolvera 0
    
    while(1){ 

        printf("Formato (Numero 1 (+-*/) Numero 2)\n\nSi desea finalizar el programa escriba 'Salir'\n\nIntroduce la operación:");
        scanf("%s", cadena);

        if (strcmp(cadena, "Salir") == 0) {
            printf("Programa Finalizado.\n");
            break;
        }

        resultado=Calcular(calculadora,cadena);
        printf("resultado %i\r\n\n",resultado);
    }
    return 0;
}