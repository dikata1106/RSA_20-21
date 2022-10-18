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

    // robot.driveDirect(200,200);
    // robot.waitDistance(2100);
    // robot.driveDirect(0,0);
    robot.drive(200, 32768);
    robot.waitDistance(2100);
    robot.drive(0, 0);

    cout << "Disconnect from serial line\r" << endl;
    robot.disconnect();

    return EXIT_SUCCESS;
}
