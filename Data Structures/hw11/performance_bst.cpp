#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();


void bst_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR 
  std::map<std::string,int> mp;

  //for almost all operations store the string and count how many times it appears
  if (operation == "sort") {
      //maps are already sorted so just input into output array
      for(int i=0; i<input_count;i++){
          mp[input_data[i]]++;
      }
      output_count=0;
      std::map<std::string,int>::iterator itr = mp.begin();
      for(; itr!=mp.end();++itr){
          for(int i =0; i<itr->second;i++){
            output_data[output_count]=itr->first;
            output_count++;
          }
      }
  } else if (operation == "remove_dups_same_order") {
      //this is the difference instead store the first instance of each word
      //and its index
      int index = 0;
      for(int i=0; i<input_count;i++){
          if(mp.find(input_data[i])==mp.end()){
              mp[input_data[i]]=index;
              index++;
          }
      }
        //if the index matches, input into the output
      output_count=mp.size();
      for(int i =0; i<output_count;i++){
          for(std::map<std::string, int>::iterator itr= mp.begin(); itr !=mp.end();++itr){
              if(itr->second==i){
                  output_data[i]=itr->first;
              }
          }
      }

  } else if (operation == "remove_dups_any_order") {
      //maps already remove dups so just input into output
      for(int i=0; i<input_count;i++){
          mp[input_data[i]]++;
      }
      output_count=mp.size();
      std::map<std::string,int>::iterator itr = mp.begin();
      for (int i =0; i< output_count;i++){
          output_data[i]=itr->first;
          ++itr;
      }
  } else if (operation == "mode") {
      //if you store the amount of times a word appear
      //then this is easy. Generate an iterator to the mode
      //value in the made and output it
      for(int i=0; i<input_count;i++){
          mp[input_data[i]]++;
      }
      int mode_count=0;
      std::map<std::string,int>::iterator itr = mp.begin();
      std::map<std::string,int>::iterator best = mp.begin();
      for(; itr!= mp.end();++itr){
          if(itr->second>mode_count){
              mode_count=itr->second;
              best=itr;
          }
      }
      output_count=1;
      output_data[0]=best->first;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
