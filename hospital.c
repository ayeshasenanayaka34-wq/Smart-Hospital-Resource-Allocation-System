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

int queueCount[NUM_SPECIALTIES] = {0, 0, 0, 0};

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
int patientID[MAX_PATIENTS];
char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int urgencyLevel[MAX_PATIENTS];
int specialtyID[MAX_PATIENTS];
int wardID[MAX_PATIENTS];
int admitted[MAX_PATIENTS];
int daysAdmitted[MAX_PATIENTS];
int registrationOrder[MAX_PATIENTS];
int patientCount = 0;
int getPatientCount(void)
{
    return patientCount;
}
int findPatientByID(int id)
{
    int i;

    for (i = 0; i < patientCount; i++)
    {
        if (patientID[i] == id)
        {
            return i;
        }
    }

    return -1;
}

double baseFee[MAX_PATIENTS];
double surcharge[MAX_PATIENTS];
double wardCost[MAX_PATIENTS];
double grossTotal[MAX_PATIENTS];
double discount[MAX_PATIENTS];
double finalPayable[MAX_PATIENTS];
double waitingTime[MAX_PATIENTS];
int bedNumber[MAX_PATIENTS];

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
        printf("%d. %s - Rs. %.2f/day - Capacity: %d beds\n",i + 1, wardName[i], wardDailyRate[i], wardCapacity[i]);
    }
}

double calculateSurcharge(int patientIndex);

void registerPatient(void)
{
    if (patientCount >= MAX_PATIENTS)
    {
        printf("Maximum patient limit reached.\n");
        return;
    }
    patientID[patientCount] = 1001 + patientCount;
    
    printf("\nEnter Patient Name: ");
    scanf(" %[^\n]", patientName[patientCount]);

    printf("Enter Age: ");
    scanf("%d", &patientAge[patientCount]);

    do
    {
        printf("Enter Urgency Level (1-Normal, 2-Urgent, 3-Critical): ");
        scanf("%d", &urgencyLevel[patientCount]);
        
        if (urgencyLevel[patientCount] < 1 || urgencyLevel[patientCount] > 3)
        {
            printf("Invalid urgency level. Please enter 1, 2, or 3.\n");
        }
    } while (urgencyLevel[patientCount] < 1 || urgencyLevel[patientCount] > 3);

    displaySpecialties();

    do
    {
        printf("Enter Specialty ID (1-4): ");
        scanf("%d", &specialtyID[patientCount]);
        
        if (specialtyID[patientCount] < 1 || specialtyID[patientCount] > 4)
        {
            printf("Invalid specialty ID. Please enter 1-4.\n");
        }
        else if (queueCount[specialtyID[patientCount] - 1] >= dailyPatientCap[specialtyID[patientCount] - 1])
        {
            printf("Daily patient cap reached for this specialty.\n");
        }
    
    } while (specialtyID[patientCount] < 1 ||
         specialtyID[patientCount] > 4 ||
         queueCount[specialtyID[patientCount] - 1] >=
         dailyPatientCap[specialtyID[patientCount] - 1]);

    baseFee[patientCount] = consultationFee[specialtyID[patientCount] - 1];
    surcharge[patientCount] = calculateSurcharge(patientCount);
    waitingTime[patientCount] = calculateWaitingTime(specialtyID[patientCount] - 1);

    do
    {
        printf("Is the patient admitted? (1-Yes, 0-No): ");
        scanf("%d", &admitted[patientCount]);

        if (admitted[patientCount] != 0 && admitted[patientCount] != 1)
        {
            printf("Invalid input. Please enter 1 or 0.\n");
        }
    } while (admitted[patientCount] != 0 && admitted[patientCount] != 1);
    

    if (admitted[patientCount] == 1)
    {
        displayWards();
        
        do
        {
            printf("Enter Ward ID (1-4): ");
            scanf("%d", &wardID[patientCount]);
            
            if (wardID[patientCount] < 1 || wardID[patientCount] > 4)
            {
                printf("Invalid ward ID. Please enter 1-4.\n");
            }

        } while (wardID[patientCount] < 1 || wardID[patientCount] > 4);

        do
        {
            printf("Enter Number of Days Admitted: ");
            scanf("%d", &daysAdmitted[patientCount]);
            
            if (daysAdmitted[patientCount] < 1)
            {
                printf("Invalid number of days. Please enter at least 1.\n");
            }
        } while (daysAdmitted[patientCount] < 1);
        
        allocateBed(patientCount);
    }

    else
    { 
        wardID[patientCount] = 0;
        daysAdmitted[patientCount] = 0;
    }
    wardCost[patientCount] = calculateWardCost(patientCount);
    grossTotal[patientCount] = calculateGrossTotal(patientCount);
    discount[patientCount] = calculateDiscount(patientCount); 
    finalPayable[patientCount] = calculateFinalPayable(patientCount); 
    registrationOrder[patientCount] = patientCount + 1;
    queueCount[specialtyID[patientCount] - 1]++;
    patientCount++;
    
    printf("\nPatient registered successfully.\n");
}

