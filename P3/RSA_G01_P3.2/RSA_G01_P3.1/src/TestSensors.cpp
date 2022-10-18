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
        cout << "dec2binif(dec!=0)" << dec % 2 << "\r" << endl;
    if (dec == 0)
        cout << "dec2binif(dec==0)\r";
}

int main(int argc, char** argv) {
    int sensor_value[7] = {0, 0, 0, 0, 0, 0, 0};
    char song1[2] = {'1', '1'};
    char song3[2] = {'3', '1'};
    char song5[2] = {'5', '1'};
    char song7[2] = {'7', '1'};
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
    cout << "Send start\r" << endl;
    robot.start();

    // Comando 132 modo full
    cout << "Send Full mode\r" << endl;
    robot.full();  // Ejecutamos el comando 142 35 y mostramos el resultado por
                   // pantalla

    cout << "Send OI mode request\r" << endl;
    sensor_value[6] = robot.updateSensor(iRobotSensors::OIMODE);
    cout << "Modo de funcionamiento: " << +sensor_value[6] << "\r" << endl;

    robot.song(1, 2, song1);
    robot.song(3, 2, song3);
    robot.song(5, 2, song5);
    robot.song(7, 2, song7);

    cout << "\nListamos todos los sensores a comprobar\r" << endl;

    while (1) {
        sensor_value[0] =
            robot.updateSensor(iRobotSensors::BUMPERS_AND_WHEELDROPS);
        if (sensor_value[0] != 0)
            robot.playSong(7);

        sensor_value[1] = robot.updateSensor(iRobotSensors::CLIFFLEFT);
        if (sensor_value[1] != 0)
            robot.playSong(5);

        sensor_value[2] = robot.updateSensor(iRobotSensors::CLIFFFRONTLEFT);
        if (sensor_value[2] != 0)
            robot.playSong(5);

        sensor_value[3] = robot.updateSensor(iRobotSensors::CLIFFFRONTRIGHT);
        if (sensor_value[3] != 0)
            robot.playSong(5);

        sensor_value[4] = robot.updateSensor(iRobotSensors::CLIFFRIGHT);
        if (sensor_value[4] != 0)
            robot.playSong(5);

        sensor_value[5] = robot.updateSensor(iRobotSensors::BUTTONS);
        if (sensor_value[5] != 0)
            robot.playSong(1);

        if (sensor_value[0] == 0 && sensor_value[1] == 0 &&
            sensor_value[2] == 0 && sensor_value[3] == 0 &&
            sensor_value[4] == 0 && sensor_value[5] == 0)
            robot.leds(8, 255, 0);
        else
            robot.leds(8, 255, 255);
    }

    // Desconectamos
    cout << "Disconnect from serial line\r" << endl;
    robot.disconnect();

    return EXIT_SUCCESS;
}
