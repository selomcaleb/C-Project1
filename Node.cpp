#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <fstream>
#include "Route.cpp"

#pragma once

using namespace std;

class Node {
public:
    shared_ptr<Node> parentNode;
    string airportCode;
    int stops;
    string airlineCode;
    shared_ptr<vector<Route>> successors;

    Node(shared_ptr<Node> parentNode, string airportCode, int stops, string airLineCode,
         shared_ptr<vector<Route> > successors) {
        this->parentNode = parentNode;
        this->airportCode = airportCode;
        this->stops = stops;
        this->airlineCode = airLineCode;
        this->successors = successors;
    }

    shared_ptr<Node> getParentNode() {
        return parentNode;
    }

    string getAirportCode() {
        return airportCode;
    }

    int getStops() {
        return stops;
    }

    string getAirlineCode() {
        return airlineCode;
    }

    shared_ptr<vector<Route>> getSuccessors() {
        return successors;
    }

    bool operator==(const Node &node) {
        return node.airportCode == this->airportCode && node.airlineCode == this->airlineCode &&
               node.successors == this->successors;
    }

    void solutionPath() {
        vector<string> airportCodes;
        vector<string> airlineCodes;
        vector<string> solution;
        vector<int> stops;
        Node *thisNode = this;

        while (thisNode != nullptr) {
            airportCodes.push_back(thisNode->getAirportCode());
            airlineCodes.push_back(thisNode->getAirlineCode());
            stops.push_back(thisNode->getStops());
            thisNode = thisNode->parentNode.get();
        }

        reverse(airlineCodes.begin(), airlineCodes.end());
        reverse(airportCodes.begin(), airportCodes.end());

        for (int i = 0; i < airlineCodes.size() - 1; i++) {
            string result = airlineCodes.at(i + 1) + " from " + airportCodes.at(i) + " to " +
                            airportCodes.at(i + 1) + " " + to_string(stops.at(i)) + " stops.";
            solution.push_back(result);
        }

        //write the contents of the solution list to a file
        ofstream myfile("kumasi-winnipeg-output.txt");
        for (auto & i : solution) {
            myfile << i << endl;
        }
        myfile.close();
    }

};
