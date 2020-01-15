//
// Created by ahmeds7 on 1/16/2019.
//
#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function
#include <vector>
#include <string>
#include <stdlib.h>

int main(){
    std::vector<float> numbers;
    std::vector<float> smaller;

    std::cout<< "Give me some numbers"<< std::endl;
    int indicator;
    std::cin>> indicator;
    for (int i= 0; i<indicator;i++){
        float number;
        std::cin >> number;
        numbers.push_back(number);
    }

    float total=0;
    for (int i=0; i<numbers.size();i++){
        total= total+numbers[i];

    }
    float average=float(total/numbers.size());

    for (int i=0; i<numbers.size();i++){
        if(numbers[i]<average){
            smaller.push_back(numbers[i]);
        }

    }
    std::cout<< "Average: "<<average<<std::endl;
    std::cout<< "Smaller: "<<std::endl;
    for (int i =0; i<smaller.size();i++){
        std::cout<<smaller[i]<<" ";
    }
    return 0;
}