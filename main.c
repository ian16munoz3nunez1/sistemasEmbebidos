#include <xc.h>
#include <pic16f887.h>

#define _XTAL_FREQ 4000000 // Configuracion de la frecuencia en 4MHz
#define motor PORTB // Definicion del puerto B como 'motor'

// Configuracion del pic
#pragma config FOSC=INTRC_NOCLKOUT
#pragma config WDTE=OFF
#pragma config PWRTE=OFF
#pragma config MCLRE=OFF
#pragma config CP=OFF
#pragma config CPD=OFF
#pragma config BOREN=OFF
#pragma config IESO=OFF
#pragma config FCMEN=OFF
#pragma config LVP=OFF
#pragma config BOR4V=BOR40V
#pragma config WRT=OFF

// Arreglo para un paso a la vez
unsigned char unPaso[] = {
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001
};

// Arreglo para dos pasos a la vez
unsigned char dosPasos[] = {
    0b00001100,
    0b00000110,
    0b00000011,
    0b00001001
};

// Arreglo para la configuracion a medio paso del motor
unsigned char medioPaso[] = {
    0b00001000,
    0b00001100,
    0b00000100,
    0b00000110,
    0b00000010,
    0b00000011,
    0b00000001,
    0b00001001
};

int t = 5; // Tiempo de espera entre cada paso

void main(void)
{
    TRISB = 0x00; // Configuracion de los pines del puerto B como salidas

    while(1)
    {
        for(int i = 0; i < 4; i++)
        {
            motor = dosPasos[i]; // Paso actual del motor
            __delay_ms(t); // Espera de un cierto periodo de tiempo
        }
    }
}

