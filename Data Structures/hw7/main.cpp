#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <list>
#include <vector>
#define earthRadiusKm 6371.0
#ifndef M_PI
#define M_PI 3.14
#endif

//TODO: You must fill in all ?????? with the correct types.
typedef unsigned int ID_TYPE; //Type for user IDs
typedef std::pair<double,double> COORD_TYPE; //Type for a coordinate (latitude and longitude)
typedef std::map<ID_TYPE ,std::vector<ID_TYPE >> ADJ_TYPE; //Adjacency Lists type
typedef std::map<ID_TYPE ,COORD_TYPE> GEO_TYPE; //Positional "dictionary"

//Function forward declarations. DO NOT CHANGE these. 
double deg2rad(double deg);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile);
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile);
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance);
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree);
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, 
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance);
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, 
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset);


// DO NOT CHANGE THIS FUNCTION
int main(int argc, char** argv){
    ADJ_TYPE adj_lists;
    GEO_TYPE locations;

    if(argc != 3){
        std::cout << "Correct usage is " << argv[0] 
                  << " [commands file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream commands(argv[1]);
    if(!commands){
        std::cerr << "Problem opening " << argv[1] << " for reading!" 
                  << std::endl;
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Problem opening " << argv[2] << " for writing!" 
                  << std::endl;
        return -1;
    }

    std::string token; //Read the next command
    while(commands >> token){
        if(token == "load-connections"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading connections." << std::endl;
                return -1;
            }

            loadConnections(adj_lists, loadfile);
        }
        else if(token == "load-locations"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading locations." << std::endl;
                return -1;
            }

            loadLocations(locations, loadfile);
        }
        else if(token == "print-degrees"){
            printDegreesOfAll(adj_lists, outfile);
        }
        else if(token == "print-degree-histogram"){
            printDegreesHistogram(adj_lists, outfile);
        }
        else if(token == "all-users-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printAllUsersWithinDistance(locations, outfile, start_id, 
                                        max_distance);
        }
        else if(token == "friends-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printFriendsWithinDistance(adj_lists, locations, outfile, 
                                       start_id, max_distance);
        }
        else if(token == "friends-with-degree"){
            ID_TYPE start_id,degree;
            commands >> start_id >> degree;

            printFriendsWithDegree(adj_lists, outfile, start_id, degree);
        }
        else if(token == "nodes-within-ID-range"){
            ID_TYPE start_id,offset;
            commands >> start_id >> offset;

            printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(),
                                    adj_lists.find(start_id), offset);
        }
        else{
            std::cerr << "Unknown token \"" << token << "\"" << std::endl;
            return -1;
        }
    }

    return 0;
}




// This function converts decimal degrees to radians
// From https://stackoverflow.com/a/10205532
// DO NOT CHANGE THIS FUNCTION
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * Taken from https://stackoverflow.com/a/10205532
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 * DO NOT CHANGE THIS FUNCTION
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//////////////////TODO: IMPLEMENT ALL FUNCTIONS BELOW THIS POINT////////////////////

/**
 * Loads a list of connections in the format "a b" meaning b is a friend of a
 * into the adjacency lists data structure. a and b are IDs.
 * @param adj_lists Adjacency lists structure
 * @param loadfile File to read from
 */
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile){
    std::string word;

    ID_TYPE id;
    ID_TYPE value;
    while (!loadfile.eof()) {
        loadfile >> id>> value;
        adj_lists[id].push_back(value);
    }
    adj_lists[id].pop_back(); //due to weird format of file, I do this to make sure parsing is correct
}

/**
 * Loads a list of locations in the format "id latitude longitude"
 * @param locations Location lookup table
 * @param loadfile File to read from
 */
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile){
    ID_TYPE key;
    double lat;
    double lon;
    while (!loadfile.eof()) {
        loadfile >> key >> lat >> lon;
        locations.insert(std::make_pair(key,std::make_pair(lat,lon)));
    }
}

