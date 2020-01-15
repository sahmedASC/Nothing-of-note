#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();


void list_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your list like this:
  std::list<std::string> lst;

  for(int i =0; i< input_count;i++){
      lst.push_back(input_data[i]);
  }

  if (operation == "sort") {
      //std::list has a sort function so just use that
      //and input to the output
      lst.sort();
      output_count=input_count;
      std::list<std::string>::iterator it= lst.begin();

      for(int i =0;i<output_count;i++){
          output_data[i]=*it;
          ++it;
      }

  } else if (operation == "remove_dups_same_order") {
      //follow the logic for the vector
      //if it finds a dup you don't input it into the array
      output_count=0;
      for(std::list<std::string>::iterator it= lst.begin(); it!=lst.end();++it){
          bool dup = false;
          for(int i =0; i< output_count;i++){
              if(*it == output_data[i]){
                  dup = true;
                  break;
              }
          }
          if(!dup){
              output_data[output_count]=*it;
              output_count++;
          }
      }
  } else if (operation == "remove_dups_any_order") {
      //sort the list using std
      //and then use the built in unique function
      lst.sort();
      lst.unique();
      output_count=lst.size();
      std::list<std::string>::iterator it= lst.begin();
      for(int i=0;i<output_count;i++){
          output_data[i]=*it;
          ++it;
      }

  } else if (operation == "mode") {
      //follow logic for the vector
      //have iterators pointing to potential mode object
      //and at the end input the values into the array
      lst.sort();
      int current_count=1;
      std::string mode;
      int mode_count=0;
      std::list<std::string>::iterator current= lst.begin();
      ++current;
      std::list<std::string>::iterator previous= lst.begin();
      for (; current != lst.end(); ++current, ++previous) {
          if (*current == *previous) {
              // if they are the same increment the count
              current_count++;
          } else if (current_count >= mode_count) {
              // found a new mode!
              mode = *previous;
              mode_count = current_count;
              current_count = 1;
          } else {
              current_count = 1;
          }
      }
      if (current_count >= mode_count) {
          // last entry is a new mode!
          mode = *previous;
          mode_count = current_count;
      }
      // save the mode to the output vector
      output_count = 1;
      output_data[0] = mode;


  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
