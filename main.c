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
#define boton    PORTBbits.RB0
#define ledVerde PORTBbits.RB1
#define ledRojo  PORTBbits.RB2

const int tVerde = 500; // Delay para el led verde
const int tRojo = 200; // Delay para el led rojo

// Funcion de interrupcion
void __interrupt() interrupcion(void)
{
    if(INTCONbits.INTF)
    {
        for(int i = 0; i < 5; i++)
        {
            ledRojo = 1;
            __delay_ms(tRojo);
            ledRojo = 0;
            __delay_ms(tRojo);
        }
        INTCONbits.INTF = 0; // Se asigna 0 a la bandera de interrupcion
    }
}

void main(void)
{
    TRISB = 0x01;
    ANSELH = 0x00;

    OPTION_REGbits.INTEDG = 1; // Activar interrupcion en flanco de subida
    INTCONbits.GIE = 1; // Habilitar interrupcion global
    INTCONbits.INTE = 1; // Habilitar interrupcion externa por pin
    INTCONbits.INTF = 0; // Resetear bandera de interrupcion

    while(1)
    {
        ledVerde = 1;
        __delay_ms(tVerde);
        ledVerde = 0;
        __delay_ms(tVerde);
    }
}

