//
// Created by ahmeds7 on 4/10/2019.
//

#ifndef HW9_MOVIE_H
#define HW9_MOVIE_H

#include <string>
#include <vector>
#include <iostream>

class movie {
public:
    //main constructor
    movie(std::string &tite, int y, int run, std::vector<std::string> &gere,
            std::vector<std::string> &actr, std::vector<std::string> &r){
        title=tite;
        year= y;
        genre= gere;
        actor = actr;
        roles = r;
        runtime=run;
        gencount= genre.size();
        actcount= actor.size();
        rcount= roles.size();
    }
    //copy constructor
    movie(const movie &m){
        title=m.title;
        year= m.year;
        genre= m.genre;
        actor = m.actor;
        roles = m.roles;
        runtime=m.runtime;
        gencount= genre.size();
        actcount= actor.size();
        rcount= roles.size();
    }
    std::string name() const{ return title;}
    //getters
    int getyear() const {return year;}
    int getrun() const{return runtime;}
    int getgencount() const{return gencount;}
    int getactorsize() const{return actcount;}
    int getrcount() const{return rcount;}
    std::string ac(int &i){ return actor[i];}
    std::string gc(int &i){return genre[i];}
    std::string rc(int &i){return roles[i];}
    //key specifics
    std::string getkey() const {return key;}
    void setkey(std::string & s){key=s;}

private:

    std::string title;
    int year;
    int runtime;
    int gencount;
    int actcount;
    int rcount;
    std::vector<std::string> genre;
    std::vector<std::string> actor;
    std::string key;
    std::vector<std::string> roles;
};


#endif //HW9_MOVIE_H
