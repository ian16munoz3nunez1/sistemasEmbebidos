#include <xc.h>
#include <pic16f887.h>

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

#define _XTAL_FREQ 4000000
#define a0 PORTAbits.RA0
#define a1 PORTAbits.RA1
#define b0 PORTAbits.RA2
#define b1 PORTAbits.RA3
#define m  PORTAbits.RA4
#define salida PORTB

unsigned char numeros[] = {
    0b11111100, //0
    0b01100000, //1
    0b11011010, //2
    0b11110010, //3
    0b01100110, //4
    0b10110110, //5
    0b10111110 //6
    //abcdefg.
};

int s0, c0, s1, c1, valor;

void main(void)
{
    TRISA = 0x1F;
    TRISB = 0x00;

    ANSEL = 0x00;

    while(1)
    {
        if(m)
        {
            s0 = a0^b0;
            c0 = ~a0&b0;
            s1 = c0^a1^b1;
            c1 = c0&~a1 | b1&~(c0^a1);
            valor = s0*1 + s1*2 + c1*4;
            if(valor > 3)
            {
                valor = ~valor - 0b11111000;
                valor = 0b0001 + valor;
                salida = numeros[valor] + 1;
            }
            else
                salida = numeros[valor];
        }
        else
        {
            s0 = a0^b0;
            c0 = a0&b0;
            s1 = c0^a1^b1;
            c1 = c0&a1 | b1&(c0^a1);
            valor = s0*1 + s1*2 + c1*4;
            salida = numeros[valor];
        }
    }
}

