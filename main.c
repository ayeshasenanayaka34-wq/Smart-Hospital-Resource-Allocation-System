#include <stdio.h>
#include "hospital.h"

int main(void)
{
    printf("Smart Hospital System\n");

    initializeBeds();
    displaySpecialties();
    displayWards();

    return 0;
}