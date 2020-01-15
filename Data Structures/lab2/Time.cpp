//
// Created by ahmeds7 on 1/23/2019.
//
#include<iostream>
#include <string>
#include "Time.h"
Time::Time() {
    hour= 0;
    minute = 0;
    second = 0;
    stringhour= std::to_string(hour);
    stringminute= std::to_string(minute);
    stringsecond= std::to_string(second);
}

Time::Time(int h,int m, int s) {
    hour = h;
    minute = m;
    second =s;
    stringhour= std::to_string(h);
    stringminute= std::to_string(m);
    stringsecond= std::to_string(s);
}
int Time::getHour()const {
    return hour;
}
int Time::getMinute() const {
    return minute;
}
int Time::getSecond()const {
    return second;
}
void Time::setHour(int ahour){
    hour = ahour;
    stringhour= std::to_string(ahour);
}
void Time::setMinute(int aminute){
    minute=aminute;
    stringminute= std::to_string(aminute);
}
void Time::setSecond(int asecond){
    second= asecond;
    stringsecond= std::to_string(asecond);
}
void Time::PrintAMPM() {
    if(stringhour.size()<2){
        stringhour="0"+stringhour;
    }
    if(stringminute.size()<2){
        stringminute="0"+stringminute;
    }
    if(stringsecond.size()<2){
        stringsecond="0"+stringsecond;
    }
    if (hour == 12){
        std::cout<<stringhour<<":"<<stringminute<<":"<<stringsecond<<" pm"<<std::endl;
    }
    else if (hour == 0){
        std::cout<<12<<":"<<stringminute<<":"<<stringsecond<<" am"<<std::endl;
    }
    else if (hour<12){
        std::cout<<stringhour<<":"<<stringminute<<":"<<stringsecond<<" am"<<std::endl;
    }
    else if (hour==24){
        std::cout<<"00"<<":"<<stringminute<<":"<<stringsecond<<" am"<<std::endl;
    }
    else if (hour>12){
        stringhour= std::to_string(hour-12);
        if(stringhour.size()<2){
            stringhour="0"+stringhour;
        }
        std::cout<<stringhour<<":"<<stringminute<<":"<<stringsecond<<" pm"<<std::endl;
    }
}
bool IsEarlierThan(const Time& t1, const Time& t2){
    if (t1.getHour()<t2.getHour()){
        return true;
    }
    else if (t1.getMinute()<t2.getMinute() and t1.getHour()==t2.getHour()){
        return true;
    }
    else if (t1.getSecond()<t2.getSecond() and t1.getHour()==t2.getHour() and t1.getMinute()== t2.getMinute()){
        return true;
    }
    else{
        return false;
    }
}
