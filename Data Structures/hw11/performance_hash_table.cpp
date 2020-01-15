#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();


void hash_table_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your hash table like this:
  // std::unordered_set<std::string> ht(input_count);
  // OR 
  std::unordered_map<std::string,int> ht(input_count);

  /*for(int i=0 ;i<input_count;i++){
      ht[input_data[i]]++;
  }*/

    //it does not make sense to sort a hash table since
    //they rely on random insertion
  if (operation == "sort") {
        exit(1);

  } else if (operation == "remove_dups_same_order") {
      //same logic as in std::map (bst)
      //store the index instead of the count
      int index = 0;
      for(int i=0; i<input_count;i++){
          if(ht.find(input_data[i])==ht.end()){
              ht[input_data[i]]=index;
              index++;
          }
      }
      output_count=ht.size();
      for(int i =0;i<output_count;i++) {
          for (std::unordered_map<std::string, int>::iterator itr = ht.begin(); itr != ht.end(); ++itr) {
              if(i == itr->second){
                  output_data[i]=itr->first;
              }
          }
      }
  } else if (operation == "remove_dups_any_order") {
      //has tables get rid of dups already so just input to the output
      //array
      for(int i=0 ;i<input_count;i++){
          ht[input_data[i]]++;
      }
      output_count=ht.size();
      std::unordered_map<std::string,int>::iterator itr = ht.begin();
      for (int i =0; i< output_count;i++){
          output_data[i]=itr->first;
          ++itr;
      }
  } else if (operation == "mode") {
      //store the amount of times a word appears
      //and store an iterator to the mode object in the
      //hash table.
      for(int i=0 ;i<input_count;i++){
          ht[input_data[i]]++;
      }
      int mode_count=0;
      std::unordered_map<std::string,int>::iterator itr = ht.begin();
      std::unordered_map<std::string,int>::iterator best = ht.begin();
      for(; itr!= ht.end();++itr){
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
