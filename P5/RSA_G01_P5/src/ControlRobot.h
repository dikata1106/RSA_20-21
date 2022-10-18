// Control Robot.h
#pragma once

#include <iostream>
#include "IRobotConnection.h"
#define INICIAL 1
#define SIGUE 2
#define BUSCA 3
#define AVANZAR 4
#define POSICIONAR 5
#define SALIR 6
#define GIRA90D 7
#define GIRA90I 8

// Estados para los motores
#define GIRAR_DERECHA 0
#define GIRAR_IZQUIERDA 1
#define RECTO 2
#define PARADO 3

#define DUCT_TAPE_L(value) \
    (value < 600)  // 344 - 1195               //suelo 680-830
#define DUCT_TAPE_FL(value) \
    (value < 1000)  // 784 - 1693 ant=1100   //suelo 800-1000
#define DUCT_TAPE_FR(value) \
    (value < 320)  // 228 - 724  ant=350    //suelo 430-580
#define DUCT_TAPE_R(value) \
    (value < 260)  // 202 - 920  fuera=120  //suelo//600 - 700

#define NORTE 1
#define SUR 2
#define ESTE 3
#define OESTE 4

/**
 *	 Definición de la clase ControlRobot
 */
class ControlRobot {
   private:
    IRobotConnection *robot;

    struct Sensores_iCreate {
        // variables para almacenar información del
        // sensor de acantilado frontal izquierdo
        unsigned int front_left;
        unsigned int front_right;
        unsigned int left;
        unsigned int right;
        bool fl;
        bool lat;
    };
    struct Sensores_iCreate sensores;

    struct Actuadores_iCreate {
        // variables para el comando Drive direct
        int vel_der;
        int vel_izq;
        // variables para el comando Drive
        int velocidad;
        int giro;
    };
    struct Actuadores_iCreate actuadores;

    char estadogen;
    char estado_actual;
    char estado_anterior;
    char estado_llamada;
    char direccion;
    char direccion_actual;
    char motores;
    bool encaminado;

   public:
    ControlRobot(void);
    ~ControlRobot(void);

    void inicializacion(char, char, char);
    bool condicionSalida();
    void leerSensores();
    void logicaEstados();
    void moverActuadores();
    void imprimirInfo();
    void finalizacion();
};
