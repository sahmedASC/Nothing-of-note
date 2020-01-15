#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();


void priority_queue_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your priority_queue like this:
  std::priority_queue<std::string,std::vector<std::string> > pq(input_data,input_data+input_count);

  if (operation == "sort") {
      //these are inherently sorted by backwards
      //so input them backwards
      output_count=input_count;
      while(pq.size()!=0){
          output_data[output_count-1]= pq.top();
          pq.pop();
          output_count--;

      }
      output_count= input_count;
  } else if (operation == "remove_dups_same_order") {
      //this is impossible without creating other structures
      //and makes no sense
      exit(1);

  } else if (operation == "remove_dups_any_order") {
      //input into the output array
      //if the value we are about to pop is equal to the
      //current last index value into the array then don't input it
      //and pop it
      output_count=0;
      while(pq.size()!=0){
          if(output_count!=0){
              if(output_data[output_count-1]!= pq.top()){
                  output_data[output_count]=pq.top();
                  pq.pop();
              }
              else{
                  pq.pop();

              }

          } else {
              output_data[output_count] = pq.top();
              pq.pop();
              output_count++;
          }


      }

  } else if (operation == "mode") {
      //since they are inherently sorted you can use that to
      //create temp priority queues that store potential modes
      //if the check pq is larger than the mode pq then you change
      //the mode
      std::priority_queue<std::string,std::vector<std::string> > mode;
      std::priority_queue<std::string,std::vector<std::string> > check;
      while (pq.size()!=0){
          if (check.size()==0){
              check.push(pq.top());
          }
          if(check.top()!=pq.top()){
              if(check.size()>mode.size()){
                  mode=check;
              }
              while(check.size()>0){
                  check.pop();
              }
              continue;
          }
          check.push(pq.top());
          pq.pop();
      }
      output_count=1;
      output_data[0]=mode.top();

  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
