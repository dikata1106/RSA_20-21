// ControlRobot .cpp

#include "ControlRobot.h"
#include <iostream>

using namespace std;

// Estados de la lógica

/**
 *	Constructora objeto ControlRobot
 */
ControlRobot::ControlRobot(void) {
}

/**
 *	Destructora objeto ControlRobot
 */
ControlRobot::~ControlRobot(void) {
}

/**
 * 	Prepara la conexión IRobotConnection e inicializa todas
 *	las variables que necesitemos en el programa
 */
void ControlRobot::inicializacion(char estadogen, char dirobj, char diract) {
    int COM_port;
    char puerto[30];
    sprintf(puerto, "/dev/ttyUSB0");
    robot = new IRobotConnection(puerto);
    cout << "Connecting... ";
    robot->connect();
    cout << "Done!!\r" << endl;
    robot->start();  // Comando 128 start
    delay(500);      // Esperamos medio segundo a que cambie de modo
    robot->full();   // Comando 132 modo full
    delay(500);      // Esperamos medio segundo a que cambie de modo
    robot->leds(3, 90, 200);
    estado_actual = INICIAL;
    estado_llamada = estadogen;
    estado_anterior = INICIAL;
    direccion = dirobj;
    direccion_actual = diract;
    encaminado = FALSE;
    // motores = PARADO;
    cout << "El estado actual al inicializar:" << (int)estado_actual << "\r"
         << endl;
    cout << "El estado general al inicializar:" << (int)estado_llamada << "\r"
         << endl;
}

/**
 * 	Calcula si se han dado las condiciones necesarias para terminar el
 *programa return bool:
 *		- true para terminar
 *		- false para continuar al menos un ciclo más
 */
bool ControlRobot::condicionSalida() {
    if (estado_actual == SALIR) {
        return true;
    }
    return false;  // nos mantenemos siempre dentro del bucle
}

/**
 *	Obtiene y trata la información de los sensores relevantes al programa,
 *	para ello usa la struct Sensores_iCreate sensores;
 */
void ControlRobot::leerSensores() {
    sensores.left = robot->updateSensor(iRobotSensors::CLIFFLEFTSIGNAL);
    sensores.front_left =
        robot->updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
    sensores.front_right =
        robot->updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
    sensores.right = robot->updateSensor(iRobotSensors::CLIFFRIGHTSIGNAL);

    if (sensores.left > 4095)
        sensores.left = 4095;
    if (sensores.front_left > 4095)
        sensores.front_left = 4095;
    if (sensores.front_right > 4095)
        sensores.front_right = 4095;
    if (sensores.right > 4095)
        sensores.right = 4095;
    sensores.fl = (!DUCT_TAPE_FL(sensores.front_left) &&
                   !DUCT_TAPE_FR(sensores.front_right));
    sensores.lat = (DUCT_TAPE_L(sensores.left) || DUCT_TAPE_R(sensores.right));
}

/**
 *	Contiene la lógica del programa
 */
void ControlRobot::logicaEstados() {
    // Actualizamos los estados:
    // estado_anterior = estado_actual;

    switch (estado_llamada) {
        case AVANZAR:
            if (sensores.lat) {
                robot->driveDirect(100, 100);
                robot->waitDistance(60);
                estado_actual = SALIR;
            } else if (sensores.fl) {
                estado_actual = SIGUE;
            } else if (!sensores.fl) {
                estado_actual = BUSCA;
            }
            break;
        case POSICIONAR:  // la idea es que entre una y otra vez en posicionar y
                          // que compruebe su dir actual y hacia donde debe ir
            // si la direccion a la que debe ir es la actual sale de
            // ControlRobot y vuelve al programa principal, sino llama a GIRAR90I
            // o D dependiendo de la direccion actual y de la dirreccion
            // objetivo, una vez gira 90 grados vuelve a POSICIONAR y en caso de
            // haber querido girar 180º entrará dos veces, pero la direccion
            // actual que tendrá sera distinta logrando llegar a la direccion
            // objetivo
            switch (direccion) {
                case NORTE:
                    if (direccion_actual == NORTE) {
                        estado_actual = SALIR;
                    } else if (direccion_actual == ESTE) {  // bien
                        estado_actual = GIRA90I;
                    } else if (direccion_actual == OESTE) {  // bien
                        estado_actual = GIRA90D;
                    } else if (direccion_actual == SUR) {
                        estado_actual = GIRA90D;
                    }
                    break;

                case SUR:
                    cout << "sur"
                         << "\r" << endl;
                    if (direccion_actual == SUR) {
                        estado_actual = SALIR;
                    } else if (direccion_actual == OESTE) {  // bien
                        estado_actual = GIRA90I;
                    } else if (direccion_actual == ESTE) {
                        estado_actual = GIRA90D;
                    } else if (direccion_actual == NORTE) {
                        estado_actual = GIRA90D;
                    }
                    break;
                case ESTE:
                    if (direccion_actual == ESTE) {
                        estado_actual = SALIR;
                    } else if (direccion_actual == SUR) {
                        estado_actual = GIRA90I;  // bien
                    } else if (direccion_actual == NORTE) {
                        estado_actual = GIRA90D;
                    } else if (direccion_actual == OESTE) {
                        estado_actual = GIRA90D;
                    }
                    break;
                case OESTE:
                    if (direccion_actual == OESTE) {
                        estado_actual = SALIR;
                    } else if (direccion_actual == NORTE) {
                        estado_actual = GIRA90I;
                    } else if (direccion_actual == SUR) {  // bien
                        estado_actual = GIRA90D;
                    } else if (direccion_actual == ESTE) {
                        estado_actual = GIRA90D;
                    }
                    break;
                    cout << "Direccion_actual:" << (int)direccion_actual
                         << "Direccion_objetivo:" << (int)direccion << "\r"
                         << endl;
            }
            break;
    }

    // Se decide que hacer con los parametros del robot
    switch (estado_actual) {
        case INICIAL:
            motores = PARADO;
            break;
        case SIGUE:
            motores = RECTO;
            break;
        case BUSCA:
            if (sensores.lat) {
                motores = PARADO;
            } else if (DUCT_TAPE_FL(sensores.front_left) &&
                       DUCT_TAPE_FR(sensores.front_right)) {
                motores = RECTO;

            } else if (DUCT_TAPE_FL(sensores.front_left)) {
                motores = GIRAR_IZQUIERDA;

            } else if (DUCT_TAPE_FR(sensores.front_right)) {
                motores = GIRAR_DERECHA;
            }
            break;
        case GIRA90D:
            // if (sensores.lat) {
            if (DUCT_TAPE_FR(sensores.front_right)) {
                encaminado = TRUE;
                motores = GIRAR_DERECHA;
            } else if (sensores.fl && encaminado) {
                estado_actual = SALIR;
                encaminado = FALSE;
                motores = PARADO;
            } else {
                motores = GIRAR_DERECHA;
            }
            break;

        case GIRA90I:
            if (DUCT_TAPE_FL(sensores.front_left)) {
                encaminado = TRUE;
                motores = GIRAR_IZQUIERDA;
            } else if (sensores.fl && encaminado) {
                estado_actual = SALIR;
                encaminado = FALSE;
                motores = PARADO;

            } else {
                motores = GIRAR_IZQUIERDA;
            }
            break;

        case SALIR:
            motores = PARADO;
            break;
        default:
            break;
    }
}

