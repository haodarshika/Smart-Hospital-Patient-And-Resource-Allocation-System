#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  maxRecords 100

char patientNames[maxRecords];
int patientAges[maxRecords];
int triageLevel[maxRecords];
int specialtyChoice[maxRecords];
int isAdmitted[maxRecords];
int assignedWard[maxRecords];
int stayDays[maxRecords];
int patientCount =0;


const char specialityTitles[4][30]={"General Practical(OPD)","Paediatrics","Cardiology","Neurology"};
const float specialityFees[4]={1500.00,2500.00,4500.00,5000.00};
const int specialityConsultantTime[4]={15,20,30,30};
int specialityQueueTracker[4]={0,0,0,0};

const char wardNames[4][30]={"General Ward","Paediatric Ward","Surgical Ward","ICU"};
const float wardDailyRates[4]={3000.00, 6000.00,12000.00,25000.00};
const int  wardCapacities[4]={20,10,10,5};



int bedMatrix[4][20];
void initHospitalData(void){
      int w,b;
      for (w=0;w<4;w++){
            for (b=0;b<20;b++){
                    bedMatrix[w][b]=0;
            }
      }
}
int allocateBed(int targetWardId){
    int wIdx =targetWardId-1;
    for (int slot =0;slot<wardCapacities[wIdx];slot++){
         if(bedMatrix[wIdx][slot]==0){
            return slot +1;
         }
    }
    return -1;
}
void registrationPatient(void){
    if (patientCount>=maxRecords){
        printf("\nSystem Full! Cannot register more patients.\n");
        return;
    }
    printf("\n----Patient Registration-----\n");
    printf("Enter Patient Name:");
    scanf("%[^\n]s",patientNames[patientCount]);
    printf("Enter Age:");
    scanf ("%d",&patientAges[patientCount]);
    printf("Enter Triage Level (1- Emergency,2- Urgent,3-Routine):");
    scanf("%d",&triageLevel[patientCount]);
    printf("\nSelect Specialty Choice:\n");
    for(int i=0;i<4;i++){
        printf("%d. %s\n",i+1 , specialityTitles[i]);
    }
    printf("Choice (1-4):");
    scanf("%d",&specialtyChoice[patientCount]);
    isAdmitted[patientCount]=0;
    assignedWard[patientCount]= -1;
    stayDays[patientCount]=0;
    printf("\nPatient registered successfully!(Patient ID:%d)\n",patientCount +1);
    patientCount++;
}


int main(void){
    initHospitalData();
    registrationPatient();

    return 0;

}








