#include <stdio.h>
#include "hospital.h"

int main(void)
{
    printf("Smart Hospital System\n");

    initializeBeds();
    displaySpecialties();
    displayWards();
    registerPatient();
    allocateBed(0);

    return 0;
}