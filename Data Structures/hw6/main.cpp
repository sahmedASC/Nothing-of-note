#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "input.h"
using namespace std;

//normal printing function
template <class T>
void print(vector<T> &input) {
    for (int i = 0; i < input.size(); i++) {
        cout << input[i] << endl;
    }
}
//helper function to sort the dictionary by size
bool help(string s, string ss){
    return s.size()<ss.size();
}
//determine if a word has a constraint as listed in the input
bool check_size(string & test, vector<constraint> constraints){
    for (int i=0;i<constraints.size();i++){
        if (test.size() == constraints[i].len()){
            return true;
        }
    }
    return false;
}
//Break the board up into a substr. Decreases and move the substr until a hit is found
//on a given row. If nothing is found, change the row. Push all found words into a vector
void sub_a(string &base, int height, int width, vector<string> &dict, vector<constraint> &constraints, int &row, int &col,vector<string> &board,
        vector<found_word> &found_words){
    if(row>=height){
        return;
    }
    if(base.size()>=dict[0].size()) {
        for (int i = 0; i < dict.size(); i++) {
            if (base == dict[i]) {
                if (check_size(base, constraints)) {
                    found_word b(base, "a");
                    for (int j = col; j < base.size() + col; j++) {
                        point p(row, j);
                        b.c_pushback(p);
                    }
                    found_words.push_back(b);
                    col += base.size();
                    base = board[row].substr(col, board[row].size() - col);
                    sub_a(base, height, width, dict, constraints, row, col, board,found_words);
                } else {
                    std::cout << "Number of solutions: 0" << std::endl;
                    exit(0);
                }
            }
        }
    }
    //boundary checking
    if (row<height){
        if(base.size()>2){
            base=base.substr(0,base.size()-1);
            sub_a(base, height, width, dict, constraints, row, col, board,found_words);
        }
        if (base.size()<=2 and col !=width){
            col+=1;
            base=board[row].substr(col,board[row].size()-col);
            sub_a(base, height, width, dict, constraints, row, col, board,found_words);
        }
        if(col>= width){
            row+=1;
            if(row>=height){
                return;
            }
            base=board[row];
            col=0;
            sub_a(base, height, width, dict, constraints, row, col, board,found_words);
        }
    }
    if(row>=height and col>=width){
        return;
    }
    return;
}
//same as sub_a but when the boundary is passed generate the next vertical string to recurse with
void sub_d(string &base, int &height, int &width, vector<string> &dict, vector<constraint> &constraints, int &row, int &col,vector<string> &board,
           vector<found_word> &found_words, string &ref){
    if(col>=width){
        return;
    }
    for(int i=0;i<dict.size();i++){
        if(base==dict[i]){
            if(check_size(base,constraints)){
                found_word b(base,"d");
                for(int j=row; j<base.size()+row;j++){
                    point p(j,col);
                    b.c_pushback(p);
                }
                found_words.push_back(b);
                row+= base.size();
                base = ref.substr(row,ref.size()-row);
                sub_d(base,height,width,dict,constraints,row,col,board,found_words,ref);
            }
            else{
                std::cout<<"Number of solutions: 0"<<std::endl;
                exit(0);
            }
        }
    }
    //boundary checking
    if(col<width){
        if(base.size()>2){
            base = base.substr(0,base.size()-1);
            sub_d(base,height,width,dict,constraints,row,col,board,found_words,ref);
        }
        if(base.size()<=2 and row!= height){
            row+=1;
            base=ref.substr(row,ref.size()-row);
            sub_d(base,height,width,dict,constraints,row,col,board,found_words,ref);
        }
        if(row>= height){
            col+=1;
            if(col>=width){
                return;
            }
            ref="";
            for(int i =0;i<height;i++){
                char c = board[i][col];
                string s(1,c);
                ref+=s;
            }
            base=ref;
            row=0;
            sub_d(base, height, width, dict, constraints, row, col, board,found_words,ref);
        }
    }
    if(row>=height and col>=width){
        return;
    }
    return;
}
//Since eveything is sorted I can use this function to assure that a potential solution set of words
//matches the constraint requirements
bool valid(vector<found_word>& solutions, vector<constraint> &constraints){
    bool check = true;
    sort(solutions.begin(),solutions.end());
    for (int i=0;i<constraints.size();i++){
        if(constraints[i].len()!=solutions[i].getw().size()){
            check= false;
            return check;
        }
    }
    return check;
}
//use recursion to do combination math nCr
//to generate indexes that check the words
void possible_indexes(int offset, int k,vector<int> &indexes, vector<int> &k_,vector<vector<int>> &valid_i) {
    if (k == 0) {
        valid_i.push_back(indexes);
        return;
    }
    for (int i = offset; i <= k_.size() - k; ++i) {
        indexes.push_back(k_[i]);
        possible_indexes(i+1, k-1,indexes,k_,valid_i);
        indexes.pop_back();
    }
    return;
}
//assert that there are no duplicate words in a solution set
//the vector is sorted so I can check adjacent elements
bool unique(vector<found_word>& solution){
    bool check= true;
    for(int i=0;i<solution.size()-1;i++){
        if(solution[i].getw()==solution[i+1].getw()){
            return !check;
        }
    }
    return check;
}
//assert that a solution set is completely valid based on constraints
//and uniqueness
void possible_board(vector<vector<int>>& valid_i, vector<constraint>& constraints,vector<found_word> &found_words,
    vector<vector<found_word>> &possible){
    vector<found_word> solution;
    for(int i=0;i<valid_i.size();i++){
        for(int j=0;j<valid_i[i].size();j++){
            solution.push_back(found_words[valid_i[i][j]-1]);
        }
        sort(solution.begin(),solution.end());
        if(valid(solution,constraints)){
            if(unique(solution)) {
                possible.push_back(solution);
            }
        }
        solution.clear();
    }
}
//function that calls the recursive search functions to find the words
vector<found_word> search(int height, int width, vector<string> &board, vector<constraint> & constraints,vector<string> &dict){
    string base = board[0];
    base= base.substr(0,width);
    int row=0; int col=0;
    vector<found_word> found_words;
    sub_a(base,height,width,dict,constraints,row,col,board,found_words);
    base="";
    row=0; col=0;
    for(int i =0;i<height;i++){
        char c = board[i][0];
        string s(1,c);
        base+=s;
    }
    string ref =base;
    sub_d(base,height,width,dict,constraints,row,col,board,found_words,ref);
    return found_words;

}
//from the vector of possible sets of words, build the boards and do one last test
void build_board(vector<vector<string>> &boards,vector<vector<found_word>>& possible_board,int width, int height,
        vector<string>&board,vector<constraint>& constraints,vector<string> &dict){

    for(int i=0;i<possible_board.size();i++) {
        vector<string> test;
        for (int u = 0; u < height; u++) {
            string line(width, '#');
            test.push_back(line);
        }
        for (int j = 0; j < possible_board[i].size(); j++) {
            for (int k = 0; k < possible_board[i][j].coordinates.size(); k++) {
                test[possible_board[i][j].coordinates[k].first()][possible_board[i][j].coordinates[k].second()] = '?';
            }
        }
        for (int b = 0; b < test.size(); b++) {
            for (int v = 0; v < test[b].size(); v++) {
                if (test[b][v] == '?') {
                    test[b][v] = board[b][v];
                }
            }
        }
        //the last test is to make sure that no extra words are created when building a
        //board for solution.
        vector<found_word> baseline = search(height, width, test, constraints, dict);
        sort(baseline.begin(),baseline.end());
        if(baseline==possible_board[i]){
        boards.push_back(test);
        test.clear();
        }
        test.clear();
    }
}
//printing for all_solutions
void final_form(vector<vector<string>>& boards){
    for(int i=0;i<boards.size();i++){
        cout<<"Board:"<<endl;
        print(boards[i]);
    }
}

