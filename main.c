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
#define led PORTBbits.RB0

int t = 1000;

void main(void)
{
    TRISB = 0x00;

    while(1)
    {
        led = 1;
        __delay_ms(t);
        led = 0;
        __delay_ms(t);
    }
}