void allocateBed(int patientIndex)
{
    int wardIndex;
    int bedIndex;

    if (admitted[patientIndex] == 0)
    {
        wardID[patientIndex] = 0;
        return;
    }

    wardIndex = wardID[patientIndex] - 1;

    for (bedIndex = 0; bedIndex < wardCapacity[wardIndex]; bedIndex++)
    {
        if (bedOccupancy[wardIndex][bedIndex] == 0)
        {
            bedOccupancy[wardIndex][bedIndex] = 1;
            bedNumber[patientIndex] = bedIndex + 1;

            printf("Bed allocated: Ward %d, Bed %d\n",wardID[patientIndex],bedIndex + 1);

            return;
        }
    }
    printf("No available bed in the selected ward.\n");
    printf("Patient will be registered as an outpatient.\n");
    admitted[patientIndex] = 0;
    wardID[patientIndex] = 0;
    daysAdmitted[patientIndex] = 0;
    bedNumber[patientIndex] = 0;
}

double calculateWaitingTime(int specialtyIndex)
{
    return queueCount[specialtyIndex] * consultationTime[specialtyIndex];
}

double calculateSurcharge(int patientIndex)
{
    if (urgencyLevel[patientIndex] == 2)
    {
        return baseFee[patientIndex] * 0.20;
    }

    if (urgencyLevel[patientIndex] == 3)
    {
        return baseFee[patientIndex] * 0.50;
    }

    return 0.0;
}

double calculateWardCost(int patientIndex)
{
    if (admitted[patientIndex] == 1)
    {
        return daysAdmitted[patientIndex] * wardDailyRate[wardID[patientIndex] - 1];
    }

    return 0.0;
}

double calculateGrossTotal(int patientIndex)
{
    return baseFee[patientIndex]+ surcharge[patientIndex]+ wardCost[patientIndex];
}

double calculateDiscount(int patientIndex)
{
    if (patientAge[patientIndex] < 5 ||
        patientAge[patientIndex] > 65)
    {
        return grossTotal[patientIndex] * 0.15;
    }

    return 0.0;
}

double calculateFinalPayable(int patientIndex)
{
    return grossTotal[patientIndex] - discount[patientIndex];
}

