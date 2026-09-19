#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_PATIENTS 100
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4
#define MAX_BEDS 20

void initializeBeds(void);
void displaySpecialties(void);
void displayWards(void);
void registerPatient(void);
void allocateBed(int patientIndex);
int getPatientCount(void);
int findPatientByID(int patientID);
double calculateWaitingTime(int specialtyIndex);
double calculateWardCost(int patientIndex);
double calculateGrossTotal(int patientIndex);
double calculateDiscount(int patientIndex);
double calculateFinalPayable(int patientIndex);
double calculateSurcharge(int patientIndex);
void displayPatientBill(int patientIndex);

#endif