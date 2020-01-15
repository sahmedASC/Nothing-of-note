//
// Created by ahmeds7 on 3/9/2019.
//

#ifndef HW6_POINT_H
#define HW6_POINT_H

#include <string>
#include <vector>
//point class to edit the vectors later
class point{
public:
    point() : first_(-1), second_(-1) {}
    point(int f,int s) :  first_(f), second_(s) {}
    int first () const { return first_;}
    int second()const {return second_;}
    bool operator==(const point &p)const{ return (first_==p.first_ and second_==p.second_);}


private:
    int first_;
    int second_;
};
//constraint class to determine valid boards
class constraint{
public:
    constraint(): len_(0){} //found_(false){}
    constraint(int l) : len_(l){}
    int len() const {return len_;}
    bool operator<(const constraint & c){ return len_<c.len_;}

private:
    int len_;
};
//"word" class
//has a direction, some get functions and vector of points
//associated with it for filtering possible solutions
class found_word{
public:
    found_word(): word("") {}
    found_word(std::string s, std::string d) : word(s), dir(d){}
    void c_pushback(point p){coordinates.push_back(p);}
    std::string getw()const{return word;}
    bool operator<(const found_word & c){
        if(word.size()<c.word.size())
            return true;
        else if(word.size()==c.word.size()){
            return word<c.word;
        } else return false;
    }
    bool operator==(const found_word & c) const{ return (word==c.word and dir==c.dir and coordinates==c.coordinates);}
    std::vector<point> coordinates;

private:
    std::string word;
    std::string dir;
};

#endif //HW6_POINT_H
