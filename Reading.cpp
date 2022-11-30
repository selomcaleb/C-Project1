#include<iostream>
#include "Node.cpp"
#include "Route.cpp"
#include <unordered_map>
#include<vector>
#include<deque>
#include<unordered_set>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
class Reading{
public:
    unordered_map<string, vector<Route>>  readRoutes(){
        unordered_map<string, vector<Route>> routesMap;
        string readLine;
        ifstream readRouteFile("/Users/selomcaleb/CLionProjects/FINAL C++ PROJECT/routes.csv");
        while (getline(readRouteFile, readLine)) {
            vector<string> data;
            stringstream iss(readLine);
            while (iss.good()) {
                string splitLine;
                getline(iss, splitLine, ',');
                data.push_back(splitLine);
            }
            string sourceAirportCode = data[2];
            string destinationAirportCode = data[4];
            string airlineId = data[0];
            int noOfStops = stoi(data[7]);
            Route route(airlineId, destinationAirportCode, noOfStops);
            /* Checking if the key is already present in the map. If not, it is creating a new key with an empty vector. */
            if (routesMap.count(sourceAirportCode) > 0) {
                routesMap.at(sourceAirportCode).push_back(route);
            }

                /* Adding the route object to the vector of routes. */
            else {
                vector<Route> routeDetails;
                routeDetails.push_back(route);
                routesMap.insert({sourceAirportCode, routeDetails});
            }
        }
        readRouteFile.close();
        return routesMap;
    };


    unordered_map<string, vector<string>> readAirports(){
        unordered_map<string, vector<string>> locationToAirportsMap;
        //unordered_map<string,string> airportToPlaces;
        string readLine;
        ifstream airportReader("/Users/selomcaleb/CLionProjects/test/airports.csv");

        while (getline(airportReader, readLine)) {
            vector<string> data;
            stringstream iss(readLine);
            while (iss.good()) {
                string splitLine;
                getline(iss, splitLine, ',');
                data.push_back(splitLine);
            }
            if (data[4] == "\\N") continue;
            string airportCode = data[4];
            string cityCountry = data[2] + ',' + ' ' + data[3];
            //airportToPlaces[airportCode] = cityCountry;


            if (locationToAirportsMap.count(cityCountry) > 0) {
                locationToAirportsMap.at(cityCountry).push_back(airportCode);
            } else {
                vector<string> airportCodes;
                airportCodes.push_back(airportCode);
                locationToAirportsMap.insert({cityCountry, airportCodes});
            }
        }
        airportReader.close();
        return locationToAirportsMap;
    };

    unordered_map<string,string> readAirportAgain() {
        unordered_map<string, string> airportToPlaces;
        string readLine;
        ifstream airportReader("/Users/selomcaleb/CLionProjects/test/airports.csv");

        while (getline(airportReader, readLine)) {
            vector<string> data;
            stringstream iss(readLine);
            while (iss.good()) {
                string splitLine;
                getline(iss, splitLine, ',');
                data.push_back(splitLine);
            }
            if (data[4] == "\\N") continue;
            string airportCode = data[4];
            string cityCountry = data[2] + ',' + ' ' + data[3];
            airportToPlaces[airportCode] = cityCountry;

            //airportToPlaces.insert({airportCode,cityCountry});



        }
        airportReader.close();
        cout<<"ha"<< airportToPlaces.size() <<endl;
        return airportToPlaces;
    };



    vector<string> breadthFirstSearch(string initialLoc, string destinationLoc){

        deque<shared_ptr<Node>> frontier;
        unordered_set<string> exploredSet;
        unordered_map<string, string> airportsToPlaces = readAirportAgain();
        unordered_map<string, vector<string>> locationToAirportsMap = readAirports();
        unordered_map<string, vector<Route>> routesMap = readRoutes();
        vector<string> airports = locationToAirportsMap.at(initialLoc);
       // unordered_map<string, string> airportsToPlaces = readAirportAgain();
        vector<string> test;
        //unordered_map<string, string> airportsToPlaces = readAirportAgain();
//        if(!airports.empty()) cout<<"yes";

        for(auto airport: airports){
            shared_ptr<Node> airportNode = make_shared<Node>(nullptr,airport,0,"", nullptr);
            frontier.push_back(airportNode);
        }

        while (!frontier.empty()){
            shared_ptr<Node> currentNode = frontier.front();
            frontier.pop_front();
            exploredSet.insert(currentNode->getAirportCode());
            if (currentNode == nullptr){
                continue;
            }

            if (routesMap.count(currentNode->getAirportCode())==0) cout<<"not found";
            vector<Route> successors = routesMap.at(currentNode->getAirportCode());
            if (!successors.empty()){
                for(Route successor: successors){
                    shared_ptr<Node> child = make_shared<Node>(currentNode,successor.getDestinationAirportCode(),successor.getStops(),successor.getAirlineCode(),
                                                               nullptr);
                   cout<<"child"<<child->getAirportCode();

                    string destinationName = airportsToPlaces.at(child->getAirportCode());
                    if (destinationName=="") cout<<"yes";

                    if (destinationName == destinationLoc){
                        child->solutionPath();
                    }

                    if (std::find(frontier.begin(),frontier.end(),child) == frontier.end() && exploredSet.find(child->getAirportCode()) == exploredSet.end()){
                        frontier.push_back(child);
                    }

                }

            }
            cout <<"No solution found" << endl;
            vector<string>empty;
            return empty;
        }

    }


};

    int main(){
        ifstream inputFile("/Users/selomcaleb/CLionProjects/FINAL C++ PROJECT/kumasi-winnipeg.txt");
        string initialLoc;
        string destinationLoc;


        getline(inputFile, initialLoc);
        getline(inputFile,destinationLoc);
        ofstream outputFile("kumasi-winnipeg_output.txt");
        //deque<Node> frontier;
        //unordered_set<string> exploredSet;
        //vector<string> airports = locationToAirportsMap.at(initialLoc);
        Reading bf = Reading();
        vector<string> path = bf.breadthFirstSearch(initialLoc,destinationLoc);
        cout<<"path" <<path.size();
        int numberOfFlights = 0;
        if(!path.empty()){
            for (string flight:path){
                outputFile << flight << endl;
                numberOfFlights++;
            }

            outputFile <<"Total Flights: " << numberOfFlights;
        } else{
            outputFile <<"solution not found";
        }
        outputFile.close();



        return 0;
    };

