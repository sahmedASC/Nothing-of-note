//
// Created by ahmeds7 on 2/13/2019.
//

#include <iostream>
#include <string>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
    std::cout << label << " ";
    for (typename std::list<T>::iterator i = data.begin(); i != data.end(); i++) {
        std::cout << " " << *i ;
    }
    std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {

    // FILL IN THIS FUNCTION
    if (data.size()==1 or data.size()==0){return;}

    typename std::list<T>::iterator i=data.begin();
    for (int j=0; j<data.size()-1;j++){
        T temp = data.back();
        data.pop_back();
        data.insert(i,temp);
    }
}


int main() {
    std::cout<<"Czech 2"<<std::endl;
    std::list<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(7);

    print(data,"before:");
    reverse(data);
    print(data,"after: ");

    std::list<std::string> data2;
    data2.push_back("apple");
    data2.push_back("banana");
    data2.push_back("carrot");
    data2.push_back("date");

    print(data2,"before:");
    reverse(data2);
    print(data2,"after: ");
}