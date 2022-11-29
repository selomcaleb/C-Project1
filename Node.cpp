#include <iostream>
#include <vector>
#include <algorithm>
#include "Routes.cpp"
using namespace std;

class Node{

    private:
    Node *parentNode;
    string airportCode;
    string airlineCode;
    int stops;
    vector<Routes>successors;

    public:

    Node(Node *parentNode, string airportCode, string airlineCode, int stops, vector<Routes>successors){
        this->parentNode = parentNode;
        this->airportCode = airportCode;
        this->airlineCode = airlineCode;
        this->stops = stops;
        this->successors = successors;
    }

    string to_string();
    bool operator==(const Node &obj);
    int hashCode();

    Node getParentNode();
    void setParentNode(Node *parentNode);

    string getAirportCode();
    void setAirportCode(string airportCode);

    string getAirlineCode();
    void setAirlineCode(string airlineCode);

    int getStops();
    void setStops(int stops);

    vector<Routes> getSuccessors();
    void setSuccessors(vector<Routes> successors);


    vector<string> solutionPath();
};

string Node:: to_string(){
    return "Node{parentNode= ", *parentNode,
            ", airportCode='" + airportCode + '\'' +
            ", airlineCode='" + airlineCode + '\'' +
            ", stops=", stops, 
            ", successors=", successors,
            "}";
}

bool Node:: operator==(const Node &obj){

    if (*this == obj) {
        return true;
    }
    if (&obj == NULL || typeid(obj) != typeid(this)){
        return false;
    }
    Node node = (Node) obj;
    return  parentNode==node.parentNode && airportCode==node.airportCode
            && airlineCode==node.airlineCode && successors==node.successors
            && stops == node.stops;
}

int Node:: hashCode(){
    return hash(*parentNode, airportCode, airlineCode, stops, successors);
}

Node Node:: getParentNode() {
    return *parentNode;
}

void Node:: setParentNode(Node *parentNode) {
    this->parentNode = parentNode;
}

string Node:: getAirportCode() {
    return airportCode;
}

void Node:: setAirportCode(string airportCode) {
    this->airportCode = airportCode;
}

string Node:: getAirlineCode() {
    return airlineCode;
}

void Node:: setAirlineCode(string airlineCode) {
    this->airlineCode = airlineCode;
}

int Node:: getStops() {
    return stops;
}

void Node:: setStops(int stops) {
    this->stops = stops;
}

vector<Routes> Node:: getSuccessors() {
    return successors;
}

void Node:: setSuccessors(vector<Routes> successors) {
    this->successors = successors;
}


/**
 * This function takes the current node  and returns an ArrayList of Strings from the start node to the current node
 *
 * @return The solution path is being returned.
 */

vector<string> Node:: solutionPath(){
    vector<string> airportCodes;
    vector<string> airlineCodes;
    vector<string> solution;
    vector<int> stops;
    Node thisNode = *this;

    while(&thisNode != NULL){
        airlineCodes.push_back(thisNode.getAirlineCode());
        airportCodes.push_back(thisNode.getAirportCode());
        stops.push_back(thisNode.getStops());
        thisNode = *thisNode.parentNode;
    }
    reverse(airlineCodes.begin(), airlineCodes.end());
    reverse(airportCodes.begin(), airportCodes.end());

    for (int i = 0;i < airlineCodes.size()-1;i++){
        string result = airlineCodes.at(i+1) + " from " + airportCodes.at(i) + " to " +
                airportCodes.at(i+1) + " " + stops.at(i) + " stops.";
        solution.push_back(result);
    }

    return solution;

    }