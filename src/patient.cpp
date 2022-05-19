#define defaultAge 19
#define rangeCnt 8
#define safeTolerancePercent 0.07
#include <Arduino.h>
#include <patient.h>

heartRange hr[rangeCnt] = {
    {0, 9, 90, 125},
    {10, 14, 85, 90},
    {15, 19, 80, 85},
    {20, 29, 75, 80},
    {30, 39, 70, 75},
    {40, 49, 65, 70},
    {50, 59, 60, 65},
    {60, 200, 50, 60}
};
uint8_t age = defaultAge;

void setAge(uint8_t target){
    age = target;
}
uint8_t getAge(){
    return age;
}
heartRange getRange(){
    for(int i=0;i<rangeCnt;i++){
        if(age >= hr[i].age1 && age <= hr[i].age2){
            return hr[i];
        }
    }
    return hr[rangeCnt-1];  //last one
}
void getSafeRange(heartRange h,int & lowerBound,int & upperBound){
    lowerBound = h.rate1 * (1.0-safeTolerancePercent);
    upperBound = h.rate2 * (1.0+safeTolerancePercent);
}
bool isSafe(int rate,int & lowerBound,int & upperBound){
    return rate >= lowerBound && rate <= upperBound;
}