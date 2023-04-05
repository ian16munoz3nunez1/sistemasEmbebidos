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

// unsigned char numeros[] = {
//     0xFC, //0
//     0x60, //1
//     0xDA, //2
//     0xF2, //3
//     0x66, //4
//     0xB6, //5
//     0xBE, //6
//     0xE0, //7
//     0xFE, //8
//     0xE6 //9
// };

int t = 1000;

void main(void)
{
    TRISB = 0x00;

    while(1)
    {
        for(int i = 0; i < 10; i++)
        {
            salida = numeros[i];
            __delay_ms(t);
        }
    }
}

