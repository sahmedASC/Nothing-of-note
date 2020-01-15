#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {

    int s;
    std::map<int, int> counters;
    vector<int> nums;
    std::ifstream in_str(argv[1]);
    if (!in_str.good()) {
        std::cerr << "Can't open " << argv[3] << " to read.\n";
        exit(1);
    }
/*
    while (in_str >> s) {
        ++counters[s];
        nums.push_back(s);
    }
    std::sort(nums.begin(), nums.end());
    std::vector<int>::iterator unique = std::unique(nums.begin(), nums.end());
    nums.resize(std::distance(nums.begin(), unique));

    int max=0;
    for (int i=0;i<nums.size();i++){
        int test =counters[nums[i]];
        if(test>max){
            max=test;
        }
    }
    for(int i=0;i<nums.size();i++){
        int test= counters[nums[i]];
        if(test==max){
            cout<<nums[i]<<endl;
        }
    }
    */
    //CHECKPOINT 2
    //

    while (in_str >> s) {
        std::map<int,int>::iterator itr = counters.find(s);
        if ( itr == counters.end() ) {
            counters.insert(make_pair(s,1));
        } else {
            ++(itr->second);
        }
        nums.push_back(s);
    }
    std::sort(nums.begin(), nums.end());
    std::vector<int>::iterator unique = std::unique(nums.begin(), nums.end());
    nums.resize(std::distance(nums.begin(), unique));
    int max=0;
    for (int i=0;i<nums.size();i++){
        std::map<int,int>::iterator butter = counters.find(nums[i]);
        if(butter->second>max){
            max=butter->second;
        }
    }
    for(int i=0;i<nums.size();i++){
        std::map<int,int>::iterator butter = counters.find(nums[i]);
        if(butter->second==max){
            cout<<nums[i]<<endl;
        }
    }

    return 0;
}