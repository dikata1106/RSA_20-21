#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <stdint.h>

#define PIN_LED 4
#define PIN_PULSADOR 5

// Inicializa GPIO23 (BCM) 4 (wPi) de salida y GPIO24 (BCM) 5 (wPi) de entrada
void inicializar() {
    // system("sudo echo 4 > /sys/class/gpio/export");
    // system("sudo echo 5 > /sys/class/gpio/export");
    // system("sudo echo out > /sys/class/gpio/gpio4/direction");
    // system("sudo echo in > /sys/class/gpio/gpio5/direction");
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_PULSADOR, INPUT);
}

int main(int argc, char**argv) {

    int encendido = 0, pulsado = 0, pulsadoant = 0;

    wiringPiSetup();
    inicializar();
    digitalWrite(PIN_LED, LOW);
    
    while (1) {
        pulsado = digitalRead(PIN_PULSADOR);                            // Lee estado del pulsador
        printf("%d, %d\n\r", pulsado, pulsadoant);                      // feedback debugger
        std::cout << std::flush;
        if (encendido == 0 && pulsado == 0 && pulsadoant == 1) {        // Si pulsado y led apagado
            digitalWrite(PIN_LED, HIGH);                                // Encender led
            encendido = 1;                                              // encendido = !encendido // cambio estado
            delay(100);                                                 // espera 0.1s para rebotes
        } else if (encendido == 1 && pulsado == 0 && pulsadoant == 1) { // Si pulsado y led encendido
            digitalWrite(PIN_LED, LOW);                                 // Apagar led
            encendido = 0;                                              // encendido = !encendido // conmutar estado
            delay(100);                                                 // espera 0.1s para rebotes
        }
        pulsadoant = pulsado;                                           // Guardar estado anterior
    }
    return 0;
}

/*
int veces = 0;

void blink(int veces) {
    int x;
    wiringPiSetup();
    pinMode(7, OUTPUT);
    for (int x = 1; x < veces + 1; x += 1) {

        std::cout << std::endl << "Encendido: " << x << "\r" << std::endl;
        digitalWrite(7, HIGH);
        delayMicroseconds(500000);
        std::cout << std::endl << "Apagado: " << x << "\r" << std::endl;
        digitalWrite(7, LOW);
        delay(500);
    }
}

int main() {
    blink(100);
    return 0;
}
*/