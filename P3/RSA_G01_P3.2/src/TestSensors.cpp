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
    int C_L[5] = {-1, -1, -1, -1, -1};
    int C_FL[5] = {-1, -1, -1, -1, -1};
    int C_FR[5] = {-1, -1, -1, -1, -1};
    int C_R[5] = {-1, -1, -1, -1, -1};
    int i = 0;
    int sumL = 0, sumFL = 0, sumFR = 0, sumR = 0;
    int avgL = 0, avgFL = 0, avgFR = 0, avgR = 0;

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

    cout << "Recogiendo 5 muestras de los sensores de barranco\r" << endl;
    for (i = 0; i < 5; i++) {
        C_L[i] = robot.updateSensor(iRobotSensors::CLIFFLEFTSIGNAL);
        C_FL[i] = robot.updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
        C_FR[i] = robot.updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
        C_R[i] = robot.updateSensor(iRobotSensors::CLIFFRIGHTSIGNAL);
    }

    cout << "Valores obtenidos y medias:\r" << endl;
    cout << "C_L\tC_FL\tC_FR\tC_R\r" << endl;
    for (i = 0; i < 5; i++) {
        sumL += C_L[i];
        sumFL += C_FL[i];
        sumFR += C_FR[i];
        sumR += C_R[i];
        cout << C_L[i] << "\t" << C_FL[i] << "\t" << C_FR[i] << "\t" << C_R[i]
             << "\r" << endl;
    }
    avgL = sumL / 5;
    avgFL = sumFL / 5;
    avgFR = sumFR / 5;
    avgR = sumR / 5;
    cout << "=============================\r" << endl;
    cout << avgL << "\t" << avgFL << "\t" << avgFR << "\t" << avgR << "\r"
         << endl;

    cout << "Disconnect from serial line\r" << endl;
    robot.disconnect();

    return EXIT_SUCCESS;
}
