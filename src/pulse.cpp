#include<Arduino.h>
// calibration needed
#define idleValue 160 // idle under this value.
#define nonsense_duration 200

unsigned long lastChange = 0;
int diff = 0;
bool prevState = false;
bool actualState = false;
bool actualState_prev = false;


bool shouldChangeActual(int diff)
{
    return abs(diff) > nonsense_duration;
}
/**
 * @brief return true if pulse state changed
 * 
 * @param val analogread value 
 * @return true 
 * @return false 
 */
bool react(int val)
{
    bool curState = val > idleValue;
    if (curState != prevState)
    {
        diff = millis() - lastChange;
        if (curState == HIGH)
        { // low signal is negaitive in value
            diff = -diff;
        }
        lastChange = millis();
        prevState = curState;
        if (diff < 0 && !shouldChangeActual(diff))
        {
            return;
        }
        actualState = curState;
    }
    bool changed = actualState != actualState_prev;
    if (changed)
    {
        actualState_prev = actualState;
    }
    return changed;
}
bool getPulseState(){
    return actualState;
}