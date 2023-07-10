// Ian Mu;oz Nu;ez

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

// Arreglo para un paso a la vez en sentido horario
unsigned char unPasoCW[] = {
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001
};
// Arreglo para un paso a la vez en sentido antihorario
unsigned char unPasoCCW[] = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000
};

// Arreglo para dos pasos a la vez en sentido horario
unsigned char dosPasosCW[] = {
    0b00001100,
    0b00000110,
    0b00000011,
    0b00001001
};
// Arreglo para dos pasos a la vez en sentido antihorario
unsigned char dosPasosCCW[] = {
    0b00000011,
    0b00000110,
    0b00001100,
    0b00001001
};

// Arreglo para la configuracion a medio paso del motor en sentido horario
unsigned char medioPasoCW[] = {
    0b00001000,
    0b00001100,
    0b00000100,
    0b00000110,
    0b00000010,
    0b00000011,
    0b00000001,
    0b00001001
};
// Arreglo para la configuracion a medio paso del motor en sentido antihorario
unsigned char medioPasoCCW[] = {
    0b00000001,
    0b00000011,
    0b00000010,
    0b00000110,
    0b00000100,
    0b00001100,
    0b00001000,
    0b00001001
};

int analogRead(); // Prototipo de la funcion para lecturas analogicas
int t = 2; // Tiempo de espera entre cada paso

void main(void)
{
    TRISB = 0x00; // Configuracion de los pines del puerto B como salidas
    ANSEL = 0x01; // Activacion de la lectura analogica por el pin RA0
    ADCON1 = 0x80; // Lectura analogica justificada a la derecha

    int i=0; // Variables para los pasos del motor
    int pasos=4; // Numero de pasos para llegar a un angulo de 5.625: 4/8
    // Angulo del motor, angulo deseado, error entre el angulo actual y deseado
    float angle=0, valor, error;

    while(1)
    {
        valor = analogRead()*0.3519; // Valor leido multiplicado por 360/1023
        error = valor-angle; // Error calculado

        if(error > 3)
        {
            __delay_ms(t); // Espera de t milisegundos
            motor = dosPasosCW[i]; // Paso siguiente en sentido horario
            angle += 0.1757; // Incrementa el valor del angulo
            i++; // Incrementa el iterador de pasos
        }

        if(error < -3)
        {
            __delay_ms(t); // Espera de t milisegundos
            motor = dosPasosCCW[i]; // Paso siguiente en sentido antihorario
            angle -= 0.1757; // Decrementa el valor del angulo
            i++; // Incrementa el iterador de pasos
        }

        if(i == pasos)
        {
            i = 0; // Si el iterador de pasos llega al limite, inicia de nuevo
        }
    }
}

int analogRead()
{
    ADCON0bits.ADCS = 0b01; // Reloj de conversion / Velocidad de conversion
    ADCON0bits.CHS = 0; // Canal analogico para la lectura
    ADCON0bits.ADON = 1; // Activacion de la lectura analogica-digital

    ADCON0bits.GO = 1; // Encendido del conversor
    while(ADCON0bits.GO == 1){NOP();} // Mientras el conversor este encendido, no hay operacion
    int valor = (ADRESH<<8)+ADRESL; // Valor digital obtenido

    return valor;
}

