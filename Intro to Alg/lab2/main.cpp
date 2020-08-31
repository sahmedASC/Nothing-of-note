#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>

using namespace std;


vector<vector<int>> generate(int width, float p){

    p = p*100;

    vector<vector<int>> adj_matrix;

    for(int i = 0 ; i<width; i++){
        vector<int> row;
        for(int j = 0 ; j<width; j++){
            row.push_back(0);
        }
        adj_matrix.push_back(row);

    }
    for (int i = 0; i<(width/2); i++){

        for(int j = i; j<width ; j++){
            if (j == i){ continue;}
            float check = abs(rand()*100 %100);

            if(check <= p){
                adj_matrix[i][j] = 1;
                adj_matrix[j][i] = 1;

            }
            else{
                continue;
            }
        }

    }

    if (width %2 != 0){
        for(int i =0; i<width ; i++){
            if(i == (width/2)){
                continue;
            }
            float check = abs(rand()*100 %100);
            if(check <= p){
                adj_matrix[(width/2)][i] = 1;
                adj_matrix[i][(width/2)] = 1;

            }
        }
    }

    return adj_matrix;
}

void out(vector<vector<int>>& ah){
    cout<< "   ";
    for(int i = 0; i< ah.size(); i++){

        cout<<i<< " ";
    }
    cout<<endl;
    for(int i = 0; i<ah.size(); i++){
        cout<<i<<": ";
        for(int j = 0; j<ah[i].size(); j++){
            cout<<ah[i][j]<< " ";
        }
        cout<<endl;
    }
}

bool bfs(vector<vector<int>>& adj_matrix, int t){
    vector<bool> visited (adj_matrix.size(), false);
    list<int> stack;

    vector<int> path;
    vector<int> max;
    for(int i =0; i<adj_matrix.size();i++) {
        if(visited[i]){
            continue;
        }
        stack.push_front(i);
        visited[i] = true;
        path.push_back(i);

        while (stack.size() != 0) {
            int node = stack.front();
            stack.pop_front();
            for (int j = 0; j < adj_matrix[node].size(); j++) {
                if (adj_matrix[node][j] == 1) {
                    if(visited[j]){
                        continue;
                    }
                    else{
                        stack.push_back(j);
                        visited[j] = true;
                        path.push_back(j);
                    }
                }
            }

        }
        if (path.size()>max.size()){
            max = path;
        }
        path.clear();

    }
    return max.size() >= t;

}


int main() {

    int* k = new int;
    *k= 40;


    int width =40;
    float p;
    int threshold = 30;
    //cout<<"width: ";
    //cin>> width;
    //cout<<"p: ";
    //cin >>p;
    cout<<"probability  met_threshold"<<endl;
    for(int i = 0; i<15 ;i++){
        int count = 0;
        for(int j = 0; j<500; j++){
            p = 0.2+(i*0.2);
            p = float(p)/40;
            vector<vector<int>> adj_matrix = generate(width,p);
            if(bfs(adj_matrix, threshold)){
                count++;
            }

        }
        cout<<"   "<<p*40<< "        "<<float(count)/500<<endl;
    }


    //out(adj_matrix);

    //cout<< "threshold: ";
    //cin >>threshold;

    return 0;
}
