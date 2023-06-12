#include <xc.h>
#include <pic16f887.h>

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

#define _XTAL_FREQ 4000000 // Configuracion de la frecuencia en 4MHz
#define decimal PORTB // Definicion del puerto B con el nombre 'decimal'
#define unidad PORTC // Definicion del puerto C con el nombre 'unidad'

// Arreglo de caracteres para mostrar los numeros
unsigned char numeros[] = {
    0b11111100, //0
    0b01100000, //1
    0b11011010, //2
    0b11110010, //3
    0b01100110, //4
    0b10110110, //5
    0b10111110, //6
    0b11100000, //7
    0b11111110, //8
    0b11100110
    //abcdefg.
};

int analogRead(int); // Prototipo de la funcion para lecuras analogicas

void main(void)
{
    TRISB = 0x00; // Configuracion de los pines del puerto B como salidas
    TRISC = 0x00; // Configuracion de los pines del puerto C como salidas
    ANSEL = 0xFF; // Activacion de las lecturas analogicas

    while(1)
    {
        int valor = analogRead(0); // Lectura analogica desde el canal 0 (AN0/RA0)
        // Valor dividido entre 204 para dividir 1023 en 5 partes
        decimal = numeros[valor/204];
        // Modulo dividido entre 21 para dividir 204 en 10 partes
        unidad = numeros[(valor%204)/21];
    }
}

int analogRead(int canal)
{
    ADCON1 = 0x80; // Justificacion de lectura analogica a la derecha
    ADCON0bits.ADCS = 0b01; // Reloj de conversion/Velocidad de conversion
    ADCON0bits.CHS = canal; // Canal analogico para la lectura
    ADCON0bits.ADON = 1; // Activacion de la conversion analogica-digital

    ADCON0bits.GO = 1; // Encendido del conversor
    while(ADCON0bits.GO == 1){NOP();}
    int valor = (ADRESH<<8)+ADRESL; // Valor digital obtenido

    return valor;
}