void displayPatientBill(int patientIndex)
{
    printf("\n==============================================\n");
    printf("\n      SMART HOSPITAL ADMISSION & BILL\n");
    printf("\n----------------------------------------------\n");
    printf("Patient ID               : PAT-%d\n", patientID[patientIndex]);
    printf("Patient Name             : %s\n", patientName[patientIndex]);
    printf("Age                      : %d\n", patientAge[patientIndex]);
    printf("Specialty                : %s\n", specialtyName[specialtyID[patientIndex] - 1]);
    if (admitted[patientIndex] == 1){
        printf("Assigned Ward            : %s (Bed #%02d)\n",
           wardName[wardID[patientIndex] - 1],
           bedNumber[patientIndex]);
    }
    else{
        printf("Assigned Ward            : Not Admitted\n");
    }
    
    if (urgencyLevel[patientIndex] == 1){
        printf("Urgency Level            : Level 1 (Normal)\n");
    }
    else if (urgencyLevel[patientIndex] == 2){
        printf("Urgency Level            : Level 2 (Urgent)\n");
    }
    else if (urgencyLevel[patientIndex] == 3)
    {
        printf("Urgency Level            : Level 3 (Critical)\n");
    }
    printf("------------------------------------------------\n");

    if (admitted[patientIndex] == 1)
    {
        printf("Ward                     : %s\n", wardName[wardID[patientIndex] - 1]);

        printf("Days Admitted            : %d\n", daysAdmitted[patientIndex]);
    }
    else
    {
        printf("Ward                     : Not Admitted\n");
    }

    printf("Base Consultation Fee    : LKR %.2f\n", baseFee[patientIndex]);
    printf("Emergency Surcharge      : LKR %.2f\n", surcharge[patientIndex]);
    printf("Ward Stay Cost (%d Days)  : LKR %.2f\n", daysAdmitted[patientIndex], wardCost[patientIndex]);
    printf("------------------------------------------------\n");
    printf("Gross Total Bill         : LKR %.2f\n", grossTotal[patientIndex]);
    printf("Age Subsidy Discount     : LKR -%.2f\n", discount[patientIndex]);
    printf("------------------------------------------------\n");
    printf("Final Payable Amount     : LKR %.2f\n", finalPayable[patientIndex]);
    printf("Estimated Waiting Time   : %.2f mins\n", waitingTime[patientIndex]);
    printf("================================================\n");
}
void generateReport(void)
{
    int i, j;
    int criticalCount = 0;
    int urgentCount = 0;
    int normalCount = 0;

    double totalRevenue = 0.0;
    double totalDiscount = 0.0;

    int highestPatientIndex = -1;
    double highestBill = 0.0;

    printf("\n========================================\n");
    printf("       SMART HOSPITAL REPORT\n");
    printf("========================================\n");

    /* Patient urgency counts and financial totals */
    for (i = 0; i < patientCount; i++)
    {
        if (urgencyLevel[i] == 3)
        {
            criticalCount++;
        }
        else if (urgencyLevel[i] == 2)
        {
            urgentCount++;
        }
        else if (urgencyLevel[i] == 1)
        {
            normalCount++;
        }

        totalRevenue += finalPayable[i];
        totalDiscount += discount[i];

        /* Find highest-paying patient */
        if (i == 0 || finalPayable[i] > highestBill)
        {
            highestBill = finalPayable[i];
            highestPatientIndex = i;
        }
    }

    printf("\nPatient Summary\n");
    printf("----------------------------------------\n");
    printf("Critical Patients : %d\n", criticalCount);
    printf("Urgent Patients   : %d\n", urgentCount);
    printf("Normal Patients   : %d\n", normalCount);

    printf("\nFinancial Summary\n");
    printf("----------------------------------------\n");
    printf("Total Revenue     : LKR %.2f\n", totalRevenue);
    printf("Total Discounts   : LKR %.2f\n", totalDiscount);

    printf("\nWard Occupancy\n");
    printf("----------------------------------------\n");

    for (i = 0; i < NUM_WARDS; i++)
    {
        int occupiedBeds = 0;
        double occupancyPercentage;

        for (j = 0; j < wardCapacity[i]; j++)
        {
            if (bedOccupancy[i][j] == 1)
            {
                occupiedBeds++;
            }
        }

        occupancyPercentage =
            (occupiedBeds / (double)wardCapacity[i]) * 100.0;

        printf("%s : %.2f%% (%d/%d beds)\n",
               wardName[i],
               occupancyPercentage,
               occupiedBeds,
               wardCapacity[i]);
    }

    printf("\nHighest-Paying Patient\n");
    printf("----------------------------------------\n");

    if (highestPatientIndex != -1)
    {
        printf("Patient Name : %s\n", patientName[highestPatientIndex]);
        printf("Patient ID   : PAT-%d\n", patientID[highestPatientIndex]);
        printf("Total Bill   : LKR %.2f\n", finalPayable[highestPatientIndex]);
    }
    else
    {
        printf("No patients registered.\n");
    }

    printf("========================================\n");
}

