/*
 * Scripts iRobot Create
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>

#define SERIAL "/dev/ttyUSB0"

void send_script(char *myScript);

int main(int argc, char **argv) {
    std::cout << "Script: " << argv[1] << std::endl;

    if (argc == 2) {
        send_script(argv[1]);
    } else {
        std::cout << "Error no argument found" << std::endl;
    }

    return EXIT_SUCCESS;
}

void send_script(char *myScript) {
    int value, fd_serial, num_bytes;

    FILE *fd_script;
    fd_script = fopen(myScript, "r");

    if (fd_script < 0) {
        std::cout << "Error opening the script file" << std::endl;
    }

    fd_serial = 0;
    fd_serial = serialOpen(SERIAL, 57600);
    if (fd_serial < 0) {
        std::cout << "Error opening serial line" << std::endl;
    }

    serialPutchar(fd_serial, 128);
    delay(10);

    std::cout << "escribiendo 128" << std::endl;

    serialPutchar(fd_serial, 132);
    delay(10);

    std::cout << "escribiendo 132" << std::endl;

    value = 0;
    num_bytes = 0;

    while (value != -1) {
        fscanf(fd_script, "%d", &value);

        if (value != -1) {
            num_bytes++;
            std::cout << std::dec << value << " " << std::endl;

            serialPutchar(fd_serial, value);
            delay(10);
        }
    }
    std::cout << "Script ends: " << num_bytes << " bytes read" << std::endl;

    serialClose(fd_serial);
    return;
}
