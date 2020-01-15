#include <iostream>
#include <fstream>
#include <vector>
#include "course.h"
#include <algorithm>
#include <iomanip>

//create a vector of course objects
void create_objects(std::vector<std::string> &data, std::vector<course> &courses, std::vector<std::string> &rooms){
    //build data. use the format of the input files to create
    //course objects and then pass them into a vector.
    for (int i=0; i<data.size()-8; i+=8){
        for(int j=0;j<data[i+4].size();j++) {
            course example(data[i], data[i + 1], data[i + 2], data[i + 3], data[i + 4] [j], data[i + 5], data[i + 6],
                           data[i + 7]);
            courses.push_back(example);
        }
        rooms.push_back(data[i + 7]);
    }
}
bool sort_if_room(const course &class1, const course &class2){
    //rooms and dept have different formatting so create two functions that will be
    //used in the std::sort method depending on the command line.
    if(class1.getDay_Value()<class2.getDay_Value()){
        return true;
    }
    else if(class1.getDay_Value()==class2.getDay_Value() and class1.getMilitary_Start()<class2.getMilitary_Start()){
        return true;
    }
    else if(class1.getDay_Value()==class2.getDay_Value() and class1.getMilitary_Start()==class2.getMilitary_Start()
                and class1.getFloatCode()<class2.getFloatCode()){
        return true;
    }
    else if(class1.getDay_Value()==class2.getDay_Value() and class1.getMilitary_Start()==class2.getMilitary_Start()
            and class1.getFloatCode()==class2.getFloatCode() and class1.getDept()<class2.getDept()){
        return true;
    }
    else{
        return false;
    }
}
bool sort_if_dept(const course &class1, const course &class2){
    //these functions will be passed into std::sort as the third argument
    //which serves as a key when working with custom class objects
    if(class1.getFloatCode()<class2.getFloatCode()){
        return true;
    }
    else if(class1.getDay_Value()<class2.getDay_Value() and class1.getFloatCode()==class2.getFloatCode()){
        return true;
    }
    else if(class1.getDay_Value()==class2.getDay_Value() and class1.getFloatCode()==class2.getFloatCode()
                and class1.getMilitary_Start()<class2.getMilitary_Start()){
        return true;
    }
    else{
        return false;
    }
}
void specified_room(std::string &parameter,std::vector<course> &courses,std::ofstream &out_str ){
    //add courses that have the matching room number
    std::vector<course> matching;
    for (int i=0;i<courses.size();i++){
        if (courses[i].getRoom()==parameter){
            matching.push_back(courses[i]);
        }
    }
    //break condition
    if (matching.size()==0){
        out_str<<"No data available."<<std::endl;
        out_str.close();
        return;
    }
    //determine the dashes
    int dash_dept=4;
    int dash_coursenum= 9;
    int dash_classtitle = 11;
    int dash_day=3;
    int dash_start=10;
    int dash_end=8;
    for (int i=0; i<matching.size();i++){
        if(matching[i].getCode().size()>dash_coursenum){
            dash_coursenum=matching[i].getCode().size();
        }
        if(matching[i].getTitle().size()>dash_classtitle){
            dash_classtitle=matching[i].getTitle().size();
        }
        if(matching[i].getRealDay().size()>dash_day){
            dash_day=matching[i].getRealDay().size();
        }
        if (matching[i].getDept().size()>dash_dept){
            dash_dept=matching[i].getDept().size();
        }
    }
    //formatting and output
    std::sort(matching.begin(),matching.end(),sort_if_room);
    out_str<<"Room "<<parameter<<std::endl;
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_dept)<<"Dept" <<"  ";
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_coursenum)<<"Coursenum" <<"  ";
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_classtitle)<<"Class Title" <<"  ";
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_day)<<"Day" <<"  ";
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_start)<<"Start Time" <<"  ";
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_end)<<"End Time" <<std::endl;

    out_str<<std::left<<std::setfill('-')<<std::setw(dash_dept)<<"" <<"  ";
    out_str<<std::left<<std::setfill('-')<<std::setw(dash_coursenum)<<"" <<"  ";
    out_str<<std::left<<std::setfill('-')<<std::setw(dash_classtitle)<<"" <<"  ";
    out_str<<std::left<<std::setfill('-')<<std::setw(dash_day)<<"" <<"  ";
    out_str<<std::left<<std::setfill('-')<<std::setw(dash_start)<<"" <<"  ";
    out_str<<std::left<<std::setfill('-')<<std::setw(dash_end)<<"" <<std::endl;
    for(int i=0;i<matching.size();i++){
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_dept)<<matching[i].getDept()<<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_coursenum)<<matching[i].getCode()<<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_classtitle)<<matching[i].getTitle()<<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_day)<<matching[i].getRealDay()<<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_start)<<matching[i].getStart()<<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_end)<<matching[i].getEnd()<<std::endl;
    }
    out_str<<matching.size()<<" entries"<<std::endl;
    out_str.close();
}
void specified_dept(std::string &parameter,std::vector<course> &courses,std::ofstream &out_str ){
    //add in all the courses that have the Dept
    std::vector<course> matching;
    for (int i=0;i<courses.size();i++){
        if (courses[i].getDept()==parameter){
            matching.push_back(courses[i]);
        }
    }
    //break condition
    if (matching.size()==0){
        out_str<<"No data available."<<std::endl;
        out_str.close();
        return;
    }
    //determining the dashes by checking the sizes
    int dash_coursenum= 9;
    int dash_classtitle = 11;
    int dash_day=3;
    int dash_start=10;
    int dash_end=8;
    for (int i=0; i<matching.size();i++){
        if(matching[i].getCode().size()>dash_coursenum){
            dash_coursenum=matching[i].getCode().size();
        }
        if(matching[i].getTitle().size()>dash_classtitle){
            dash_classtitle=matching[i].getTitle().size();
        }
        if(matching[i].getRealDay().size()>dash_day){
            dash_day=matching[i].getRealDay().size();
        }
    }
    //output and formatting
    std::sort(matching.begin(),matching.end(),sort_if_dept);
    out_str<<"Dept "<<parameter<<std::endl;
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_coursenum)<<"Coursenum" <<"  ";
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_classtitle)<<"Class Title" <<"  ";
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_day)<<"Day" <<"  ";
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_start)<<"Start Time" <<"  ";
    out_str<<std::left<<std::setfill(' ')<<std::setw(dash_end)<<"End Time" <<std::endl;

    out_str<<std::left<<std::setfill('-')<<std::setw(dash_coursenum)<<"" <<"  ";
    out_str<<std::left<<std::setfill('-')<<std::setw(dash_classtitle)<<"" <<"  ";
    out_str<<std::left<<std::setfill('-')<<std::setw(dash_day)<<"" <<"  ";
    out_str<<std::left<<std::setfill('-')<<std::setw(dash_start)<<"" <<"  ";
    out_str<<std::left<<std::setfill('-')<<std::setw(dash_end)<<"" <<std::endl;

    for(int i=0;i<matching.size();i++){
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_coursenum)<<matching[i].getCode()<<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_classtitle)<<matching[i].getTitle()<<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_day)<<matching[i].getRealDay()<<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_start)<<matching[i].getStart()<<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_end)<<matching[i].getEnd()<<std::endl;
    }
    out_str<<matching.size()<<" entries"<<std::endl;
    out_str<<std::endl;
    out_str.close();
}
void custom(std::vector<course> &courses,std::ofstream &out_str ){
    //specifically search for courses that are 1000 level for freshmen
    std::vector<std::string> valid_names;
    std::vector<course> freshmancourse;
    for(int i=0; i<courses.size();i++){
        if((courses[i].getFloatCode()-1000)<1000){
            freshmancourse.push_back(courses[i]);
            valid_names.push_back(courses[i].getRoom());
        }
    }
    //break condition
    if (freshmancourse.size()==0){
        out_str<<"No data available."<<std::endl;
        out_str.close();
        return;
    }
    //the new vector of rooms needs to be unique for clean output so do it again here
    std::sort(valid_names.begin(), valid_names.end());
    std::vector<std::string>::iterator unique_rooms = std::unique(valid_names.begin(), valid_names.end());
    valid_names.resize(std::distance(valid_names.begin(), unique_rooms));

    out_str<<"Freshman are going to be found in these rooms. Be prepared:"<<std::endl;
    std::sort(valid_names.begin(),valid_names.end());
    //main part of the output
    for (int k=0; k<valid_names.size();k++){
        std::vector<course> matching;
        for (int j=0;j<freshmancourse.size();j++ ){
            if(freshmancourse[j].getRoom()==valid_names[k]){
                matching.push_back(freshmancourse[j]);
            }
        }
        //determining the dashes
        int dash_dept=4;
        int dash_coursenum= 9;
        int dash_classtitle = 11;
        int dash_day=3;
        int dash_start=10;
        int dash_end=8;
        for (int i=0; i<matching.size();i++){
            if(matching[i].getCode().size()>dash_coursenum){
                dash_coursenum=matching[i].getCode().size();
            }
            if(matching[i].getTitle().size()>dash_classtitle){
                dash_classtitle=matching[i].getTitle().size();
            }
            if(matching[i].getRealDay().size()>dash_day){
                dash_day=matching[i].getRealDay().size();
            }
            if (matching[i].getDept().size()>dash_dept){
                dash_dept=matching[i].getDept().size();
            }
        }
        //output and formatting as stated in the guidelines
        std::sort(matching.begin(),matching.end(),sort_if_room);
        out_str<<"Room "<<valid_names[k]<<std::endl;
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_dept)<<"Dept" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_coursenum)<<"Coursenum" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_classtitle)<<"Class Title" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_day)<<"Day" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_start)<<"Start Time" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_end)<<"End Time" <<std::endl;

        out_str<<std::left<<std::setfill('-')<<std::setw(dash_dept)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_coursenum)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_classtitle)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_day)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_start)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_end)<<"" <<std::endl;
        for(int i=0;i<matching.size();i++){
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_dept)<<matching[i].getDept()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_coursenum)<<matching[i].getCode()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_classtitle)<<matching[i].getTitle()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_day)<<matching[i].getRealDay()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_start)<<matching[i].getStart()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_end)<<matching[i].getEnd()<<std::endl;
        }
        out_str<<matching.size()<<" entries"<<std::endl;
        out_str<<std::endl;
        matching.clear();
    }
    out_str.close();
}
void unspecified_room(std::vector<std::string> rooms,std::vector<course> &courses,std::ofstream &out_str ){
    //loop through the organized vector of rooms. If there are matches you output according to the guidelines
    for (int j=0; j<rooms.size();j++) {
        std::vector<course> matching;
        for (int i = 0; i < courses.size(); i++) {
            if (courses[i].getRoom() == rooms[j]) {
                matching.push_back(courses[i]);
            }
        }
        //break condition
        std::sort(matching.begin(), matching.end(), sort_if_room);
        if (matching.size()==0){
            out_str<<"No data available."<<std::endl;
            out_str.close();
            return;
        }
        //determines how many dashes are going to be needed by checking size
        //of elements
        int dash_dept=4;
        int dash_coursenum= 9;
        int dash_classtitle = 11;
        int dash_day=3;
        int dash_start=10;
        int dash_end=8;
        for (int i=0; i<matching.size();i++){
            if(matching[i].getCode().size()>dash_coursenum){
                dash_coursenum=matching[i].getCode().size();
            }
            if(matching[i].getTitle().size()>dash_classtitle){
                dash_classtitle=matching[i].getTitle().size();
            }
            if(matching[i].getRealDay().size()>dash_day){
                dash_day=matching[i].getRealDay().size();
            }
            if (matching[i].getDept().size()>dash_dept){
                dash_dept=matching[i].getDept().size();
            }
        }
        //formatting and structuring the output
        std::sort(matching.begin(),matching.end(),sort_if_room);
        out_str<<"Room "<<rooms[j]<<std::endl;
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_dept)<<"Dept" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_coursenum)<<"Coursenum" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_classtitle)<<"Class Title" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_day)<<"Day" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_start)<<"Start Time" <<"  ";
        out_str<<std::left<<std::setfill(' ')<<std::setw(dash_end)<<"End Time" <<std::endl;

        out_str<<std::left<<std::setfill('-')<<std::setw(dash_dept)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_coursenum)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_classtitle)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_day)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_start)<<"" <<"  ";
        out_str<<std::left<<std::setfill('-')<<std::setw(dash_end)<<"" <<std::endl;
        for(int i=0;i<matching.size();i++){
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_dept)<<matching[i].getDept()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_coursenum)<<matching[i].getCode()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_classtitle)<<matching[i].getTitle()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_day)<<matching[i].getRealDay()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_start)<<matching[i].getStart()<<"  ";
            out_str<<std::left<<std::setfill(' ')<<std::setw(dash_end)<<matching[i].getEnd()<<std::endl;
        }
        out_str<<matching.size()<<" entries"<<std::endl;
        out_str<<std::endl;
        matching.clear();
    }
    out_str.close();
}