/**
 * Prints all users within a certain distance of a particular user.
 * Sorted from shortest distance to user to longest distance to user.
 * Rounds down to the next lowest km if the difference is a decimal
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
 //Assert that the start_id exists and then use the built in function to get values store them in a map
 //and print them out based on the size and other specifications
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance){
    bool check = false;
    for(GEO_TYPE::const_iterator it = locations.begin();it!=locations.end();++it){
        if(it->first==start_id) {
            check = true;
            break;
        }
    }
    if(check) {
        GEO_TYPE::const_iterator base=locations.find(start_id);
        std::map<double, std::vector<ID_TYPE> > valid;
        for (GEO_TYPE::const_iterator it = locations.begin(); it != locations.end(); ++it) {
            if (it != base) {
                double test = distanceEarth(it->second.first, it->second.second, base->second.first,
                                           base->second.second);
                if (test <= max_distance) {
                    valid[int(test)].push_back(it->first);
                }
            }
        }
        if (valid.size() == 0) {
            outfile << "There are no users within " << max_distance << " km of user " << start_id << std::endl;
            return;
        } else {
            outfile << "User IDs within " << max_distance << " km of user " << start_id << ":" << std::endl;
            for (std::map<double ,std::vector<ID_TYPE >>::iterator it = valid.begin();it!=valid.end();++it) {
                outfile << " " << int(it->first) << " km:";
                for(int i=0;i<it->second.size();i++) {
                    outfile << " "<<it->second[i];
                }
                outfile<<std::endl;
            }
        }
        return;
    }
    outfile<<"User ID "<< start_id << " does not have a recorded location."<<std::endl;
}

/**
 * Prints a sorted list of degrees (smallest to largest) along with how many users
 * have that degree. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
 //generate a map of degrees as the histogram and output it
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
    std::map<ID_TYPE,ID_TYPE > histogram;
    std::vector<std::pair<const ID_TYPE,ID_TYPE >> valid;
    int count=0;
    for(ADJ_TYPE::const_iterator it= adj_lists.begin();it!=adj_lists.end();++it){
        if(it->second.size()>0){
            count++;
            ++histogram[it->second.size()];
        }
    }
    outfile<<"Histogram for "<<count<<" users:"<<std::endl;
    for(std::map<ID_TYPE,ID_TYPE>::iterator it= histogram.begin();it!=histogram.end();++it){
        outfile<<" Degree "<<it->first<<": "<< it->second<<std::endl;
    }

}

/**
 * Prints a sorted list of user IDs (smallest to largest) along with the degree for
 * each user. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
 //loop through the map and output thier respective degrees
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
    std::vector<std::pair<const ID_TYPE,std::vector<ID_TYPE > >> valid;
    for(ADJ_TYPE::const_iterator it= adj_lists.begin();it!=adj_lists.end();++it){
        if(it->second.size()>0){
            valid.push_back(std::make_pair(it->first,it->second));
        }
    }
    outfile<<"Degrees for "<<valid.size()<< " users:"<<std::endl;
    for(int i=0;i<valid.size();i++){
        outfile<<" "<<valid[i].first<<": Degree "<<valid[i].second.size()<<std::endl;
    }

}

/**
 * Prints all friends of a particular user who have a particular degree.
 * Sorted by user ID (from smallest to largest).
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 * @param start_id User whose friends we are looking at
 * @param degree The degree of friends we want to print. Will be >=1.
 */
 //assert that the start_id exists and then find the user's friends check their values and
 //output them
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree){
    bool check = false;
    for(ADJ_TYPE::const_iterator it= adj_lists.begin();it!=adj_lists.end();++it){
        if(it->first==start_id){
            check = true;
            break;
        }
    }
    if (check) {
        ADJ_TYPE::const_iterator base = adj_lists.find(start_id);
        std::vector<ID_TYPE> valid;
        for (ID_TYPE i = 0; i < base->second.size(); i++) {
            ADJ_TYPE::const_iterator test = adj_lists.find(base->second[i]);
            if (test != adj_lists.end() and test != base) {
                if (test->second.size() == degree) {
                    valid.push_back(test->first);
                }
            }
        }
        if (valid.size() > 0) {
            outfile << "User " << base->first << " has " << valid.size() << " friend(s) with degree " << degree << ":";
            for (ID_TYPE i = 0; i < valid.size(); i++) {
                outfile << " " << valid[i];
            }
            outfile << std::endl;
        } else {
            outfile << "User " << base->first << " has " << valid.size() << " friend(s) with degree " << degree<<std::endl;
        }
        return;;
    }
    outfile<<"There is no user with friends and ID "<< start_id<<std::endl;
}

