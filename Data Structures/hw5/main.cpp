//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN 
//       CHANGES TO MoreTests()
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>

#include "unrolled.h"

// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T>& a, std::list<T> &b) { 
  if (a.size() != b.size()) return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter) return false;
    a_iter++;
    b_iter++;
  }
  assert (a_iter == a.end() && b_iter == b.end()); 
  return true;
}


// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}


// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }  

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr
    ;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 20);
  assert (a.front() == 10);
  assert (a.back() == 29);
  a.pop_front();
  b.pop_front();
  assert (a.size() == 19);
  assert (a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert (a.size() == 18);
  assert (a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert (a.size() == 12);
  assert (a.front() == 16);
  assert (a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 16);
  assert (a.front() == 93);
  assert (SAME(a,b));

  // erase the multiples of 3
  std::cout <<"erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 10);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr,77);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr,77);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 14);
  assert (SAME(a,b));

  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr,88);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr,88);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 15);
  assert (SAME(a,b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 9);
  assert (SAME(a,b));

}


// ===================================================================
void MoreTests() {

  //
  //
  // ADD YOUR OWN TEST CASES HERE
  // ADD COMMENTS TO EXPLAIN THE PURPOSE OF THE TEST CASES
  // TEST CASES SHOULD FINISH AND NOT CRASH. OUTPUT IS HELPFUL AS WELL.
  //
  //
  std::cout<<"Time for some more tests"<<std::endl;
  UnrolledLL<int> new_boy;
  UnrolledLL<int> a;
  for (int i = 10; i < 30; ++i) {
      a.push_back(i);
  }
  //Testing the assignment operator and copy constructor
  new_boy=a;
  a.print(std::cout);
  new_boy.print(std::cout);
  if (a.size() != new_boy.size()){std::cout<<"Nah"<<std::endl; exit(1);}
  typename UnrolledLL<int>::iterator new_iter = new_boy.begin();
  typename UnrolledLL<int>::iterator a_iter = a.begin();
  while (new_iter != new_boy.end() && a_iter != a.end()) {
      if (*new_iter != *a_iter) {std::cout<<"Nah"<<std::endl; exit(1);}
      a_iter++;
      new_iter++;
  }
  assert (a_iter == a.end() && new_iter == new_boy.end());

  //Push front an Unrolled List into existence
  UnrolledLL<int> front;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    front.push_front(i);
    b.push_front(i);
  }

  std::cout<<std::endl;

  // iterate through the integers and print them out
  std::cout << "the integers from 29->10" << std::endl;
  for (UnrolledLL<int>::iterator itr = front.begin(); itr != front.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(front,b));

  //using erase to effectively delete a list
  std::cout<<"Using erase() to delete a list"<<std::endl;
  for (UnrolledLL<int>::iterator itr = front.begin(); itr != front.end();) {
    itr=front.erase(itr);
  }
  front.print(std::cout);
  assert(front.size()==0);
  std::cout<<std::endl;

  //testing the operator-- functionality.
  front=new_boy;
  std::cout<<"The contents of new_boy:"<<std::endl;
  for(UnrolledLL<int>::iterator i=new_boy.begin();i!=new_boy.end();++i ){
    std::cout << " " << *i;
  }
  std::cout<<std::endl;
  std::cout<<"The contents of new_boy reversed (front):"<<std::endl;
  for(UnrolledLL<int>::iterator i=front.rbegin();i!=front.rend();--i ){
    std::cout << " " << *i;
  }
  std::cout<<std::endl;
  std::cout<<std::endl;

  //pop backing and pop fronting two UnrolledLL into non-existence

  std::cout<<"Using popback/front to obliterate Unrolled lists"<<std::endl;
  assert(front.size()==new_boy.size());
  int size= front.size();
  for(int i =0;i<size;i++){
    new_boy.pop_back();
    front.pop_front();
  }
  assert(front.size()==0 and front.size()==new_boy.size());
  front.print(std::cout);
  new_boy.print(std::cout);

}
