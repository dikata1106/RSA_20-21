/*
 * Ejemplos para aprender a usar correctamente la clase Laberinto y sus
 * estructuras
 */

#include <poll.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include "ControlRobot.h"
#include "Laberinto.h"

using namespace std;

void ejemplo1();
void ejemplo2();
void ejemplo3(const char *path);
void prueba1(const char *path);
void prueba2(const char *path);
void prueba3(const char *path);
void control_robot(char, char, char);
int getch(int ms);

// coord origen-destino globales
int ox = 0, oy = 0, dx = 5, dy = 5;

int main(int argc, char *argv[]) {
    char ejemplo;

    cout << "Escribe un número para ejecutar un ejemplo:\n\r"
         << "\t 1 - Ejemplo 1\n\r"
         << "\t 2 - Ejemplo 2\n\r"
         << "\t 3 - Ejemplo 3 usando Rejilla.xml\n\r"
         << "\t 4 - Ejemplo 3 usando Laberinto.xml\n\r"
         << "\t 5 - Prueba1 usando Rejilla.xml\n\r"
         << "\t 6 - Prueba1 usando Laberinto.xml\n\r"
         << "\t 7 - Prueba2 usando Rejilla.xml\n\r"
         << "\t 8 - Prueba2 usando Laberinto.xml\n\r"
         << "\t 9 - Prueba3 usando Rejilla.xml\n\r"
         << "\t 0 - Prueba3 usando Laberinto.xml\n\r" << endl;
    while (!(ejemplo = getch(500)))
        ;  // espera a que se pulse una tecla
    switch (ejemplo) {
        case '1':
            ejemplo1();
            break;
        case '2':
            ejemplo2();
            break;
        case '3':
            ejemplo3("xml/Rejilla.xml");
            break;
        case '4':
            ejemplo3("xml/Laberinto.xml");
            break;
        case '5':
            prueba1("xml/Rejilla.xml");  // copia de ejemplo 3 (con el codigo de
                                         // avanzar)
            break;
        case '6':
            prueba1("xml/Laberinto.xml");  // copia de ejemplo 3 (con el codigo
                                           // de avanzar)
            break;
        case '7':
            prueba2("xml/Rejilla.xml");  // encontrar camino solo print
            break;
        case '8':
            prueba2("xml/Laberinto.xml");  // encontrar camino solo print
            break;
        case '9':
            prueba3("xml/Rejilla.xml");  // encontrar camino  y recorrer
            break;
        case '0':
            prueba3("xml/Laberinto.xml");  // encontrar camino y recorrer
            break;
        default:
            cout << "número no reconocido\r" << endl;
            break;
    }

    return EXIT_SUCCESS;
}

void control_robot(char estado_actual, char dirobj, char diract) {
    ControlRobot robot;

    robot.inicializacion(estado_actual, dirobj, diract);

    while (!robot.condicionSalida()) {
        robot.leerSensores();
        robot.logicaEstados();
        robot.moverActuadores();
        robot.imprimirInfo();
    }

    robot.finalizacion();
}

/*
 * El primer ejemplo consiste en la creación de una lista enlazada de nodos
 * camino que sigue la siguiente secuencia: [0,0] - [4,3] - [5,1]
 */
void ejemplo1() {
    cout << "Ejemplo1:\r" << endl;
    nodo *nodo_A = new nodo();
    nodo_A->x = 0;
    nodo_A->y = 0;

    // cout << nodo_A->x << " - " << nodo_A->y << endl;

    // Creamos un nuevo camino que contiene el nodo [2,1]
    camino *aux = new camino();
    aux->nodo_actual = nodo_A;
    aux->anterior = NULL;
    aux->siguiente = NULL;

    nodo *nodo_B = new nodo();
    nodo_B->x = 4;
    nodo_B->y = 3;

    aux->siguiente = new camino();
    aux->siguiente->nodo_actual =
        nodo_B;  // Asignamos al nuevo camino el nodo [4,3]
    aux->siguiente->siguiente = NULL;
    aux->siguiente->anterior = aux;

    nodo *nodo_C = new nodo();
    nodo_C->x = 5;
    nodo_C->y = 1;

    camino *camino_C = new camino();
    aux->siguiente->siguiente = camino_C;
    camino_C->nodo_actual = nodo_C;
    camino_C->anterior = aux->siguiente;
    camino_C->siguiente = NULL;

    cout << "Camino creado: ";
    do {
        cout << "[" << aux->nodo_actual->x << "," << aux->nodo_actual->y
             << "] ";
        aux = aux->siguiente;  // Actualizamos el valor del nodo auxiliar
    } while (aux != NULL);
    cout << "\n\r" << endl;
}

