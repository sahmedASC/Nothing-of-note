//
// Created by ahmeds7 on 2/6/2019.
//

#ifndef HW3_TABLE_H
#define HW3_TABLE_H

#include <iostream>

#endif //HW3_TABLE_H

#include <vector>

template <class T> class Table{
public:
    //get functions
    T get(unsigned int n, unsigned int m);
    unsigned int numRows() const{return rows;}
    unsigned int numColumns() const{ return cols;}
    //constructors
    Table() { this->create(); }
    Table(const Table &t){copy(t);}
    Table(unsigned int n, unsigned int m,const T& t = T()) { this->create(n, m,t); }
    //member functions
    void print();
    void push_back_row(const std::vector<T> &x);
    void push_back_column(const std::vector<T> &x);
    void pop_back_column();
    void pop_back_row();
    void set(unsigned int n, unsigned int m, const T &val);
    //destructor
    ~Table();
    //misc.
    Table& operator=(const Table<T>& t);
private:
    //Constructors
    void copy(const Table<T> &a);
    void create();
    void create(unsigned int n, unsigned int m, const T &val);
    //variables
    T** values;
    unsigned int rows;
    unsigned int cols;
};
//default constructor
template <class T> void Table<T>::create(){
    values= NULL;
    rows=0;
    cols=0;
}
//real constructor
template <class T> void Table<T>::create(unsigned int n, unsigned int m, const T &val){
    values = new T*[n];
    rows =n ;
    cols=m;
    for (int i=0; i<rows;i++){
        values[i]= new T[m];
        for (int j=0;j<cols;j++){
            values[i][j]= val;
        }
    }
}
//set member values equal to eachother
template <class T> void Table<T>::copy(const Table<T> &t) {
    this-> rows = t.rows;
    this-> cols = t.cols;
    this-> values= new T*[this->rows];

    // Copy the data
    for (unsigned int i = 0; i < this->rows; i++) {
        values[i] = new T[cols];
        for (unsigned int j = 0; j< cols; j++) {
            this->values[i][j] = t.values[i][j];
        }
    }
}
//copy the values into another and prevent duplicate copying
template <class T> Table<T>& Table<T>::operator=(const Table<T>& t) {
    if (this != &t) {
        for(unsigned int i=0; i<rows;i++){
            delete [] values[i];
        }
        delete [] values;
        this -> copy(t);
    }
    return *this;
}
//return the value in the table and break if invalid value is given
template <class T> T Table<T>::get(unsigned int n, unsigned int m){
    if(n>rows or m>cols or n<0 or m<0){
        std::cerr<<"Table Index out of range. Seg Fault. (get)"<<std::endl;
        exit(1);
    }return values[n][m];}
//same as the get function
template <class T> void Table<T>::set( unsigned int n, unsigned int m, const T &val){
    if(n>rows or m>cols or n<0 or m<0){
        std::cerr<<"Table Index out of range. Seg Fault. (set)"<<std::endl;
        exit(1);
    }
    values[n][m]= val;
}
//run through the table iteratively and cout all the elements
template <class T> void Table<T>::print(){
    std::cout<< "table: "<< rows<< " rows, "<< cols<< " cols"<<std::endl;
    for (int i= 0; i< rows;i++){
        for (int j= 0; j<cols;j++){
            std::cout<< values[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
//allocate a larger array of pointers. copy the values. deleter the
//original. assign the temp values to the original
//break if the vector is an invalid size
template <class T> void Table<T>::push_back_row(const std::vector<T> &x) {
    T** new_stuff= new T*[rows+1];
    unsigned int r= rows;

    for (unsigned int i=0; i<rows;i++) {
        new_stuff[i] = new T[cols];
        for(int j=0; j<cols;j++) {
            new_stuff[i][j] = values[i][j];
        }
        delete [] values[i];
    }
    delete []values;
    // Delete the old array and reset the pointers
    new_stuff[r]=new T[cols];
    if(x.size() != cols){
        std::cerr<<"Invalid vector size. Too long or small (push_back_row)"<<std::endl;
        exit(1);
    }
    for (int i =0;i<x.size();i++){
        new_stuff[r][i]=x[i];
    }
    rows=r+1;
    values = new_stuff;
}
//same as push back row only allocating larger column arrays
//break if vector is invalid
template <class T> void Table<T>::push_back_column(const std::vector<T> &x){
    T** new_stuff = new T*[rows];
    for (unsigned int i=0; i<rows;i++){
        new_stuff[i] = new T[cols+1];
        for(int j=0; j<cols;j++) {
            new_stuff[i][j] = values[i][j];
        }
        delete [] values[i];
    }
    delete [] values;
    if(x.size() != rows){
        std::cerr<<"Invalid vector size. Too long or small. (push_back_row)"<<std::endl;
        exit(1);
    }
    for (int i =0;i<rows;i++){
        new_stuff[i][cols]=x[i];
    }
    cols+=1;
    values = new_stuff;
}
//allocate a smaller array by colums
//copy everything by the last values and delete original
template <class T> void Table<T>::pop_back_column(){
    if(cols==0){
        std::cerr<<"Invalid amount of columns (pop_back_column)"<<std::endl;
        exit(1);
    }
    T** new_stuff = new T*[rows];
    for (unsigned int i=0; i<rows;i++){
        new_stuff[i] = new T[cols-1];
        for(int j=0; j<cols-1;j++) {
            new_stuff[i][j] = values[i][j];
        }
        delete [] values[i];
    }
    delete [] values;

    cols-=1;
    values = new_stuff;
}
//allocate a smaller array by rows.
//copy everything except the last row and delete the original and re-assign
template <class T> void Table<T>::pop_back_row(){
    if(rows==0){
        std::cerr<<"Invalid amount of rows (pop_back_row)"<<std::endl;
        exit(1);
    }
    T** new_stuff = new T*[rows-1];
    for (unsigned int i=0; i<rows-1;i++){
        new_stuff[i] = new T[cols];
        for(int j=0; j<cols;j++) {
            new_stuff[i][j] = values[i][j];
        }
        delete [] values[i];
    }
    delete [] values[rows-1];
    delete [] values;

    rows=rows-1;
    values = new_stuff;
}
//destructor. delete everything and leave no trace.
template <class T> Table<T>::~Table(){
    for(int i=0; i<rows;i++){
        delete [] values[i];
    }
    delete [] values;
}
