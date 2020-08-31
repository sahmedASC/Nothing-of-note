#include <iostream>

#include <vector>
using namespace std;


void search(vector<int> & a, int k, int &c){
    int pivot = rand() % a.size();
    vector<int> small;
    vector<int> equal;
    vector<int> large;

    for(int i=0; i< a.size(); i++){
        if(a[i]==a[pivot]){
            equal.push_back(a[i]);
        }
        else if (a[i]< a[pivot]){
            small.push_back(a[i]);
        }
        else if (a[i]>a[pivot]){
            large.push_back(a[i]);
        }
    }
    if(k ==1){
        c= small[0];
        for(int i =0; i<small.size(); i++){
            if(small[i]<c){
                c = small[i];
            }
        }
        return;
    }
    if(k <= small.size()) {
        k = k - small.size();
        if (k < 0) {
            k += small.size();
            search(small, k, c);
        }
        if (k == 0) {
            c = small[0];
            for (int i = 0; i < small.size(); i++) {
                if (small[i] > c) {
                    c = small[i];
                }
            }
            return;
        }
    }
    else if(k<= small.size()+equal.size()) {
        c = equal[0];
        return;
    }
    else if(k> (small.size()+equal.size())){
        k= k -(small.size()+equal.size());
        search(large, k, c);
    }
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


int partition (vector<int> &a, int low, int high)
{
    int pivot = a[rand()%a.size()];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (a[j] < pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return (i + 1);
}

void quick(vector<int> &a, int lo, int hi){
    if (lo<hi){
        int p = partition(a, lo, hi);

        quick(a,lo,p-1);
        quick(a,p+1,hi);
    }
}



int main() {

    vector<int> ints = {7, 2, 4, 6, 9, 11, 2, 6, 10, 6, 15, 6, 14, 2, 7, 5, 13, 9, 12, 15 };


    //search(ints, k, c);

    int lo = 0;
    int hi = ints.size()-1;
    quick(ints,lo, hi);
    cout<< ints[ints.size()/2]<<endl;

    vector<vector<int>> splits;
    vector<int> push;
    for(int i=0; i<ints.size(); i++){
        if(i %5==0){
            splits.push_back(push);
            push.clear();

        }
        push.push_back(ints[i]);
    }
    splits.push_back(push);

    vector<int> medians;
    for(int i=0; i<splits.size();i++){
        
    }

    return 0;
}
