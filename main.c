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

int t = 300;

void main(void)
{
    TRISB = 0x00;

    while(1)
    {
        for(int i = 0; i <= 31; i++)
        {
            salida = i;
            __delay_ms(t);
        }
    }
}

