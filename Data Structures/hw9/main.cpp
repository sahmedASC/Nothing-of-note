#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "movie.h"
using namespace std;

std::map<string, string> parse_a(std::ifstream & in_str){
    //generate a map of the actors
    string b, d;
    std::map<string,string> actor_id;
    while (!in_str.eof()){
        in_str>> b>> d;
        actor_id.insert ( std::pair<string,string>(b,d) );
    }
    return actor_id;
}
void parse_m(std::ifstream &in_str,vector<movie> &movies){
    //following the pattern of the format
    //parse in the file and create a movie object at the end
    //and push it into a vector of movie objects
    string b;
    int count=1;
    int loop=0;
    int year;
    int run;
    string title;
    vector<string> genre;
    vector<string> actor;
    vector<string> role;

    while(!in_str.eof()){
        in_str>> b;
        if (count ==1) {
            title = b;
            count++;
            continue;
        }
        if(count == 2){
            year= stoi(b);
            count++;
            continue;
        }
        if(count ==3){
            run = stoi(b);
            count++;
            continue;
        }
        if(count == 4){
            loop = stoi(b);
            for(int i =0; i<loop;i++){
                in_str>> b;
                genre.push_back(b);
            }
            count++;
            continue;
        }
        if(count ==5){
            loop = stoi(b);
            for(int i =0; i<loop; i++){
                in_str>>b;
                actor.push_back(b);
            }
            count++;
            continue;
        }
        if(count ==6){
            loop = stoi(b);
            for (int i=0;i<loop;i++){
                in_str>> b;
                role.push_back(b);
            }
            movie m(title,year,run,genre,actor,role);
            movies.push_back(m);
            genre.clear();
            actor.clear();
            role.clear();
            count = 1;
            continue;
        }

    }
}
vector<string> binary(int x) {
    //the combinations of the movie partials
    //is equal to the binary number of that
    //combination number
    //generate a vector of strings that are the binary
    //numbers for partial key generations later down the line
    vector<string> partials;
    for (int i = 0; i < x; i++) {
        int num[6];
        int p = i;

        int k = 0;
        while (p > 0) {
            num[k] = p % 2;
            p = p / 2;
            k++;
        }
        string s= "";
        for (int j = k - 1; j >= 0; j--) {
            s+=to_string(num[j]);
        }

        while(s.size()<6){
            s="0"+s;
        }
        partials.push_back(s);
    }
    return partials;
}
unsigned int hash_func ( const std::string& key )  {
    //  This implementation comes from
    //  http://www.partow.net/programming/hashfunctions/
    //  Found in Lab 10 .cpp file
    //  This is a general-purpose, very good hash function for strings.
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
        hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
}
string keygen(movie &m, string& partial){
    //use the binary strings
    //if the number is a 1 then add it's
    //representative value, otherwise add in 0 or ?
    string key="";
    if(partial[0]=='1'){
        key+=m.name();
    }
    else key+='?';
    if(partial[1]=='1'){
        key+=to_string(m.getyear());
    }
    else key+='?';
    if(partial[2]=='1'){
        key+=to_string(m.getrun());
    }
    else key+='?';
    if(partial[3]=='1'){
        for(int i=0;i<m.getgencount();i++){
            key+=m.gc(i);
        }
    }
    else key+='0';
    if(partial[4]=='1'){
        for(int i=0; i<m.getactorsize();i++){
            key+=m.ac(i);
        }
    }
    else key+='0';
    if(partial[5]=='1'){
        for(int i=0;i<m.getrcount();i++){
            key+=m.rc(i);
        }
    }
    else key+='0';
    return key;
}

void linear_probe(vector<movie*>& htable, movie* &ptr,int index){
    //linear probe function as described in lecture
    int count =0;
    while(count <htable.size()){
        index = (index+1)%htable.size();
        if(htable[index]==NULL){
            htable[index]=ptr;
            return;
        }
        count++;
    }
}

void resize_table(unsigned int new_size,vector<movie*> &htable) {
    //taken from lab 10. double the size, get the values, rehash and insert
    //linear probe if necessary
    std::vector<movie*> newTable(new_size,NULL);
    for (unsigned int p = 0; p <htable.size(); ++p){
        unsigned int hash_value = hash_func(htable[p]->getkey());
        unsigned int index = hash_value % new_size;
        if(newTable[index]!=NULL){
            linear_probe(newTable,htable[p],index);
        }
        else {
            newTable[index]=htable[p];
        }
    }
    htable.clear();
    htable = newTable;
}

