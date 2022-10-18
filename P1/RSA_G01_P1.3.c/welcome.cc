#include <softPwm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>

#define PIN_LED 4
#define PIN_PULSADOR 5

// Modifica señal PWM con nuevo valor p2
void regular_led(int p2) {
    softPwmWrite(4, p2);
}

// Inicializa GPIO23 (BCM) 4 (wPi) de salida y GPIO24 (BCM) 5 (wPi) de entrada
// Crea PWM para el led con rango 0..100
void inicializar() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_PULSADOR, INPUT);
    softPwmCreate(PIN_LED, 0, 100);
}

int main(int argc, char** argv) {
    int encendido = 0, pulsado = 0, pulsadoant = 0, p2 = 0;

    wiringPiSetup();
    inicializar();
    regular_led(p2);  // Inicialmente led apagado

    while (1) {
        pulsado = digitalRead(PIN_PULSADOR);
        printf("%d, %d\n\r", pulsado, pulsadoant);
        std::cout << std::flush;
        if (encendido == 1) {     // Si led encendido
            if (p2 < 100) {       // Si no a maxima PWM
                p2 += 10;         // Aumentar PWM
                regular_led(p2);  // Regular con nueva PWM
                delay(500);       // Espera 0.5s
            }
            if (pulsado == 0 && pulsadoant == 1) {  // Si pulsador pulsado
                encendido = 0;                      // Cambiar a apagado
                std::cout << std::endl
                          << "Bajando: "
                          << "\r" << std::endl;
            }
        } else if (encendido == 0) {  // Si led apagado
            if (p2 > 0) {             // Si no min PWM
                p2 -= 10;             // Bajar PWM
                regular_led(p2);      // Regular con nueva PWM
                delay(1000);          // Espera 1s
            }
            if (pulsado == 0 && pulsadoant == 1) {  // Si pulsador apagado
                encendido = 1;                      // Cambiar a encendido
                std::cout << std::endl
                          << "Subiendo: "
                          << "\r" << std::endl;
            }
        }
        pulsadoant =
            pulsado;  // Guardar estado anterior el pulsador (como biestable D
    }
    return 0;
}