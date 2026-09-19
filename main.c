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

int main(void){
    initHospitalData();
    printf("------Smart Hospital and Resource Allocation System -----\n");
    printf("Hospital system initialized successfully.\n");
    return 0;

}








