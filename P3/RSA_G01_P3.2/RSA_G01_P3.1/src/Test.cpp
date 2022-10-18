/*
 * File:   Test.cpp
 * Author: @bgamecho
 *
 * Test program for iRobot_Framework
 */

#include "Libs/iRobot_framework/IRobotConnection.h"

#define COM "/dev/ttyUSB0"

using namespace std;

void dec2bin(int dec) {
    if (dec != 0)
        dec2bin(dec / 2);
    if (dec != 0)
        cout << dec % 2;
}

int main(int argc, char** argv) {
    int sensor_value = 0;

    // Creamos un objeto robot
    IRobotConnection robot(COM);

    // Activamos el Verbose Mode
    robot.setVerboseMode(true);

    // Iniciamos la conexion...
    cout << "Connecting... ";
    if (robot.connect() != 1) {
        cout << "Error\n" << endl;
        return EXIT_FAILURE;
    }
    cout << "Done!\n" << endl;
    // delay(500);

    // Comando 128 start
    cout << "Send start" << endl;
    robot.start();
    // delay(500);

    // Ejecutamos el comando 142 35 y mostramos el resultado por pantalla
    cout << "Send OI mode request" << endl;
    sensor_value = robot.updateSensor(iRobotSensors::OIMODE);
    cout << "Modo de funcionamiento: " << +sensor_value << endl;

    // Comando 132 modo full
    cout << "Send Full mode" << endl;
    robot.full();
    // delay(500);

    // Ejecutamos el comando 142 35 y mostramos el resultado por pantalla
    cout << "Send OI mode request" << endl;
    sensor_value = robot.updateSensor(iRobotSensors::OIMODE);
    cout << "Modo de funcionamiento: " << +sensor_value << endl;

    // Avanzamos durante 2 segundos a 200mm/s y paramos los motores
    cout << "Send drive direct for 2 seconds, then stops" << endl;
    robot.driveDirect(200, 200);
    delay(2000);
    cout << "Then stops" << endl;
    robot.driveDirect(0, 0);

    // Desconectamos
    cout << "Disconnect from serial line" << endl;
    robot.disconnect();

    return EXIT_SUCCESS;
}
