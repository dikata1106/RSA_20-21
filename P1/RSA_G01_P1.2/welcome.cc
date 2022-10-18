#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[]) {
    char name[20];
    printf("Como te llamas?\n\r");
    std::cout << std::flush;
    scanf("%s", name);
    printf("Hola %s!\n\r", name);
    std::cout << std::flush;
    exit(0);
}