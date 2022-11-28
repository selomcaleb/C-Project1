//
// Created by Selom Caleb Arcmann-Ackummey on 26/11/2022.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>



using namespace std;

template<typename K, typename V>

void print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

int main() {

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

            values = city + ", " + country;

            airports.insert({key, values});

        }

        print_map(airports);
        airportsFile.close();

    } catch (const exception &e) {
        cout << "Cannot open or read file." << e.what() << endl;
    }

    return 0;
}

