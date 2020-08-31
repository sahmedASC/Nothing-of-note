//
// Created by ahmeds7 on 4/1/2020.
//

#include <iostream>
#include <vector>
using namespace std;

bool remove (vector<vector<int>> & ex, int W){
    //assurance check so loop doesn't go on forever
    //if something is removed you have to continue otherwise
    //if nothing is removed then you know you are done.
    if (ex.size()<=1){
        return false;
    }
    vector<vector<int>> same;
    bool check = false;
    for(int i = 0; i<ex.size();i++){
        if (ex[i][0]<=W){
            same.push_back(ex[i]);
        }
        else{
            check = true;
        }
    }
    ex=same;
    return check;
}
vector<vector<int>> greedy(vector<vector<int>>&  Data, int W){
    vector<vector<int>> base;
    vector<vector<int>> sol;

    //get rid of anything over the W constraint
    for(int i =0; i<Data.size();i++){
        if (Data[i][0]<=W){
            base.push_back(Data[i]);
        }
    }

    //Greedy alorithm
    int best= 0;
    while (true){
        //compute the best ratio at the time
        for (int i =0; i<base.size();i++){
            if(i!=best &&( (base[i][1]/float(base[i][0])) >(base[best][1]/float(base[best][0])))){
                best = i;
            }
        }
        //append it to a solution vector
        sol.push_back(base[best]);
        best =0;
        W= W-base[best][0];

        //assurance check
        if(remove(base,W)){
            break;
        }
    }

    return sol;


}
int dynamic(vector<vector<int>> & Data, int W){
    //generate a table
    vector<vector<int>> Table (W+1,vector<int>(Data.size()+1,0));

    //algorithm from 6.4
    for (int i=1; i<Data.size()+1; i++){
        for(int j =1; j<W+1;j++){
            if (Data[i-1][0]>j){
                Table[j][i] = Table[j][i-1];
            }
            else{
                Table[j][i] = max(Table[j][i-1], Table[j-Data[i-1][0]][i-1]+Data[i-1][1]);
            }
        }
    }
    int n = Data.size();

    return Table[W][Data.size()];

}

int main(){

    vector<vector<int>> Data = {{96, 91}, {96, 92}, {96, 92}, {97, 94}, {98, 95}, {100, 94}, {100, 96}, {102, 97}, {103, 97},
                                {104, 99}, {106, 101}, {107, 101}, {106, 102}, {107, 102}, {109, 104}, {109, 106}, {110, 107}, {111, 108},
                                {113, 107}, {114, 110}};

//This vector stores the items from the greedy algorithm
    vector<vector<int>> answer = greedy(Data, 300);

    //this value is the from the dynamic algorithm
    int answer2 = dynamic(Data, 300);
    return 1;
}

