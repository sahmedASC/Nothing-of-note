//
// Created by ahmeds7 on 4/17/2019.
//

#include "UrgentQueue.h"
#include "Job.h"

void UrgentQueue::perc_down(int x) {
    //perc down from index, as shown in lecture
    int y=0;
    while((2*x+1)<uqueue.size()){

        if((2*x+2)<uqueue.size() and (uqueue[2*x+2]->getPriority()) > (uqueue[2*x+1]->getPriority())){
            y=2*x+2;
        }
        else y = 2*x+1;
        if(uqueue[y]->getPriority()>uqueue[x]->getPriority()){
            Job* s1= uqueue[y];
            Job* s2= uqueue[x];
            uqueue[x]=s1;
            uqueue[y]=s2;
            x=y;

        }
        else{

            break;
        }
    }
}

void UrgentQueue::perc_up() {
    //perc up from the bottom to the top
    int x =uqueue.size()-1;
    while (x>0){
        if(uqueue[x]->getPriority()> uqueue[(x-1)/2]->getPriority()){
            Job* s1=uqueue[x];
            Job* s2= uqueue[(x-1)/2];
            uqueue[x]=s2;
            uqueue[(x-1)/2]=s1;
            x=(x-1)/2;
        }
        else break;
    }
}
void UrgentQueue::update() {
    //update the hooks by changing the hook values to their indexes
    for (int i =0; i<uqueue.size();i++){
        uqueue[i]->urgent_hook=i;
    }
}

void UrgentQueue::push(Job* &j){
    //push operation as described in lecture
    j->priority_ptr=this;
    uqueue.push_back(j);
    perc_up();
    update();
}
Job* UrgentQueue::pop() {
    //pop functionas described in lecture
    Job* temp = uqueue[0];
    uqueue[0]= uqueue[uqueue.size()-1];
    uqueue.pop_back();
    perc_down(0);
    update();
    return temp;
}

void UrgentQueue::remove_from_index(int x) {
    //check to see if it's either in the back or if it's the only element
   if(uqueue.size()==1){
       uqueue.pop_back();
       return;
   }
   if(x == uqueue.size()-1){
       uqueue.pop_back();
       return;
   }
   //otherwise essentially run pop function
   //but from the specified index instead.
   uqueue[x]=uqueue[uqueue.size()-1];
   uqueue.pop_back();
   perc_down(x);
   update();

}

void UrgentQueue::printHeap(std::ofstream &out) {
    //simple output
    out<< "UQ "<<uqueue.size()<<" jobs:"<<std::endl;
    for(int i=0; i<uqueue.size();i++){
        out<<"\t"<<uqueue[i];
    }
}