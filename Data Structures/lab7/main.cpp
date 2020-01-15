#include <iostream>
#include <math.h>


float dist(int x, int y){
    float d=pow((pow(x,2))+(pow(y,2)),0.5);
    return d;
}
int paths(int x, int y, int &count){
    float d=dist(x,y);

    if(x==0 and y==0)return count+=1;

    if (dist(x - 1, y) < d and x!=0) {
        paths(x - 1, y, count);
    }
    if(dist(x,y-1)<d and y!=0){
        paths(x,y-1,count);
    }
    return count;

}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int count =0;
    int answer = paths(12,12,count);
    std::cout<<answer<<std::endl;

    return 0;
}