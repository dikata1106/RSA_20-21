#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <stdint.h>

#define PIN_LED 4

int main(int argc, char**argv) {
    wiringPiSetup();                // Configuracion wiringPi
    pinMode(PIN_LED, OUTPUT);       // Configura GPIO23 (BCM) 4 (wPi) de salida
    while (1){
        digitalWrite(PIN_LED, HIGH);// Encender led
        delay(1000);                // Espera 1s
        digitalWrite(PIN_LED, LOW); // Apagar led
        delay(1000);                // Espera 1s
        
        // Otra forma:
        // digitalWrite(PIN_LED, !digitalRead(PIN_LED));
        // delay(1000);
    }
    return 0;
}