/*
 * El segundo ejemplo repite lista enlazada de nodos camino [0,0] - [4,3] -
 * [5,1] usando "laberinto.xml" como Mapa
 */
void ejemplo2() {
    cout << "Ejemplo2: \r" << endl;

    Laberinto *maze;
    maze = new Laberinto("xml/Laberinto.xml");
    maze->imprimirLaberinto();

    // Para usar maze->matriz fuera de la clase Laberinto hay que cambiar en
    // Laberinto.h su visibilidad de private a public.
    nodo nodo_matriz = maze->matriz[0][0];

    // Comprobamos que hemos copiado bien el nodo matriz[0][0] a nodo_matriz
    // cout << nodo_matriz.Este->x << " - " << nodo_matriz.Este->y << endl;

    camino *mi_camino = new camino();
    mi_camino->nodo_actual = &nodo_matriz;

    camino *mi_camino2 = new camino();
    mi_camino2->nodo_actual = &maze->matriz[4][3];
    mi_camino->siguiente = mi_camino2;

    camino *mi_camino3 = new camino();
    mi_camino3->nodo_actual = &maze->matriz[5][1];
    mi_camino->siguiente->siguiente = mi_camino3;

    // Imprimimos los nodos que contienen los caminos de la lista mi_camino
    // junto con el nodo que se encuentra enlazado al Este
    cout << "Camino creado: \r" << endl;
    do {
        cout << "[" << mi_camino->nodo_actual->x << ","
             << mi_camino->nodo_actual->y << "] ";
        if (mi_camino->nodo_actual->Este == NULL) {
            cout << ": no existe nodo al Este\r" << endl;
        } else {
            cout << ": nodo al Este [" << mi_camino->nodo_actual->Este->x << ","
                 << mi_camino->nodo_actual->Este->y << "]\r" << endl;
        }
        mi_camino =
            mi_camino->siguiente;  // Actualizamos el valor del nodo auxiliar
    } while (mi_camino != NULL);
    cout << "\n\r" << endl;
}

/*
 * El tercer ejemplo carga un laberinto y permite recorrerlo usando el teclado:
 * - Flechas del teclado: Cambia la orientación del robot
 * - Barra espaciadora: Avanza una posición si puede
 * - Backspace, Enter y Tab: Imprime los nodos del camino por los que ha pasado
 * el robot
 * - q : Termina de recorrer el laberinto
 */
