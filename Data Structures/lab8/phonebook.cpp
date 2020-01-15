// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
/*
void add( map<int, string>& phonebook, int number, string const& name) {
    phonebook[number]=name;
}

// given a phone number, determine who is calling
void identify( map<int,string> & phonebook, int number) {
  if (phonebook[number].size()>0)
    cout << phonebook[number]<< " is calling" << endl;
  else
    cout << "WHO??!?!??!" << endl;
}*/

void add(vector<string> &phonebook, int number, string const& name) {
    phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
    if (phonebook[number] == "UNASSIGNED")
        cout << "unknown caller!" << endl;
    else
        cout << phonebook[number] << " is calling!" << endl;
}

int main() {
  // create the phonebook; initially all numbers are unassigned
  vector<string> phonebook(1000000000, "UNASSIGNED");

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);

//analysis:
/*
 * Construction O(N)
 * add O(1)
 * identify O(1)
 * memory O(N)
 *
 *nothing would change if the size was extended. N would be larger but the operations would still be constant time
 */

/*
  map<int, string> phonebook;
  add(phonebook, 1234567, "fred");
  add(phonebook, 2345678, "sally");
  add(phonebook, 3456789, "george");

  // test the phonebook
  identify(phonebook, 1234567);
  identify(phonebook, 7654321);*/
  return 0;
}