int main( int argc, char* argv[]) {
    //open input and output stream with bad file check
    std::ifstream in_str(argv[1]);
    if (!in_str.good()) {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    std::ofstream out_str(argv[2]);
    if (!out_str.good()) {
        std::cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }
    //variable declaration
    std::vector <std::string> data;
    std::vector <std::string> rooms;
    std::vector<course> courses;
    std::string info;
    std::string output;
    std::string parameter;

    //create a vector of the input data
    while (!in_str.eof()) {
        in_str >> info;
        if (info.size()!=0) {
            data.push_back(info);
        }
    }

    if(data.size()>0) {
        if (argc == 4) {
            std::string output(argv[3]);
        } else if (argc == 5) {
            output = std::string(argv[3]);
            parameter = std::string(argv[4]);
        }
        //function call
        create_objects(data, courses, rooms);

        //unique room vector creation
        std::sort(rooms.begin(), rooms.end());
        std::vector<std::string>::iterator unique_rooms = std::unique(rooms.begin(), rooms.end());
        rooms.resize(std::distance(rooms.begin(), unique_rooms));

        //call the functions for outputting
        if (output == std::string("room") and parameter.size() != 0) {
            specified_room(parameter, courses, out_str);
        } else if (output == std::string("dept") and parameter.size() != 0) {
            specified_dept(parameter, courses, out_str);
        } else if (std::string(argv[3]) == std::string("room") and argc == 4) {
            unspecified_room(rooms, courses, out_str);
        }
        else if (std::string(argv[3]) == std::string("custom") and argc==4) {
            custom(courses, out_str);
        }
    }
    else{
        //empty txt clause
        out_str<<"No data available."<<std::endl;
        out_str.close();
    }
    return 0;
}