void ejemplo3(const char *path) {
    bool fin = false;
    bool mapa_modificado = false;
    char tecla, orientacion;
    int x, y;

    Laberinto *maze;
    maze = new Laberinto(path);
    maze->imprimirLaberinto();

    do {
        if (tecla = getch(300)) {
            switch (tecla) {
                case 8:   // Backspace
                case 9:   // Tab
                case 10:  // Enter
                    maze->imprimirCaminoRobot();
                    break;
                case 27:
                    tecla = getch(10);
                    if (tecla == 91) {
                        tecla = getch(10);

                        maze->getPosRobot(&x, &y, &orientacion);
                        switch (tecla) {
                            case 65:  // Flecha arriba
                                if (orientacion == NORTE) {
                                    cout << "El robot ya se encuentra "
                                            "orientado hacia el Norte\r"
                                         << endl;
                                } else {
                                    cout << "Robot orientado al Norte\r"
                                         << endl;
                                    maze->orientarRobotNorte();
                                    mapa_modificado = true;
                                }
                                break;
                            case 66:  // Flecha abajo
                                if (orientacion == SUR) {
                                    cout << "El robot ya se encuentra "
                                            "orientado hacia el Sur\r"
                                         << endl;
                                } else {
                                    cout << "Robot orientado al Sur\r" << endl;
                                    maze->orientarRobotSur();
                                    mapa_modificado = true;
                                }
                                break;
                            case 67:  // Flecha derecha
                                if (orientacion == ESTE) {
                                    cout << "El robot ya se encuentra "
                                            "orientado hacia el Este\r"
                                         << endl;
                                } else {
                                    cout << "Robot orientado al Este\r" << endl;
                                    maze->orientarRobotEste();
                                    mapa_modificado = true;
                                }
                                break;
                            case 68:  // Flecha izquierda
                                if (orientacion == OESTE) {
                                    cout << "El robot ya se encuentra "
                                            "orientado hacia el Oeste\r"
                                         << endl;
                                } else {
                                    cout << "Robot orientado al Oeste\r"
                                         << endl;
                                    maze->orientarRobotOeste();
                                    mapa_modificado = true;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    break;

                case 32:  // Barra espaciadora

                    maze->getPosRobot(&x, &y, &orientacion);
                    switch (orientacion) {
                        case NORTE:
                            if (maze->esNorteLibre()) {
                                maze->avanzaNorte();
                                mapa_modificado = true;
                            } else {
                                cout << "No existe un camino al Norte \r"
                                     << endl;
                            }
                            break;
                        case SUR:
                            if (maze->esSurLibre()) {
                                maze->avanzaSur();
                                mapa_modificado = true;
                            } else {
                                cout << "No existe un camino al Sur\r" << endl;
                            }
                            break;
                        case ESTE:
                            if (maze->esEsteLibre()) {
                                maze->avanzaEste();
                                mapa_modificado = true;
                            } else {
                                cout << "No existe un camino al Este \r"
                                     << endl;
                            }
                            break;
                        case OESTE:
                            if (maze->esOesteLibre()) {
                                maze->avanzaOeste();
                                mapa_modificado = true;
                            } else {
                                cout << "No existe un camino al Oeste \r"
                                     << endl;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case 'q':
                    fin = true;
                    break;
                default:
                    break;
            }
            if (mapa_modificado) {
                maze->imprimirLaberinto();
                mapa_modificado = false;
            }
        }
    } while (!fin);

    maze->imprimirCaminoRobot();
}

void prueba1(const char *path) {
    bool fin = false;
    bool mapa_modificado = false;
    char tecla, orientacion;
    int x, y;

    Laberinto *maze;
    maze = new Laberinto(path);
    maze->imprimirLaberinto();

    do {
        if (tecla = getch(300)) {
            switch (tecla) {
                case 8:   // Backspace
                case 9:   // Tab
                case 10:  // Enter
                    maze->imprimirCaminoRobot();
                    break;
                case 27:
                    tecla = getch(10);
                    if (tecla == 91) {
                        tecla = getch(10);

                        maze->getPosRobot(&x, &y, &orientacion);
                        switch (tecla) {
                            case 65:  // Flecha arriba
                                if (orientacion == NORTE) {
                                    cout << "El robot ya se encuentra "
                                            "orientado hacia el Norte\r"
                                         << endl;
                                } else {
                                    cout << "Robot orientado al Norte\r"
                                         << endl;
                                    if (orientacion == SUR) {
                                        control_robot(POSICIONAR, OESTE,
                                                      orientacion);
                                        control_robot(POSICIONAR, NORTE, OESTE);
                                    } else {
                                        control_robot(POSICIONAR, NORTE,
                                                      orientacion);
                                    }

                                    maze->orientarRobotNorte();

                                    mapa_modificado = true;
                                }
                                break;
                            case 66:  // Flecha abajo
                                if (orientacion == SUR) {
                                    cout << "El robot ya se encuentra "
                                            "orientado hacia el Sur\r"
                                         << endl;
                                } else {
                                    cout << "Robot orientado al Sur\r" << endl;
                                    if (orientacion == NORTE) {
                                        control_robot(POSICIONAR, ESTE,
                                                      orientacion);
                                        control_robot(POSICIONAR, SUR, ESTE);
                                    } else {
                                        control_robot(POSICIONAR, SUR,
                                                      orientacion);
                                    }

                                    maze->orientarRobotSur();

                                    mapa_modificado = true;
                                }
                                break;
                            case 67:  // Flecha derecha
                                if (orientacion == ESTE) {
                                    cout << "El robot ya se encuentra "
                                            "orientado hacia el Este\r"
                                         << endl;
                                } else {
                                    if (orientacion == OESTE) {
                                        control_robot(POSICIONAR, SUR,
                                                      orientacion);
                                        control_robot(POSICIONAR, ESTE, SUR);
                                    } else {
                                        control_robot(POSICIONAR, ESTE,
                                                      orientacion);
                                    }
                                    cout << "Robot orientado al Este\r" << endl;

                                    cout << "Robot orientado al Este2\r"
                                         << endl;
                                    maze->orientarRobotEste();

                                    mapa_modificado = true;
                                    cout << "Robot orientado al Este3\r"
                                         << endl;
                                }
                                break;
                            case 68:  // Flecha izquierda
                                if (orientacion == OESTE) {
                                    cout << "El robot ya se encuentra "
                                            "orientado hacia el Oeste\r"
                                         << endl;
                                } else {
                                    if (orientacion == ESTE) {
                                        control_robot(POSICIONAR, NORTE,
                                                      orientacion);
                                        control_robot(POSICIONAR, OESTE, NORTE);
                                    } else {
                                        control_robot(POSICIONAR, OESTE,
                                                      orientacion);
                                    }
                                    cout << "Robot orientado al Oeste\r"
                                         << endl;

                                    maze->orientarRobotOeste();

                                    mapa_modificado = true;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    break;

                case 32:  // Barra espaciadora

                    maze->getPosRobot(&x, &y, &orientacion);
                    switch (orientacion) {
                        case NORTE:
                            if (maze->esNorteLibre()) {
                                control_robot(AVANZAR, NORTE, NORTE);  // avanza
                                maze->avanzaNorte();

                                mapa_modificado = true;
                            } else {
                                cout << "No existe un camino al Norte \r"
                                     << endl;
                            }
                            break;
                        case SUR:
                            if (maze->esSurLibre()) {
                                control_robot(AVANZAR, SUR, SUR);  // avanza
                                maze->avanzaSur();
                                mapa_modificado = true;
                            } else {
                                cout << "No existe un camino al Sur\r" << endl;
                            }
                            break;
                        case ESTE:
                            if (maze->esEsteLibre()) {
                                control_robot(AVANZAR, ESTE, ESTE);  // avanza
                                maze->avanzaEste();
                                mapa_modificado = true;
                            } else {
                                cout << "No existe un camino al Este \r"
                                     << endl;
                            }
                            break;
                        case OESTE:
                            if (maze->esOesteLibre()) {
                                control_robot(AVANZAR, OESTE, OESTE);  // avanza
                                maze->avanzaOeste();
                                mapa_modificado = true;
                            } else {
                                cout << "No existe un camino al Oeste \r"
                                     << endl;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case 'q':
                    fin = true;
                    break;
                default:
                    break;
            }
            if (mapa_modificado) {
                maze->imprimirLaberinto();
                mapa_modificado = false;
            }
        }
    } while (!fin);

    maze->imprimirCaminoRobot();
}

void prueba2(const char *path) {
    Laberinto *maze;
    maze = new Laberinto(path);
    maze->imprimirLaberinto();
    maze->encontrarCamino(0, 0, 5, 5);
}

void prueba3(const char *path) {
    char orientacion;
    int x, y;
    Laberinto *maze;
    maze = new Laberinto(path);
    maze->imprimirLaberinto();
    struct camino *recorrido = maze->encontrarCamino(ox, oy, dx, dy);
    while (recorrido->siguiente != NULL) {
        maze->getPosRobot(&x, &y, &orientacion);
        if (recorrido->nodo_actual->x == recorrido->siguiente->nodo_actual->x) {
            if (recorrido->nodo_actual->y <
                recorrido->siguiente->nodo_actual->y) {  // avanzara sur
                if (orientacion != SUR) {
                    if (orientacion == NORTE) {
                        control_robot(POSICIONAR, ESTE, orientacion);
                        control_robot(POSICIONAR, SUR, ESTE);
                    } else {
                        control_robot(POSICIONAR, SUR, orientacion);
                    }
                    maze->orientarRobotSur();
                    maze->avanzaSur();
                }
            } else {  // avanzara norte
                if (orientacion != NORTE) {
                    // cout << "Robot orientado al Norte\r" << endl;
                    if (orientacion == SUR) {
                        control_robot(POSICIONAR, OESTE, orientacion);
                        control_robot(POSICIONAR, NORTE, OESTE);
                    } else {
                        control_robot(POSICIONAR, NORTE, orientacion);
                    }
                    maze->orientarRobotNorte();
                    maze->avanzaNorte();
                }
            }
        } else {
            if (recorrido->nodo_actual->x <
                recorrido->siguiente->nodo_actual->x) {  // avanzara este
                if (orientacion != ESTE) {
                    if (orientacion == OESTE) {
                        control_robot(POSICIONAR, SUR, orientacion);
                        control_robot(POSICIONAR, ESTE, SUR);
                    } else {
                        control_robot(POSICIONAR, ESTE, orientacion);
                    }
                    maze->orientarRobotEste();
                    maze->avanzaEste();
                }
            } else {  // avanzara oeste
                if (orientacion != OESTE) {
                    if (orientacion == ESTE) {
                        control_robot(POSICIONAR, NORTE, orientacion);
                        control_robot(POSICIONAR, OESTE, NORTE);
                    } else {
                        control_robot(POSICIONAR, OESTE, orientacion);
                    }
                    maze->orientarRobotOeste();
                    maze->avanzaOeste();
                }
            }
        }

        control_robot(AVANZAR, NULL, NULL);
        maze->imprimirLaberinto();
        recorrido = recorrido->siguiente;
    }
}

/**
 * Espera la lectura de un caracter por teclado durante ms milisegundos
 * @param ms tiempo de espera en milisegundos
 * @return 0 si no lee nada, el caracter leido en otro caso
 */
int getch(int ms) {
    int ret;
    struct termios oldt, newt;
    struct pollfd pfds[1];

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    pfds[0].fd = STDIN_FILENO;
    pfds[0].events = POLLIN;
    poll(pfds, 1, ms);
    if (pfds[0].revents & POLLIN) {
        char ch;
        read(STDIN_FILENO, &ch, 1);
        ret = ch;
    } else {
        ret = 0;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ret;
}
