#ifndef __URGENTQ_H_
#define __URGENTQ_H_
//You can change/add to these #includes
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

typedef unsigned int uq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class UrgentQueue{
public:
    UrgentQueue(){}
    void push(Job*& );
    void perc_up();
    Job* pop();
    void perc_down(int x);
    Job* top()const { return uqueue[0];}
    void remove_from_index(int x);
    void printHeap(std::ofstream &out);
    void update();


//////////FILL THIS IN///////////

private:
    //the priority queue is represented as a vector
    std::vector<Job*> uqueue;
};

#endif
