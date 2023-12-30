#include "18F4550.h"                //Incluimos la librería del PIC  y Habilitamos Conversion ADC=10
#DEVICE ADC=10

#include <ctype.h>

#FUSES HS,NOPROTECT,NOLVP,NOWDT,NOPUT,BROWNOUT, WDT16384       //Configuración Perro Guardián para 1min.


#use delay(clock=2000000)              //Frecuencia de trabajo de 2MHz y Configuración Puerto D (Sensores Ultrasonidos).
#USE standard_io(D)

#include "LCDeasy.c"
#define LCD_DATO 1
#define LCD_COMANDO 0               //comandos para lcd
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02


int32 fosc = 2000000;

//Definimos el nombre para los pulsos echo y triigger y se asocian a sus correspondientes pines.
#define P_ECHO1 PIN_D1
#define P_TRIG1 PIN_D0

#define P_ECHO2 PIN_D3
#define P_TRIG2 PIN_D2

#define P_ALARMA PIN_C5

#define P_FRENO PIN_C6

#define INTERMITENTES PIN_C7

#define P_MOTOR PIN_C0

#include <HCSR04_1.c>
#include <HCSR04_2.c>         //Librerias de los sensores






float distancia_delantera = 0, distancia_trasera = 0;

void inicializar() {
    output_C(0);
    output_B(0);
    HCSR04_1_init();
    HCSR04_2_init();
    setup_adc(adc_clock_div_2);
    set_adc_channel(0);
    delay_us(10);
    lcd_init();
    output_low(INTERMITENTES);
}


void controlarMotores() {
    if (distancia_delantera < 30 && distancia_trasera > 30) { //Si hay peligro de colisión delantera
        output_low(P_MOTOR);
        output_high(P_FRENO);
        output_high(P_ALARMA);
        int i;
        lcd_send_byte(LCD_COMANDO, LCD_CLEAR);
        printf(lcd_putc, "Posible colision \ndelantera!");
        delay_ms(1000);
        for (i=0;i<6;i++){                  // Bucle para encender los intermitentes
        output_high(INTERMITENTES);
        delay_ms(250);
        output_low(INTERMITENTES);
        delay_ms(250);
        }
    } else if (distancia_trasera < 30 && distancia_delantera > 30) { // Si hay peligro de colisión trasera
        output_high(P_MOTOR);
        output_low(P_FRENO);
        output_high(P_ALARMA);
        lcd_send_byte(LCD_COMANDO, LCD_CLEAR);
        printf(lcd_putc, "Posible colision \ntrasera!");
        delay_ms(1000);
    } else if (distancia_delantera < 30 && distancia_trasera < 30) { // Si hay peligro de colisión trasera y delantera
        output_low(P_MOTOR);
        output_high(P_FRENO);
        output_high(P_ALARMA);
        lcd_send_byte(LCD_COMANDO, LCD_CLEAR);
        printf(lcd_putc, "Peligro por \nretencion!");
        delay_ms(1000);
        int i;
        for (i=0;i<6;i++){
        output_high(INTERMITENTES);
        delay_ms(250);
        output_low(INTERMITENTES);
        delay_ms(250);
        }
    } else {                                // Si no hay peligro de colisión
        output_high(P_MOTOR);
        output_low(P_FRENO);
        output_low(P_ALARMA);
    }
}

void mostrarDistancias() {
    lcd_send_byte(LCD_COMANDO, LCD_CLEAR);
    printf(lcd_putc, "Sensor Delantero\nDist: %0.2f m", distancia_delantera);
    delay_ms(1000);
    lcd_send_byte(LCD_COMANDO, LCD_CLEAR);
    printf(lcd_putc, "Sensor Trasero\nDist: %0.2f m", distancia_trasera);
    delay_ms(1000);
}

void main() {
    inicializar();

    while (true) {
        distancia_delantera = HCSR04_1_get_distance();
        distancia_trasera = HCSR04_2_get_distance();
        controlarMotores();
        mostrarDistancias();}
    }

