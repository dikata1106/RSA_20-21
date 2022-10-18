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
    if(dec!=0) dec2bin(dec/2);
    if(dec!=0) cout << "dec2binif(dec!=0)" << dec%2 << "\r" << endl;
    if(dec==0) cout<<"dec2binif(dec==0)\r";
}

int main(int argc, char**argv) {

    int sensor_value = 0, maxwallsignal = 0;
    int command = 0, count = 10;

    // Creamos un objeto robot
    IRobotConnection robot(COM);
    
    // Activamos el Verbose Mode
    robot.setVerboseMode(false);
    
    // Iniciamos la conexion...
    cout << "Connecting... ";
    if(robot.connect()!=1){ 
        cout << "Error\r" << endl;
        return EXIT_FAILURE;
    }
    cout << "Done!\r" << endl;
    //delay(500);
    
    // Comando 128 start
    cout << "Send start\r" << endl;
    robot.start();
    //delay(500);
    
    // Comando 132 modo full
    cout << "Send Full mode\r" << endl;
    robot.full();    // Ejecutamos el comando 142 35 y mostramos el resultado por pantalla
    
    cout << "Send OI mode request\r" << endl;    
    sensor_value = robot.updateSensor(iRobotSensors::OIMODE);
    cout << "Modo de funcionamiento: " << +sensor_value << "\r" << endl;
      
 
    //Ejemplo de uso del sensor BUMP y conversion dec -> bin
    cout << "\nActivate any combination of Bumpers and Wheel Drops\r" << endl;
    sensor_value = robot.updateSensor(iRobotSensors::BUMPERS_AND_WHEELDROPS);
    cout << "Bumps and Wheel Drops: " << +sensor_value << "\r" << endl;
    if(dec!=0) dec2bin(+sensor_value/2);
    if(dec!=0) cout << "(dec!=0)" <<+sensor_value%2<< "\r" << endl;
  
    // Leemos todos los sensores y los mostramos por pantalla
    cout << "\nListamos todos los sensores de parado\r" << endl;

    sensor_value = robot.updateSensor(iRobotSensors::CLIFFLEFT);
    cout << "Group 9 Cliff Left: " << +sensor_value << "\r" << endl;

    sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTLEFT);
    cout << "Group 10 Cliff Front Left: " << +sensor_value << "\r" << endl;
    
    sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTRIGHT);
    cout << "Group 11 Cliff Front Right: " << +sensor_value << "\r" << endl;

    sensor_value = robot.updateSensor(iRobotSensors::CLIFFRIGHT);
    cout << "Group 12 Cliff Right: " << +sensor_value << "\r" << endl;

    sensor_value = robot.updateSensor(iRobotSensors::BUTTONS);
    cout << "Group 18 Buttons: " << +sensor_value << "\r" << endl;
    dec2bin(+sensor_value);  

//    sensor_value = robot.updateSensor(iRobotSensors::CLIFFLEFTSIGNAL);
//    cout << "Group 28 Cliff Left Signal: " << +sensor_value << "\r" << endl;
//    
//    sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
//    cout << "Group 29 Cliff Front Left Signal: " << +sensor_value << "\r" << endl;
//    
//    sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
//    cout << "Group 30 Cliff Front Right Signal: " << +sensor_value << "\r" << endl;
//    
//    sensor_value = robot.updateSensor(iRobotSensors::CLIFFRIGHTSIGNAL);
//    cout << "Group 31 Cliff Right Signal: " << +sensor_value << "\r" << endl;

    //Avanzamos durante 2 segundos a 200mm/s y paramos los motores
    cout << "\nSend drive direct robot.driveDirect(250,150);\r" << endl;
    robot.driveDirect(250,150);
    delay (2000);
    cout << "Listamos todos los sensores en marcha\r" << endl;
    // Leemos los sensores y los mostramos por pantalla

    sensor_value = robot.updateSensor(iRobotSensors::BUMPERS_AND_WHEELDROPS);
    cout << "Bumps and Wheel Drops: " << +sensor_value << "\r" << endl;
    if(dec!=0) dec2bin(+sensor_value/2);
    if(dec!=0) cout<< "(dec!=0)" <<+sensor_value%2<< "\r" << endl;
 
    sensor_value = robot.updateSensor(iRobotSensors::CLIFFLEFT);
    cout << "Group 9 Cliff Left: " << +sensor_value << "\r" << endl;

    sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTLEFT);
    cout << "Group 10 Cliff Front Left: " << +sensor_value << "\r" << endl;
    
    sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTRIGHT);
    cout << "Group 11 Cliff Front Right: " << +sensor_value << "\r" << endl;

    sensor_value = robot.updateSensor(iRobotSensors::CLIFFRIGHT);
    cout << "Group 12 Cliff Right: " << +sensor_value << "\r" << endl;
 
    sensor_value = robot.updateSensor(iRobotSensors::BUTTONS);
    cout << "Group 18 Buttons: " << +sensor_value << "\r" << endl;
    dec2bin(+sensor_value);  
     
//    sensor_value = robot.updateSensor(iRobotSensors::CLIFFLEFTSIGNAL);
//    cout << "Group 28 Cliff Left Signal: " << +sensor_value << "\r" << endl;
//    
//    sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
//    cout << "Group 29 Cliff Front Left Signal: " << +sensor_value << "\r" << endl;
//    
//    sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
//    cout << "Group 30 Cliff Front Right Signal: " << +sensor_value << "\r" << endl;
//    
//    sensor_value = robot.updateSensor(iRobotSensors::CLIFFRIGHTSIGNAL);
//    cout << "Group 31 Cliff Right Signal: " << +sensor_value << "\r" << endl;
//
//    sensor_value = robot.updateSensor(iRobotSensors::OIMODE);
//    cout << "Group 35 OI Mode: " << +sensor_value << "\r" << endl;

    robot.driveDirect(200,200);
    cout << "Then it stops\r" << endl;
    robot.driveDirect(0,0);
   
    // Desconectamos
    cout << "Disconnect from serial line\r" << endl;
    robot.disconnect();

    return EXIT_SUCCESS;
}
