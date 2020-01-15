//
// Created by ahmeds7 on 4/17/2019.
//

#include "TimeQueue.h"
#include "Job.h"

void TimeQueue::perc_down(int x) {
    //perc down from index as shown in lecture
    //check the time values instead
    int y=0;
    while((2*x+1)<tqueue.size()){

        if((2*x+2)<tqueue.size() and (tqueue[2*x+2]->getTime()) < (tqueue[2*x+1]->getPriority())){
            y=2*x+2;
        }
        else y = 2*x+1;
        if(tqueue[y]->getTime()<tqueue[x]->getTime()){
            Job* s1= tqueue[y];
            Job* s2= tqueue[x];
            tqueue[x]=s1;
            tqueue[y]=s2;
            x=y;

        }
        else{
            break;
        }
    }
}
void TimeQueue::perc_up() {
    //perc up function altered to work with vector
    //same process as shown in lecture
    int x = tqueue.size()-1;
    while (x>0){
        if(tqueue[x]->getTime()< tqueue[(x-1)/2]->getTime()){
            Job* s1=tqueue[x];
            Job* s2= tqueue[(x-1)/2];
            tqueue[x]=s2;
            tqueue[(x-1)/2]=s1;
            x=(x-1)/2;
        }
        else break;
    }
}
void TimeQueue::update() {
    //update the hooks based on their indexes
    for(int i =0;i<tqueue.size();i++){
        tqueue[i]->time_hook=i;
    }
}
void TimeQueue::push(Job *j) {
    //push function as described in lecture
    j->time_ptr=this;
    tqueue.push_back(j);
    perc_up();
    update();
}
Job* TimeQueue::pop() {
    //pop function as described in lecture, just returns something this time
    Job* temp = tqueue[0];
    tqueue[0]= tqueue[tqueue.size()-1];
    tqueue.pop_back();
    perc_down(0);
    update();
    return temp;
}
void TimeQueue::remove_from_index(int x) {
    if(tqueue.size()==1){
        tqueue.pop_back();
        return;
    }
    if(x == tqueue.size()-1){
        tqueue.pop_back();
        return;
    }
    tqueue[x]=tqueue[tqueue.size()-1];
    tqueue.pop_back();
    perc_down(x);
    update();
}
void TimeQueue::printHeap(std::ofstream &out) {
    //output
    out<< "TQ "<<tqueue.size()<<" jobs:"<<std::endl;
    for(int i=0; i<tqueue.size();i++){
        out<<"\t"<<tqueue[i];
    }
}