int main(int argc, char* argv[]) {
    //Get the dict file, remove duplicate words
    std::ifstream in_str(argv[1]);
    if (!in_str.good()) {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    vector<string> dict;
    string word;
    while (!in_str.eof()) {
        in_str >> word;
        dict.push_back(word);
    }
    std::sort(dict.begin(), dict.end(),help);
    std::vector<std::string>::iterator unique = std::unique(dict.begin(), dict.end());
    dict.resize(std::distance(dict.begin(), unique));
    //Get the beginning crossword file
    std::ifstream fboard(argv[2]);
    if (!fboard.good()) {
        std::cerr << "Can't open " << argv[2] << " to read.\n";
        exit(1);
    }
    //parsing
    vector<string> board;
    vector<constraint> constraints;
    vector<found_word> found_words;
    int length;
    string num;
    while (!fboard.eof()) {
        fboard >> word;
        if (word[0]=='!'){
            continue;
        }
        else if (word[0]=='+'){
            if (word.size()==2){
                num = word.substr(1,1);
                length= stoi(num);
            }
            else{
                num = word.substr(1,word.size()-1);
                length= stoi(num);
            }
            constraint c(length);
            constraints.push_back(c);
        }
        else{
            board.push_back(word);
        }
    }
    int height= board.size()-1;
    int width = board[0].size();
    sort(constraints.begin(),constraints.end());

    //meat of the program all functions are explained above
    found_words=search(height,width,board,constraints,dict);
    vector<vector<found_word>> possible;
    vector<int> indexes;
    vector<int> k_;
    vector<vector<int>> valid_i;
    int c_size= constraints.size();
    int f_size= found_words.size();
    int offset =0;
    for(int i=0;i<f_size;i++){
        k_.push_back(i+1);
    }
    possible_indexes(offset,c_size, indexes,k_,valid_i);
    possible_board(valid_i, constraints,found_words,possible);


    vector<vector<string>> boards;
    build_board(boards,possible,width, height,board,constraints,dict);
    //final output.
    if(string(argv[3])=="one_solution"){
        if (string(argv[4])=="count_only"){
            if(boards.size()>=1) {
                cout << "Number of solution(s): 1" <<endl;
                return 0;
            }
            else{
                cout << "Number of solution(s): 0" <<endl;
                return 0;
            }
        }
        else if(string(argv[4])=="print_boards"){
            if(boards.size()>=1){
                cout << "Number of solution(s): 1" <<endl;
                cout<<"Board:"<<endl;
                print(boards[0]);
            }
        }
    }
    else if(string(argv[3])=="all_solutions"){
        if (string(argv[4])=="count_only"){
            if(boards.size()>=1) {
                cout << "Number of solution(s): "<<boards.size() <<endl;
                return 0;
            }
            else{
                cout << "Number of solution(s): 0" <<endl;
                return 0;
            }
        }
        else if(string(argv[4])=="print_boards"){
            if(boards.size()>=1){
                cout << "Number of solution(s): "<<boards.size() <<endl;
                final_form(boards);
            }
        }
    }
    return 0;
}