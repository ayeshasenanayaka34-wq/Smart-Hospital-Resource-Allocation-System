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

char wardName[NUM_WARDS][50] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU"
};

double wardDailyRate[NUM_WARDS] = {
    3000.00,
    6000.00,
    12000.00,
    25000.00
};

int wardCapacity[NUM_WARDS] = {
    20,
    10,
    10,
    5
};
}