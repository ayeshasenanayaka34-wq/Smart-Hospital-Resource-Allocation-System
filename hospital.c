#include <stdio.h>
#include <string.h>
#include "hospital.h"

int main(){
char specialtyName[NUM_SPECIALTIES][50] = {
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

double consultationFee[NUM_SPECIALTIES] = {
    1500.00,
    2500.00,
    4500.00,
    5000.00
};

int consultationTime[NUM_SPECIALTIES] = {
    15,
    20,
    30,
    30
};

int dailyPatientCap[NUM_SPECIALTIES] = {
    30,
    20,
    12,
    10
};

}