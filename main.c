#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxRecords 100


char patientNames[maxRecords][50];
int patientAges[maxRecords];

int patientTriageLevels[maxRecords];

int patientSpecialtyChoices[maxRecords];

int patientAdmittedStatuses[maxRecords];

int patientWards[maxRecords];

int patientStayDays[maxRecords];

int patientCount = 0;

const char specialtyList[4][30] = {"General Practical (OPD)", "Paediatrics", "Cardiology", "Neurology"};
const float specialtyFees[4] = {1500.00, 2500.00, 4500.00, 5000.00};
const int specialtyConsultTimes[4] = {15, 20, 30, 30};
int specialtyQueueTrackers[4] = {0, 0, 0, 0};


const char wardList[4][30] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};
const float wardDailyRates[4] = {3000.00, 6000.00, 12000.00, 25000.00};
const int wardCapacities[4] = {20, 10, 10, 5};

int wardBeds[4][20];

void setupSystem(void) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 20; j++) {
            wardBeds[i][j] = 0;
        }
    }
}

int findAvailableBed(int wardId) {
    int wardIndex = wardId - 1;
    for (int bed = 0; bed < wardCapacities[wardIndex]; bed++) {
        if (wardBeds[wardIndex][bed] == 0) {
            return bed + 1;
        }
    }
    return -1;
}

void addPatientRecord(void) {
    if (patientCount >= maxRecords)
{
        printf("\nSystem Full! Cannot register more patients.\n");
        return;
    }

    printf("\n-----Patient Registration-----\n");

    printf("Enter Patient Name: ");
    scanf(" %[^\n]s", patientNames[patientCount]);

    printf("Enter Age: ");
    scanf("%d", &patientAges[patientCount]);

    printf("Enter Triage Level (1- Emergency, 2- Urgent, 3-Routine): ");
    scanf("%d", &patientTriageLevels[patientCount]);

    printf("\nSelect Specialty Choice:\n");
    for (int idx = 0; idx < 4; idx++) {
        printf("%d. %s\n", idx + 1, specialtyList[idx]);
    }
    printf("Choice (1-4): ");
    scanf("%d", &patientSpecialtyChoices[patientCount]);

    // Increment queue tracker for selected specialty
    int selectedSpecialtyIndex = patientSpecialtyChoices[patientCount] - 1;
    if (selectedSpecialtyIndex >= 0 && selectedSpecialtyIndex < 4) {
        specialtyQueueTrackers[selectedSpecialtyIndex]++;
    }

    patientAdmittedStatuses[patientCount] = 0;
    patientWards[patientCount] = -1;
    patientStayDays[patientCount] = 0;

    patientCount++;
    printf("\nPatient registered successfully!(Patient ID:%d)\n", patientCount);
    printf("----------------------------------------\n");


    printf("\n    SPECIALITY QUEUE SUMMARY\n");
    printf("----------------------------------------\n");
    for (int idx = 0; idx < 4; idx++) {
        int estimatedWaitTime = specialtyQueueTrackers[idx] * specialtyConsultTimes[idx];
        printf("%d. %-23s |Queue:%d patients| Est.Wait:%d mins\n",
               idx + 1, specialtyList[idx], specialtyQueueTrackers[idx], estimatedWaitTime);
    }
}

int main(void) {
    setupSystem();
    addPatientRecord();
    return 0;
}
