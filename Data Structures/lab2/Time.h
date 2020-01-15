//
// Created by ahmeds7 on 1/23/2019.
//

#ifndef LAB2_TIME_H
#define LAB2_TIME_H

#include <iostream>

class Time {
public:
    Time();
    Time(int h, int m, int s);
    int getHour() const;
    int getMinute()const ;
    int getSecond()const ;
    void setHour(int ahour);
    void setMinute(int aminute);
    void setSecond(int asecond);
    void PrintAMPM();
private:
    int hour;
    int minute;
    int second;
    std::string stringhour;
    std::string stringminute;
    std::string stringsecond;
};
bool IsEarlierThan(const Time& t1, const Time& t2);


#endif //LAB2_TIME_H
