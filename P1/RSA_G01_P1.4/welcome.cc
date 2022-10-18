#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <stdint.h>

#define PIN_PULSADOR 5

int contador = 0;
int pulsado = 0, pulsadoant=0;

// Creacion hilo 1
PI_THREAD(thread1) {
    piHiPri(60); // establece prioridd a 60
    while (true) {
        piLock(0); // bloquea
        contador++; // incrementa contador
        piUnlock(0); // desbloquea
        std::cout << std::endl << "thr: 1, cont: " << contador << "\r" << std::endl;
        delay(1000); // espera 1s
    }
}

// Creacion hilo 2
PI_THREAD(thread2) {
    piHiPri(30); // establece prioridad a 30
    while (true) {
        piLock(0); // bloquea
        contador++; // incrementa contador
        piUnlock(0); // desbloquea
        std::cout << std::endl << "thr: 2, cont: " << contador << "\r" << std::endl;
        delay(700); // Espera 0.7s
    }
}

void esperaInterrupcion(void) {
    // Hace dos lecturas del pulsador para evitar glitches
    pulsadoant = digitalRead(5);
    delay(10);
    pulsado = digitalRead(5);
    // Si se define como pulsado, resetea contador
    if (pulsado == 0 && pulsadoant == 0) {
        contador = 0;
        std::cout << std::endl << "Pulsador pulsado; cont = " << contador << "\r" << std::endl;
    }
    pulsado = 1;
}

int main(void) {

    wiringPiSetup();
    pinMode(PIN_PULSADOR, INPUT);
    //creación de los threads
    printf("Main: creando threads\n");
    int r = piThreadCreate(thread1);
    int v = piThreadCreate(thread2);
    if ((r != 0) || (v != 0)) {
        printf("Error al crear un thread!\n");
        return 1;
    }
    /*Activa la espera por interrupción*/
    wiringPiISR(PIN_PULSADOR, INT_EDGE_BOTH, &esperaInterrupcion);
    while(1);   // ejecutando tareas cada hilo lo suyo
    return 0;
}

