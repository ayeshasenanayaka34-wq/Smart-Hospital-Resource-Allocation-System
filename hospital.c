#include <stdio.h>
#include <string.h>
#include "hospital.h"

void initializeBeds(void);
void displaySpecialties(void);
void displayWards(void);

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

int bedOccupancy[NUM_WARDS][MAX_BEDS];

char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int urgencyLevel[MAX_PATIENTS];
int specialtyID[MAX_PATIENTS];
int wardID[MAX_PATIENTS];
int daysAdmitted[MAX_PATIENTS];
int registrationOrder[MAX_PATIENTS];
int patientCount = 0;
double baseFee[MAX_PATIENTS];
double surcharge[MAX_PATIENTS];
double wardCost[MAX_PATIENTS];
double grossTotal[MAX_PATIENTS];
double discount[MAX_PATIENTS];
double finalPayable[MAX_PATIENTS];
double waitingTime[MAX_PATIENTS];


void initializeBeds(void)
{
    int i, j;

    for (i = 0; i < NUM_WARDS; i++)
    {
        for (j = 0; j < MAX_BEDS; j++)
        {
            bedOccupancy[i][j] = 0;
        }
    }
}

void displaySpecialties(void)
{
    int i;

    printf("\nAvailable Specialties:\n");

    for (i = 0; i < NUM_SPECIALTIES; i++)
    {
        printf("%d. %s - Rs. %.2f - %d min - Daily Cap: %d\n",
               i + 1,
               specialtyName[i],
               consultationFee[i],
               consultationTime[i],
               dailyPatientCap[i]);
    }
}

void displayWards(void)
{
    int i;

    printf("\nAvailable Wards:\n");

    for (i = 0; i < NUM_WARDS; i++)
    {
        printf("%d. %s - Rs. %.2f/day - Capacity: %d beds\n",
               i + 1,
               wardName[i],
               wardDailyRate[i],
               wardCapacity[i]);
    }
}