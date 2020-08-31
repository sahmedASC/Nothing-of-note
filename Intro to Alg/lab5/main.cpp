#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;

//returns the vector with the larger size.
std::vector<int> large(vector<int> &x, vector<int> &y){
    if (x.size()>y.size()){
        return x;
    }
    else{
        return y;
    }
}

vector<int> procedure(vector<int> &A){
    //construct a table that is 2D size
    // N by N
    //Each slot of the table has a subsequence vector.
    vector<vector<vector<int>>> Table;
    for(int i = 0; i<A.size();i++){
        vector<int> B;
        B.push_back(A[0]);
        vector<vector<int>> temp;
        for(int j =0 ; j<A.size();j++){
            temp.push_back(B);
        }
        Table.push_back(temp);
    }

    //main code k-1 is the distance from pointersor indexes
    //i and j
    for(int k= 2; k<=A.size();k++){
        for(int i = 0; i<(A.max_size()-k+1);i++){
            int j = i+k-1;
            if(j>=A.size()){
                break;
            }
            //base check
            if (A[i] == A[j] && k == 2) {
                Table[i][j] = {A[i], A[j]};
            }
            //if the indexes are equal to the same value you have a potential
            //palindrome. You've already verified this with the table
            //So you add A[i] and A[j] to the previous palindrome in the table
            //and slot it into the current table index.
            else if(A[i] == A[j]){
                Table[i][j] = Table[i+1][j-1];
                Table[i][j].insert(Table[i][j].begin(),A[i]);
                Table[i][j].push_back(A[i]);
            }
            //if they aren't equal you still have to update the current table index
            //this is set to the large of the two subsequences in the table at the current time
            else{
                Table[i][j]= large(Table[i][j-1], Table[i+1][j]);
            }
        }
    }

    //this holds the subsequence.
    return Table[0][A.size()-1];


}


int main()
{
    //hard coded array
    std::vector<int> A {7, 2, 4, 6, 9, 11, 2, 6, 10, 6, 15, 6, 14, 2, 7, 5, 13, 9, 12, 15};
    vector<int>answer= procedure(A);

    //random array size 100
    std::vector<int> B;
    for(int i =0;i<100;i++){
        B.push_back(rand() %100);
    }
    vector<int> answer2 = procedure(B);
    int size_of_palindrome = answer2.size();

    return 0;
}
