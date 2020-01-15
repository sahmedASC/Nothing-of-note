//this was written by Saaif Ahmed '22
//The objective of this program is to mimic several image processes
//using vectors and the command line inputs
//First homework of Data Structures wooooo.
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

//this is the replace function. It iterates through the vector and replaces the value
//given in the command line.
std::vector<string> replace(string fore, char* back, vector<string> list){
    for(int i= 0; i<list.size();i++){
        for(int j = 0; j<list[i].size();j++){
            string test(1, list[i][j]);
            if( test == fore){
                char* rep = back;
                list[i][j] = rep[0];
            }
        }
    }
    return list;
}
//for both the dilation and erosion I run through the vector and do the
//"cross check". If anything matches I store that coordinate in another vector of pairs
std::vector<std::pair <int, int>> dilation(string fore, vector<string> list, std::vector<std::pair <int, int>> coor){
    for(int i=0; i<list.size(); i++){
        for (int j= 0; j<list[i].size()-1;j++){
            if(list[i][j] != fore.c_str()[0]){
                //"cross check". Essentially I start out with junk values and if current index in within
                //range of the vector then I change the value to a real value for comparison
                string testup="       ";
                string testdown="     ";
                string testleft="      ";
                string testright="      ";
                if (j!=0) {
                    string testleft(1, list[i][j - 1]);
                    if (testup == fore or testdown == fore or testleft == fore or testright == fore) {
                        std::pair<int, int> place(i, j);
                        coor.push_back(place);
                    }
                }
                if(i!=0) {
                    string testup(1, list[i - 1][j]);
                    if (testup == fore or testdown == fore or testleft == fore or testright == fore) {
                        std::pair<int, int> place(i, j);
                        coor.push_back(place);
                    }
                }
                if(j!=list[i].size()-1) {
                    string testright(1, list[i][j + 1]);
                    if (testup == fore or testdown == fore or testleft == fore or testright == fore) {
                        std::pair<int, int> place(i, j);
                        coor.push_back(place);
                    }
                }
                if(i!=list.size()-1) {
                    string testdown(1, list[i + 1][j]);
                    if (testup == fore or testdown == fore or testleft == fore or testright == fore) {
                        std::pair<int, int> place(i, j);
                        coor.push_back(place);
                    }
                }

                if (testup== fore or testdown==fore or testleft== fore or testright == fore){
                    std::pair <int,int> place (i,j);
                    coor.push_back(place);
                }
            }
        }
    }
    return coor;
}
//same as the dilation process
std::vector<std::pair <int,int>> erosion(string fore, char empty, vector<string> list, std::vector<std::pair <int,int>> coor){
    for(int i=0; i<list.size()-1; i++){
        for (int j=0; j<list[i].size()-1;j++){
            if(list[i][j] == fore.c_str()[0]){
                //exactly the same as the dilation cross check.
                string testup="junk";
                string testdown="junk";
                string testleft="junk";
                string testright="junk";
                string check(1, empty);

                if (i!=0){
                    string testup(1, list[i - 1][j]);
                    if (testup == check or testdown==check or testleft== check or testright == check){
                        std::pair <int,int> place (i,j);
                        coor.push_back(place);
                    }
                }
                if(i!=list.size()-1){
                    string testdown(1, list[i + 1][j]);
                    if (testup== check or testdown == check or testleft== check or testright == check){
                        std::pair <int,int> place (i,j);
                        coor.push_back(place);
                    }
                }
                if(j!=0){
                    string testleft(1, list[i][j - 1]);
                    if (testup== check or testdown==check or testleft== check or testright == check){
                        std::pair <int,int> place (i,j);
                        coor.push_back(place);
                    }
                }
                if(j!=list[i].size()-1){
                    string testright(1, list[i][j + 1]);
                    if (testup== check or testdown==check or testleft== check or testright == check){
                        std::pair <int,int> place (i,j);
                        coor.push_back(place);
                    }
                }

                if (testup== check or testdown==check or testleft== check or testright == check){
                    std::pair <int,int> place (i,j);
                    coor.push_back(place);
                }
            }
        }
    }
    return coor;
}

int main(int argc, char* argv[]) {
    //bad file check
    std::ifstream in_str(argv[1]);
    if (!in_str.good()) {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    //variable declaration and assignment
    std::vector<std::string> list;
    string fore= argv[4]; //specifically the foreground character for replace and dilation

    std::vector<std::pair <int, int>> coor;

    //create a vector of the strings/lines of the file for computation
    std::string line;
    while (!in_str.eof()) {
        in_str >> line;
        list.push_back(line);
    }

    //if it's replace run this block that'll replace
    if (string(argv[3])==string("replace")) {
        char* back = argv[5];
        list = replace(fore, back, list);
    }

    //if it's dilation run this block that replaces the calculated values
    else if (string(argv[3])==string("dilation")){
        std::vector <std::pair <int,int>> places = dilation(fore, list, coor);

        for (int i = 0; i< places.size(); i++){
            list[places[i].first][places[i].second] = fore[0];
        }
    }
    //erosion segment
    else if (string(argv[3])==string("erosion")){
        char empty = argv[5][0];
        std::vector <std::pair <int,int>> places = erosion(fore, empty, list, coor);

        for (int i = 0; i< places.size(); i++){
            list[places[i].first][places[i].second] = empty;

        }
    }
    //for opening I run the vector through the functions twice and each time create a
    //new vector of coordinate pairs to be changed
    else if (string(argv[3])==string("opening")){
        char* empty = argv[5];
        std::vector <std::pair <int,int>> places = erosion(fore, empty[0], list, coor);
        for (int i = 0; i< places.size(); i++){
            list[places[i].first][places[i].second] = empty[0];
        }
        std::cout<<std::endl;
        std::vector <std::pair<int,int>> places2 = dilation(fore,list,coor);
        for (int i = 0; i< places2.size(); i++){
            list[places2[i].first][places2[i].second] = fore[0];

        }
    }
    //same process as opening but in reverse for closing
    else if (string(argv[3])==string("closing")){
        char* empty = argv[5];
        std::vector <std::pair<int,int>> places2 = dilation(fore,list,coor);
        for (int i = 0; i< places2.size(); i++){
            list[places2[i].first][places2[i].second] = fore[0];

        }
        std::cout<<std::endl;
        std::vector <std::pair <int,int>> places = erosion(fore, empty[0], list, coor);
        for (int i = 0; i< places.size(); i++){
            list[places[i].first][places[i].second] = empty[0];

        }
    }
    //output file name
    std::ofstream out_str;
    out_str.open(argv[2]);
    //file check
    if (!out_str.good()) {
        std::cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }
    //write sequence
    for(int i=0; i<list.size()-1;i++){
        out_str << list[i]<<std::endl;
    }
    out_str.close();
    return 0;
}