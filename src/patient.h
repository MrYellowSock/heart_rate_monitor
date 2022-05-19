struct heartRange
{
    int age1, age2;
    int rate1, rate2;
};

void setAge(uint8_t target);
uint8_t getAge();
heartRange getRange();
void getSafeRange(heartRange h,int & lowerBound,int & upperBound);
bool isSafe(int rate,int & lowerBound,int & upperBound);