/**
 * Prints friends of a particular user within a certain distance of that user.
 * Sorted from shortest distance to user to longest distance to user.
 * @param adj_lists Adjacency lists structure
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
 //assert that the user exists finds the user friends check that they have a location and output them
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, 
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance){
    bool check = false;
    for(GEO_TYPE::const_iterator it = locations.begin();it!=locations.end();++it){
        if(it->first==start_id) {
            check = true;
            break;
        }
    }
    if(check) {
        ADJ_TYPE::const_iterator base = adj_lists.find(start_id);

        std::vector<GEO_TYPE::const_iterator> friends;
        for (int i = 0; i < base->second.size(); i++) {
            GEO_TYPE::const_iterator f = locations.find(base->second[i]);
            if (f != locations.end()) {
                friends.push_back(f);
            }
        }
        GEO_TYPE::const_iterator b = locations.find(start_id);
        std::vector<std::pair<double, ID_TYPE >> valid;
        for (int i = 0; i < friends.size(); ++i) {
            double test = distanceEarth(b->second.first, b->second.second, friends[i]->second.first,
                                        friends[i]->second.second);
            if (fabs(test) <= max_distance) {
                valid.push_back(std::make_pair(test, friends[i]->first));
            }
        }
        sort(valid.begin(), valid.end());
        if (valid.size() == 0) {
            outfile << "There are no friends within " << max_distance << " km of user " << start_id << std::endl;
            return;
        } else {
            outfile << "Friends within " << max_distance << " km of user " << start_id << ":" << std::endl;
            for (int i = 0; i < valid.size(); i++) {
                outfile << " " << float(valid[i].first) << " km: " << valid[i].second << std::endl;
            }
        }
        return;
    }
    for(ADJ_TYPE::const_iterator it = adj_lists.begin();it!=adj_lists.end();++it) {
        if(start_id==it->first) {
            outfile << "User ID " << start_id << " does not have a recorded location." << std::endl;
            return;
        }
    }
    outfile<<"There is no user with friends and ID "<< start_id<<std::endl;
}

/**
 * Prints users with an ID that is "close" to a particular user's ID.
 * Sorted from smallest to largest user ID.
 * Only prints for degree >=1.
 *
 * If there are M IDs that should be printed this function should only use
 * ADJ_TYPE::const_iterator::operator++ / ADJ_TYPE::const_iterator::operator-- O(M) times
 *
 * @param outfile File to write output to
 * @param begin The .begin() iterator for the adjacency lists structure
 * @param end The .end() iterator for the adjacency lists structure
 * @param start_it Iterator for user we are using as our baseline (i.e. 0 diifference)
 *        It is possible that the start_it was not found in the data.
 * @param offset Maximum absolute difference from start_id that a printed user's
 *               ID can have
 */
 //create a low and high bound and due to typedefs make sure that there is no integer overflow
 //otherwise just check that the values are valid and output.
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, 
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset){
    ID_TYPE low=0;
    if(offset<start_it->first){
        low= start_it->first-offset;}

    ID_TYPE high= start_it->first+offset;
    bool check = false;
    for(ADJ_TYPE::const_iterator it= begin;it!=end;++it){
        if(it==start_it){
            check=true;
            break;
        }
    }
    if(check) {
        std::vector<ID_TYPE> valid;
        for (ADJ_TYPE::const_iterator it = begin; it != end; ++it) {
            if (low <= it->first and it->first <= high and it->first!=start_it->first) {
                valid.push_back(it->first);
            }
        }
        if(valid.size()>0) {
            outfile << "Users with an ID within +/-" << offset << " of " << start_it->first << ":";
            for (int i = 0; i < valid.size(); i++) {
                outfile << " " << valid[i];
            }
            outfile << std::endl;
            return;
        }
        else{
            outfile<<"There are no users with an ID within +/-"<<offset<<" of "<<start_it->first<<std::endl;
            return;
        }
    }
    else{
        outfile<<"There is no user with the requested ID"<<std::endl;
    }

}
