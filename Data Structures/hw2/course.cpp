//
// Created by ahmeds7 on 1/21/2019.
//

#include "course.h"
#include <iostream>
#include <sstream>
#include <string>

course::course() {
    //default constructor
    std::string crn = " ";
    std::string dept = " ";
    std::string code = " ";
    std::string title = " ";
    std::string days = " ";
    std::string start = " ";
    std::string end = " ";
    std::string room=" ";
}
course::course(std::string acrn, std::string adept,std::string acode,
        std::string atitle,char adays,std::string astart,std::string aend,std::string aroom) {
    //matching given inputs to attribute values
    crn=acrn;
    days=adays;
    start=astart;
    dept=adept;
    code = acode;
    //turn the code into a float for comparison
    floatcode=float(stoi(acode.substr(0,4))) + float(stoi(acode.substr(5,2)))/float(100);
    title=atitle;
    end=aend;
    room=aroom;
    //this block turns the start times and the end times into military time
    //and as floats for easy comparison later down the line
    if (astart.substr(5)=="PM"){
        int hour = stoi(astart.substr(0,2));
        float minute = float(stoi(astart.substr(3,2)))/100;
        if ((hour+12)%24==0){
            hour=12;
        }
        else{
            hour=(hour+12)%24;
        }
        military_start=float(hour)+minute;
    }
    else{
        int hour = stoi(astart.substr(0,2));
        float minute = float(stoi(astart.substr(3,2)))/100;
        military_start=float(hour)+minute;
    }
    if (aend.substr(5)=="PM"){
        int hour = stoi(aend.substr(0,2));
        float minute = float(stoi(aend.substr(3,2)))/100;
        if ((hour+12)%24==0){
            hour=12;
        }
        else{
            hour=(hour+12)%24;
        }
        military_end=float(hour)+minute;
    }
    else{
        int hour = stoi(aend.substr(0,2));
        float minute = float(stoi(aend.substr(3,2)))/100;
        military_end=float(hour)+minute;
    }
    //to compare days of the week. set each day to a specific int value
    //for comparison in std::sort
    if (days== 'M'){
        day_value=1;
        realday="Monday";
    }
    else if (days== 'T'){
        day_value=2;
        realday="Tuesday";
    }
    else if (days== 'W'){
        day_value=3;
        realday="Wednesday";
    }
    else if (days== 'R'){
        day_value=4;
        realday="Thursday";
    }
    else if (days== 'F'){
        day_value=5;
        realday="Friday";
    }
}
//all the get functions
std::string course:: getCrn()const{
    return crn;
}
std::string course::getDept()const{
    return dept;
}
std::string course::getRoom()const{
    return room;
}
int course::getDay_Value()const{
    return day_value;
}
float course::getFloatCode()const{
    return floatcode;
}
std::string course::getCode()const{
    return code;
}
float course::getMilitary_Start()const{
    return military_start;
}
float course::getMilitary_End()const{
    return military_end;
}
std::string course::getStart()const{
    return start;
}
std::string course::getEnd()const{
    return end;
}
std::string course::getTitle()const{
    return title;
}
std::string course::getRealDay() const{
    return realday;
}
char course::getDays()const{
    return days;
}
