#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
#include "Routes.cpp"
#include "Node.cpp"
#include "BFSalgorithm.cpp"

using namespace std;

template<typename K, typename V>

void print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

int main() {
    static unordered_map<string, vector<Routes>> routesMap;
    static unordered_map<string, string> airportsToPlaces;
    static unordered_map<string, vector<string>> locationToAirportsMap;

    /**
       * Reading from the airports.csv file
     **/
    try {
        ifstream airportsFile("airports.csv");
        string row = "";
        int count = 0;
        string ignore;
        string key;
        string values;
        string city;
        string country;
        string code;
        char delim = ',';

        while (getline(airportsFile, row)) {
            if (count == 0) {
                count++;
                continue;
            }

            stringstream input(row);

            getline(input, ignore, delim);
            getline(input, ignore, delim);
            getline(input, city, delim);
            getline(input, country, delim);
            getline(input, key, delim);
            getline(input, code, delim);

            values = city + ", " + country;

            airportsToPlaces.insert({key, values});
            /* Create new vector of airport codes and store them as airportValues */
            vector<string> airportValues;
            for (const auto& [k, v] : airportsToPlaces) {
                if (v == values) {
                    airportValues.push_back(k);
                }
            }



            if (airportValues.empty()) {
                vector<string> newAirportValues;
                string codeforAirport = key;
                string nullValue = "\\N";
                if (codeforAirport == nullValue) {
                    newAirportValues.push_back(code);
                } else {
                    newAirportValues.push_back(key);
                }
                locationToAirportsMap.insert({values, newAirportValues});

                
            } else {
                static string codeForAirport;
                if (!std::count(airportValues.begin(), airportValues.end(), key)) {
                    if (key == "\\N") {
                        string codeForAirport = code;
                    } else {
                        string codeForAirport = key;
                    }
                    airportValues.push_back(codeForAirport);
                    locationToAirportsMap.insert({values, airportValues});
                }
            }

        }
        for (auto &itr: locationToAirportsMap) {
            for (string i: itr.second){
                cout << itr.first << ": " << i << endl;
            }
        }
        cout << "" << endl;
        print_map(airportsToPlaces);


        airportsFile.close();

    } catch (const exception &e) {
        cout << "Cannot open or read file." << e.what() << endl;
    }

    /**
        * Reading from the  routes.csv file
    **/
    try{
        ifstream routesFile("routes.csv");
        string row = "";
        int count = 0;
        string ignore;
        string key;
        string airlinecode;
        string airlineid;
        string destairportcode;
        int stops;
        static vector<Routes> values;
        char delim = ',';

        while (getline(routesFile, row)) {
            if (count == 0) {
                count++;
                continue;
            }

            stringstream input(row);

            getline(input, airlinecode, delim);
            getline(input, airlineid, delim);
            getline(input, key, delim);
            getline(input, ignore, delim);
            getline(input, destairportcode, delim);
            getline(input, ignore, delim);

            Routes route(airlinecode, airlineid, destairportcode, stops);

            values.push_back(route);
            cout << route.toString() << endl;
            routesMap.insert({key, values});

        }
        for (Routes i: values){cout << i.toString() << endl;}
        routesFile.close();

    } catch (const exception &e) {
        cout << "Unable to open or read routes file." << e.what() << endl;
    }


    //reading from the input file
    ifstream inputFile("kumasi-winnipeg.txt");
    string initialLoc;
    string destinationLoc;

    getline(inputFile, initialLoc);
    getline(inputFile,destinationLoc);

    BFS BFS(airportsToPlaces, locationToAirportsMap);
    queue<Node> frontier;
    set<string> exploredSet;
    vector<string> airports = locationToAirportsMap.at(initialLoc);

    ofstream outputFile("kumasi-winnipeg_output.txt");
    vector<string> path = BFS.breadthFirstSearch(initialLoc,destinationLoc);
    int numberOfFlights = 0;
    if(!path.empty()){
        for (string flight:path){
            outputFile << flight << endl;
            numberOfFlights++;
        }

        outputFile <<"Total Flights: " + numberOfFlights;
    } else{
        outputFile <<"solution not found";
    }

    outputFile.close();



    return 0;
}