//
// Created by Selom Caleb Arcmann-Ackummey on 28/11/2022.
//



#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "routes.cpp"



using namespace std;

template<typename K, typename V>

void print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

int main() {
    static unordered_map<string, vector<Routes>> routeHashMap;
    static unordered_map<string, string> airports;
    static unordered_map<string, vector<string>> locationToAirportsMap;

/**
   * Reading from the airports.csv file
 **/
    try {
        ifstream airportsFile("/Users/selomcaleb/Desktop/ICPTeam/airports.csv");
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

            airports.insert({key, values});
            /* Create new vector of airport codes and store them as airportValues */
            vector<string> airportValues;
            for (const auto& [k, v] : airports) {
                if (v == values) {
                    airportValues.push_back(k);
                }
            }


            /*
            * If airportValues is null, the String(city, country) key does not have any value yet.
            * Create new airport values arraylist for the key and add corresponding airport code to it.
            */
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

                /*
                 * If airportValues is not null, check if current route is in values before
                 * adding, to prevent duplicate airport codes in each value arraylist
                 */
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
        print_map(airports);


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
            // getline(input, stops);

            Routes routes(airlinecode, airlineid, destairportcode, stops);

            values.push_back(routes);
            cout << routes.toString() << endl;
            routeHashMap.insert({key, values});

        }
        for (Routes i: values){cout << i.toString() << endl;}
        routesFile.close();

    } catch (const exception &e) {
        cout << "Unable to open or read routes file." << e.what() << endl;
    }

    return 0;
}
