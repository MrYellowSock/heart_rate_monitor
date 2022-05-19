#include <Arduino.h>
#define averageSample 4
int rate = 0;
unsigned long lastHigh = 0;
uint8_t sum_cnt = 0;
int history[averageSample];
int getBPM()
{
    if (sum_cnt < averageSample)
    {
        return rate;
    }
    else
    {
        int sum = 0;
        for (int i = 0; i < averageSample; i++)
        {
            sum += history[i];
        }
        return sum / averageSample;
    }
}
void insertRate(int rate)
{
    if (sum_cnt < averageSample)
    {
        history[sum_cnt++] = rate;
    }
    else
    {
        for (int i = 1; i < averageSample; i++)
        {
            history[i - 1] = history[i];
        }
        history[averageSample - 1] = rate;
    }
}
void registerPulseState(bool pulseState)
{
    if (pulseState == HIGH)
    {
        if (lastHigh > 0)
        {
            rate = 60000 / (millis() - lastHigh);
            insertRate(rate);
        }
        lastHigh = millis();
    }
}
void inactive(){
    rate = 0;
    sum_cnt = 0;
}