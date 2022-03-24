#include <Arduino.h>
#define PIN_HEART_RATE_INPUT 2


uint32_t heartPumped = 0;
void onHeartPumped()        //add value to heart rate when sensor value changed
{
    heartPumped++;
}
void setup()
{
    Serial.begin(9600);
    pinMode(PIN_HEART_RATE_INPUT, INPUT);
    attachInterrupt(PIN_HEART_RATE_INPUT, onHeartPumped, RISING);
}

unsigned long currentTime = 0;
unsigned long previousTime = 0;

void loop()
{
    currentTime = millis();
    if (currentTime - previousTime >= 1000*60) //1 minute has passed
    {
        Serial.print("Heart rate : ");
        Serial.println(heartPumped);
        
        heartPumped = 0; // clear heart rate value.
        previousTime = currentTime;
    }
}