void saveBedStatus(void)
{
    FILE *file;
    int i, j;

    file = fopen("beds_status.txt", "w");

    if (file == NULL)
    {
        printf("Unable to save bed status.\n");
        return;
    }

    for (i = 0; i < NUM_WARDS; i++)
    {
        for (j = 0; j < wardCapacity[i]; j++)
        {
            fprintf(file, "%d ", bedOccupancy[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}


void loadBedStatus(void)
{
    FILE *file;
    int i, j;

    file = fopen("beds_status.txt", "r");

    if (file == NULL)
    {
        return;
    }

    for (i = 0; i < NUM_WARDS; i++)
    {
        for (j = 0; j < wardCapacity[i]; j++)
        {
            fscanf(file, "%d", &bedOccupancy[i][j]);
        }
    }

    fclose(file);
}


void savePatientRecord(int patientIndex)
{
    FILE *file;

    file = fopen("patient_records.txt", "a");

    if (file == NULL)
    {
        printf("Unable to save patient record.\n");
        return;
    }

    fprintf(file,
            "Patient ID: PAT-%d | Name: %s | Age: %d | Specialty: %s | Final Bill: LKR %.2f\n",
            patientID[patientIndex],
            patientName[patientIndex],
            patientAge[patientIndex],
            specialtyName[specialtyID[patientIndex] - 1],
            finalPayable[patientIndex]);

    fclose(file);
}
void sortPatientsByPriority(void)
{
    int i, j;
    int tempInt;
    double tempDouble;
    char tempName[50];

    for (i = 0; i < patientCount - 1; i++)
    {
        for (j = i + 1; j < patientCount; j++)
        {
            if (urgencyLevel[i] < urgencyLevel[j] ||
                (urgencyLevel[i] == urgencyLevel[j] &&
                 registrationOrder[i] > registrationOrder[j]))
            {
                /* Swap patient name */
                strcpy(tempName, patientName[i]);
                strcpy(patientName[i], patientName[j]);
                strcpy(patientName[j], tempName);

                /* Swap integer data */
                tempInt = patientID[i];
                patientID[i] = patientID[j];
                patientID[j] = tempInt;

                tempInt = patientAge[i];
                patientAge[i] = patientAge[j];
                patientAge[j] = tempInt;

                tempInt = urgencyLevel[i];
                urgencyLevel[i] = urgencyLevel[j];
                urgencyLevel[j] = tempInt;

                tempInt = specialtyID[i];
                specialtyID[i] = specialtyID[j];
                specialtyID[j] = tempInt;

                tempInt = wardID[i];
                wardID[i] = wardID[j];
                wardID[j] = tempInt;

                tempInt = admitted[i];
                admitted[i] = admitted[j];
                admitted[j] = tempInt;

                tempInt = daysAdmitted[i];
                daysAdmitted[i] = daysAdmitted[j];
                daysAdmitted[j] = tempInt;

                tempInt = registrationOrder[i];
                registrationOrder[i] = registrationOrder[j];
                registrationOrder[j] = tempInt;

                tempInt = bedNumber[i];
                bedNumber[i] = bedNumber[j];
                bedNumber[j] = tempInt;

                /* Swap double data */
                tempDouble = baseFee[i];
                baseFee[i] = baseFee[j];
                baseFee[j] = tempDouble;

                tempDouble = surcharge[i];
                surcharge[i] = surcharge[j];
                surcharge[j] = tempDouble;

                tempDouble = wardCost[i];
                wardCost[i] = wardCost[j];
                wardCost[j] = tempDouble;

                tempDouble = grossTotal[i];
                grossTotal[i] = grossTotal[j];
                grossTotal[j] = tempDouble;

                tempDouble = discount[i];
                discount[i] = discount[j];
                discount[j] = tempDouble;

                tempDouble = finalPayable[i];
                finalPayable[i] = finalPayable[j];
                finalPayable[j] = tempDouble;

                tempDouble = waitingTime[i];
                waitingTime[i] = waitingTime[j];
                waitingTime[j] = tempDouble;
            }
        }
    }
}