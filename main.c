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
    if (patientCount >= maxRecords) {
        printf("\nSystem Full! Cannot register more patients.\n");
        return;
    }

    printf("\n-----Patient Registration-----\n");

    printf("Enter Patient Name: ");
    scanf(" %[^\n]s", patientNames[patientCount]);

    printf("Enter Age: ");
    scanf("%d", &patientAges[patientCount]);


    printf("Enter Urgency Level (1- Normal, 2- Urgent, 3- Critical): ");
    scanf("%d", &patientTriageLevels[patientCount]);

    printf("\nSelect Specialty Choice:\n");
    for (int idx = 0; idx < 4; idx++) {
        printf("%d. %s\n", idx + 1, specialtyList[idx]);
    }
    printf("Choice (1-4): ");
    scanf("%d", &patientSpecialtyChoices[patientCount]);

    int selectedSpecialtyIndex = patientSpecialtyChoices[patientCount] - 1;
    if (selectedSpecialtyIndex >= 0 && selectedSpecialtyIndex < 4) {
        specialtyQueueTrackers[selectedSpecialtyIndex]++;
    }

    printf("\nIs Admitted to Ward? (1- Yes, 0- No): ");
    scanf("%d", &patientAdmittedStatuses[patientCount]);

    if (patientAdmittedStatuses[patientCount] == 1) {
        printf("\nSelect Ward:\n");
        for (int i = 0; i < 4; i++) {
            printf("%d. %s\n", i + 1, wardList[i]);
        }
        printf("Choice (1-4): ");
        scanf("%d", &patientWards[patientCount]);

        printf("Enter Days Stayed: ");
        scanf("%d", &patientStayDays[patientCount]);

        int bNum = findAvailableBed(patientWards[patientCount]);
        if (bNum != -1) {
            wardBeds[patientWards[patientCount] - 1][bNum - 1] = 1;
            printf("Bed #%d booked.\n", bNum);
        } else {
            printf("Ward full!\n");
        }
    } else {
        patientWards[patientCount] = -1;
        patientStayDays[patientCount] = 0;
    }

    patientCount++;
    printf("\nPatient registered successfully!(Patient ID: PAT-%d)\n", 1000 + patientCount);
    printf("----------------------------------------\n");

    printf("\n    SPECIALITY QUEUE SUMMARY\n");
    printf("----------------------------------------\n");
    for (int idx = 0; idx < 4; idx++) {
        int estimatedWaitTime = specialtyQueueTrackers[idx] * specialtyConsultTimes[idx];
        printf("%d. %-23s |Queue:%d patients| Est.Wait:%d mins\n",
               idx + 1, specialtyList[idx], specialtyQueueTrackers[idx], estimatedWaitTime);
    }
}

void calculateBill(int pIdx) {
    if (pIdx < 0 || pIdx >= patientCount) {
        printf("Invalid patient ID!\n");
        return;
    }

    int sIdx = patientSpecialtyChoices[pIdx] - 1;
    float base = specialtyFees[sIdx];


    float surcharge = 0;
    if (patientTriageLevels[pIdx] == 2) surcharge = base * 0.20;
    else if (patientTriageLevels[pIdx] == 3) surcharge = base * 0.50;

    float wardTotal = 0;
    if (patientAdmittedStatuses[pIdx] == 1) {
        int wIdx = patientWards[pIdx] - 1;
        wardTotal = patientStayDays[pIdx] * wardDailyRates[wIdx];
    }

    float gross = base + surcharge + wardTotal;


    float discount = 0;
    if (patientAges[pIdx] < 5 || patientAges[pIdx] > 65) {
        discount = gross * 0.15;
    }

    float net = gross - discount;

    printf("\n--- PATIENT BILL ---\n");
    printf("Patient ID: PAT-%d\n", 1000 + pIdx + 1);
    printf("Name: %s\n", patientNames[pIdx]);
    printf("Base Fee: LKR %.2f\n", base);
    printf("Surcharge: LKR %.2f\n", surcharge);
    printf("Ward Charge: LKR %.2f\n", wardTotal);
    printf("Gross Amount: LKR %.2f\n", gross);
    printf("Discount: LKR -%.2f\n", discount);
    printf("Net Total: LKR %.2f\n", net);
}


void sortPatientsByPriority(void) {
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patientTriageLevels[j] < patientTriageLevels[j + 1]) {

                char tempName[50];
                strcpy(tempName, patientNames[j]);
                strcpy(patientNames[j], patientNames[j + 1]);
                strcpy(patientNames[j + 1], tempName);

                int tempAge = patientAges[j];
                patientAges[j] = patientAges[j + 1];
                patientAges[j + 1] = tempAge;

                int tempTriage = patientTriageLevels[j];
                patientTriageLevels[j] = patientTriageLevels[j + 1];
                patientTriageLevels[j + 1] = tempTriage;

                int tempSpec = patientSpecialtyChoices[j];
                patientSpecialtyChoices[j] = patientSpecialtyChoices[j + 1];
                patientSpecialtyChoices[j + 1] = tempSpec;

                int tempAdm = patientAdmittedStatuses[j];
                patientAdmittedStatuses[j] = patientAdmittedStatuses[j + 1];
                patientAdmittedStatuses[j + 1] = tempAdm;

                int tempWard = patientWards[j];
                patientWards[j] = patientWards[j + 1];
                patientWards[j + 1] = tempWard;

                int tempDays = patientStayDays[j];
                patientStayDays[j] = patientStayDays[j + 1];
                patientStayDays[j + 1] = tempDays;
            }
        }
    }
}

int main(void) {
    setupSystem();
    addPatientRecord();

    if (patientCount > 0) {
        calculateBill(0);
        sortPatientsByPriority();
    }

    return 0;
}
