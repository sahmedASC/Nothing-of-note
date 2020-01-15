#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>
#include "iostream"

typedef unsigned int tq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class TimeQueue{
public:
    void perc_up();
    void push(Job* j);
    void perc_down(int x);
    Job* pop();
    Job* top() const {return tqueue[0];}
    void remove_from_index(int x);
    void printHeap(std::ofstream &out);
    void update();



private:
    //the queue is represented as a vector
    //because it is the prefered data type
    std::vector<Job*> tqueue;

//////////FILL THIS IN///////////

};

#endif
