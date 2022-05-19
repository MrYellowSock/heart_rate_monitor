#include <Arduino.h>
#include <pulse.h>
#include <bpm.h>
#include <patient.h>

#define BAUD 57600
#define heartPin A6
#define buzzPin 2
#define ledPin 13
#define inactiveDuration 5000
#define dangerDuration 10000
#define collectInterval 20

void printLabel(char * label,int val){
    Serial.print(label);Serial.print(val);Serial.print(", ");
}

void setup()
{
    // put your setup code here, to run once:
    pinMode(ledPin, OUTPUT);
    pinMode(buzzPin, OUTPUT);
    pinMode(heartPin, INPUT);
    Serial.begin(BAUD);
}
char readBuff[3];
void serialEvent() {    //age input event.
    Serial.readBytesUntil(0,readBuff,3);
    setAge((uint8_t)atoi(readBuff));     //just took the first bite.
}


unsigned long lastRead = 0;
unsigned long lastActivity = 0;
unsigned long lastSafe = 0;
unsigned long curRead = 0;
void loop()
{
    curRead = millis();
    if (curRead - lastRead >= collectInterval)
    {
        int val = analogRead(heartPin);
        lastRead = curRead;
        bool changed = react(val);
        if (changed)
        {
            registerPulseState(getPulseState());
            digitalWrite(ledPin, getPulseState());
            tone(buzzPin, getPulseState()?1000:0,10);
            lastActivity = curRead;
        }
        heartRange hr = getRange();
        int lb,ub;
        getSafeRange(hr,lb,ub);

        if(curRead - lastActivity >= inactiveDuration){
            inactive();
        }
        if(isSafe(getBPM(),lb,ub)){
            lastSafe = curRead;
        }
        if(curRead - lastSafe >= dangerDuration){
            tone(buzzPin, 2000,1000);
        }

        printLabel("val:",val/16);
        printLabel("bpm:",getBPM());
        printLabel("state:",getPulseState() ? 40 : 0);
        printLabel("in1:",hr.rate1);
        printLabel("in2:",hr.rate2);
        printLabel("out1:",lb);
        printLabel("out2:",ub);
        Serial.println();
    }
}