/**
 *  	Activa los actuadores correspondientes en función de lo decidido
 *	en la lógica del programa
 */
void ControlRobot::moverActuadores() {
    switch (motores) {
        case PARADO:
            actuadores.vel_der = 0;
            actuadores.vel_izq = 0;
            break;
        case RECTO:
            actuadores.vel_der = 150;
            actuadores.vel_izq = 150;
            robot->leds(3, 90, 200);
            break;
        case GIRAR_DERECHA:
            actuadores.vel_der = -50;
            actuadores.vel_izq = 50;
            robot->leds(3, 0, 0);
            break;
        case GIRAR_IZQUIERDA:
            actuadores.vel_der = 50;
            actuadores.vel_izq = -50;
            robot->leds(3, 0, 0);
            break;
        default:
            break;
    }

    robot->driveDirect(actuadores.vel_der, actuadores.vel_izq);
}

/**
 *	Muestra información relevante al usuario
 */
void ControlRobot::imprimirInfo(void) {
    char estado[20];
    char estadogenaux[20];
    char direaux[20];
    char direaux2[20];

    switch (estado_llamada) {
        case AVANZAR:
            sprintf(estadogenaux, "AVANZAR");
            break;
        case POSICIONAR:
            sprintf(estadogenaux, "POSICIONAR");
            break;
        default:
            sprintf(estadogenaux, "No estado general");
            break;
    }
    switch (direccion) {
        case NORTE:
            sprintf(direaux, "NORTE");
            break;
        case SUR:
            sprintf(direaux, "SUR");
            break;
        case ESTE:
            sprintf(direaux, "ESTE");
            break;
        case OESTE:
            sprintf(direaux, "OESTE");
            break;
        default:
            sprintf(direaux, "No hay direccion");
            break;
    }
    switch (direccion_actual) {
        case NORTE:
            sprintf(direaux2, "NORTE");
            break;
        case SUR:
            sprintf(direaux2, "SUR");
            break;
        case ESTE:
            sprintf(direaux2, "ESTE");
            break;
        case OESTE:
            sprintf(direaux2, "OESTE");
            break;
        default:
            sprintf(direaux2, "No hay direccion");
            break;
    }

    switch (estado_actual) {
        case INICIAL:
            sprintf(estado, "INICIAL");
            break;
        case SIGUE:
            sprintf(estado, "SIGUE");
            break;
        case BUSCA:
            sprintf(estado, "BUSCA");
            break;
        case GIRA90D:
            sprintf(estado, "GIRA90D");
            break;
        case GIRA90I:
            sprintf(estado, "GIRA90I");
            break;
        case SALIR:
            sprintf(estado, "SALIR");
            break;
        default:
            sprintf(estado, "errrrrrorrrrr");
            break;
    }

    //    printf("Estado: %s ", estado);
    //    printf(": %s ", sensores.fl ? "true" : "false");
    //    printf(" Valor: %d", sensores.front_left);
    //    printf("\n\r");
    cout << " Estado: " << estado << " estadogen: " << estadogenaux
         << " direccion_obj: " << direaux << " direccion_act: " << direaux2
         << "\r" << endl;
}

// void ControlRobot::imprimirInfo(void) {
//        char estado[20];
//        switch (estado_actual) {
//            case INICIAL: sprintf(estado, "INICIAL");
//                break;
//            case SIGUE: sprintf(estado, "SIGUE");
//                break;
//            case BUSCA: sprintf(estado, "BUSCA");
//                break;
//            case PAUSA: sprintf(estado, "PAUSA");
//                break;
//            case OBSTACULO: sprintf(estado, "OBSTACULO");
//                break;
//            default: sprintf(estado, "INDEFINIDO");
//                break;
//        }
//
//        cout << "Estado: " << estado << "\r" << endl;
//    }

/**
 *	Cierra conexiones abiertas
 */
void ControlRobot::finalizacion(void) {
    robot->disconnect();
    delete robot;
}
