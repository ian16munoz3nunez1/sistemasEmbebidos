// Ian Mu;oz Nu;ez

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
#define asc PORTAbits.RA0
#define desc PORTAbits.RA1
#define salida PORTB

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
    0b11100110 //9
    //abcdefg.
};

void main(void)
{
    int i=0;

    TRISA = 0x03;
    TRISB = 0x00;

    ANSEL = 0x00;

    while(1)
    {
        if(asc)
        {
            __delay_ms(200);
            while(asc){NOP();}
            i++;
        }

        if(desc)
        {
            __delay_ms(200);
            while(desc){NOP();}
            i--;
        }

        if(i > 9) i = 0;
        if(i < 0) i = 9;

        salida = numeros[i];
    }
}