void create_table(vector<movie*>& htable, float occupy, vector<movie>& movies, vector<string>& partials){
    //from the movie objects generate 64 copies of it with all the partial hashes
    //put them all on the heap and assign pointers to them
    //hash the pointers into the hash table
    //resize if necessary
    int unique=0;
    for(int i =0; i<movies.size();i++){
        for(int j=0; j<partials.size();j++){
            if(unique/float(htable.size())>occupy){
                resize_table(htable.size()*2,htable);
            }
            movie* ptr = new movie(movies[i]);
            string key = keygen(movies[i],partials[j]);
            ptr->setkey(key);

            int index = hash_func(key) % htable.size();
            if(htable[index]!=NULL){
                linear_probe(htable,ptr,index);
            }
            else {
                htable[index]=ptr;
            }
            unique+=1;
        }
    }
}

void q_search(vector<movie*> &htable, string& key, vector<movie*> &valid){
    //find the index using hashing. if it matches then pushback
    //linear probe till you find a null to make sure that you find
    //all query matches
    int index = hash_func(key)% htable.size();
    int count = 0;
    while(count<htable.size()){
        if(htable[index]==NULL){
            return;
        }
        if (htable[index] and htable[index]->getkey()==key){
            valid.push_back(htable[index]);

        }
        index= (index+1) %htable.size();
        count++;
    }
}
void print(vector<movie*>& valid, map<string, string> & actors){
    //generic print according to sample ouput
    if(valid.size()==0){
        cout<<"No results for query."<<endl;
        return;
    }
    cout<<"Printing "<<valid.size()<< " result(s):"<<endl;
    for(int i =0;i<valid.size();i++){
        cout<<valid[i]->name()<<endl;
        cout<<valid[i]->getyear()<<endl;
        cout<<valid[i]->getrun()<<endl;
        cout<<valid[i]->getgencount();
        for(int j =0; j<valid[i]->getgencount();j++){
            cout<< " "<<valid[i]->gc(j);
        }
        cout<<endl;
        cout<<valid[i]->getactorsize();
        for(int j=0;j<valid[i]->getactorsize();j++){
            cout<<" " <<actors[valid[i]->ac(j)]<<" (" <<valid[i]->rc(j)<<")";
        }
        cout<<endl;
    }
}

int main() {
    //general values unless stated otherwise by cin
    string command;
    int tsize = 100;
    float occupy = 0.5;
    std::map<string, string> actors;
    vector<movie *> hash_table(tsize, NULL);

    while (command != "quit") {
        std::cin >> command;
        if (command == "table_size") {
            //create the hash table of the different size
            std::cin >> command;
            tsize = stoi(command);
            vector<movie * > new_(tsize,NULL);
            hash_table=new_;
            new_.clear();
            continue;
        }
        if (command == "occupancy") {
            std::cin >> command;
            occupy = stof(command);
            continue;
        }
        if (command == "movies") {
            //parse the movie file
            string file;
            std::cin >> file;
            std::ifstream in_str(file);
            if (!in_str.good()) {
                std::cerr << "Can't open " << file << " to read.\n";
                exit(1);
            }
            std::vector<movie> movies;
            parse_m(in_str, movies);
            vector<string> partials = binary(64);

            create_table(hash_table,occupy,movies,partials);
            continue;

        }
        if (command == "actors") {
            string file;
            std::cin >> file;
            std::ifstream in_str(file);
            if (!in_str.good()) {
                std::cerr << "Can't open " << file << " to read.\n";
                exit(1);
            }

            actors = parse_a(in_str);
            continue;
        }
        if (command == "query") {
            //parse the query key
            //follow closely to the parse_m function about
            int count = 1;
            int loop = 0;
            string querykey = "";
            while (count < 7) {
                std::cin >> command;
                if (count < 4) {
                    querykey += command;
                    count++;
                    continue;
                }
                if (count < 7 ) {
                    loop = stoi(command);
                    if(loop==0){
                        querykey += command;
                    }
                    for (int i = 0; i < loop; i++) {
                        std::cin >> command;
                        querykey += command;
                    }
                    count++;
                    continue;
                }
            }
            //vector to store the matching indexes
            vector<movie*> valid;
            q_search(hash_table,querykey,valid);
            print(valid,actors);
            continue;
        }
    }
    //destructor for the hashtable;
    for(int i=0;i<hash_table.size();i++){
        delete hash_table[i];
    }
    hash_table.clear();
    return 0;
}