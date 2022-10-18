/*
 * File:   Test.cpp
 * Author: @bgamecho
 *
 * Test program for iRobot_Framework
 */

#include "Libs/iRobot_framework/IRobotConnection.h"

#define COM "/dev/ttyUSB0"

using namespace std;

int main(int argc, char** argv) {
    int sensor_value = -1;

    // Creamos un objeto robot
    IRobotConnection robot(COM);
    // Activamos el Verbose Mode
    robot.setVerboseMode(false);

    // Iniciamos la conexion...
    cout << "Connecting... ";
    if (robot.connect() != 1) {
        cout << "Error\r" << endl;
        return EXIT_FAILURE;
    }
    cout << "Done!\r" << endl;

    // Comando 128 start
    cout << "Send start and full mode\r" << endl;
    robot.start();
    robot.full();
    while (1) {
        cout << "Recogiendo 1 muestra del sensor de distancia a la pared (Wall "
                "Signal)\r"
             << endl;
        sensor_value = robot.updateSensor(iRobotSensors::WALLSIGNAL);
        cout << "Valors obtenido: " << sensor_value << "\r" << endl;
    }
    cout << "Disconnect from serial line\r" << endl;
    robot.disconnect();

    return EXIT_SUCCESS;
}
