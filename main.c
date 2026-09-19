#include <stdio.h>
#include "hospital.h"

int main(void)
{
    int choice;
    int patientIndex;

    printf("Smart Hospital System\n");

    initializeBeds();
    loadBedStatus();

    do
    {
        printf("\n==============================\n");
        printf("      SMART HOSPITAL MENU\n");
        printf("==============================\n");
        printf("1. Register Patient\n");
        printf("2. Display Patient Bill\n");
        printf("3. Display Specialties\n");
        printf("4. Display Wards\n");
        printf("5. Generate Report\n");
        printf("6. Exit\n");
        printf("==============================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            registerPatient();

            patientIndex = getPatientCount() - 1;

            allocateBed(patientIndex);
            saveBedStatus();

            displayPatientBill(patientIndex);
            savePatientRecord(patientIndex);
        }
        else if (choice == 2)
        {
            int patientID;

            printf("Enter Patient ID (1001, 1002, ...): ");
            scanf("%d", &patientID);

            patientIndex = findPatientByID(patientID);

            if (patientIndex != -1)
            {
                displayPatientBill(patientIndex);
            }
            else
            {
                printf("Patient not found.\n");
            }
        }
        else if (choice == 3)
        {
            displaySpecialties();
        }
        else if (choice == 4)
        {
            displayWards();
        }
        else if (choice == 5)
        {
            generateReport();
        }
        else if (choice == 6)
        {
            saveBedStatus();
            printf("Exiting Smart Hospital System...\n");
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}