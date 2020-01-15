//
// Created by ahmeds7 on 1/21/2019.
//

#ifndef HW2_COURSE_H
#define HW2_COURSE_H
#include <iostream>

class course {
public:
    //get functions to retrieve values
    std::string getCrn()const;
    std::string getDept()const;
    std::string getRoom()const;
    int getDay_Value()const;
    float getFloatCode()const;
    std::string getCode()const;
    float getMilitary_Start()const;
    float getMilitary_End()const;
    std::string getStart()const;
    std::string getEnd()const;
    std::string getTitle()const;
    std::string getRealDay() const;
    char getDays()const;

    //constructors
    course();
    course(std::string acrn, std::string adept,std::string acode,
            std::string atitle,char adays,std::string astart,std::string aend,std::string aroom);
private:
    //attributes and member variables
    std::string crn;
    std::string dept;
    std::string room;
    int day_value;
    float floatcode;
    std::string code;
    float military_start;
    float military_end;
    std::string start;
    std::string end;
    std::string title;
    std::string realday;
    char days;
};


#endif //HW2_COURSE_H
