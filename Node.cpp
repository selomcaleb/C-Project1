#include <iostream>
#include <vector>
#include <algorithm>
#include "Routes.cpp"
using namespace std;

class Node{

    protected:
    Node parentNode;
    string airportCode;
    string airlineCode;
    int stops;
    vector<Routes>successors;

    public:

    Node(Node parentNode, string airportCode, string airlineCode, int stops, vector<Routes>successors){
        this->parentNode = parentNode;
        this->airportCode = airportCode;
        this->airlineCode = airlineCode;
        this->stops = stops;
        this->successors = successors;
    }

    string to_string(){
        return "Node{" +
                "parentNode=" + parentNode +
                ", airportCode='" + airportCode + '\'' +
                ", airlineCode='" + airlineCode + '\'' +
                ", stops=" + stops +
                ", successors=" + successors +
                '}';
    }

    bool operator==(const Node &obj){

        if (this *== obj) {
           return true;
       }
       if (obj == null || getClass() != obj.getClass()){
           return false;
       }
       Node node = (Node) obj;
       return  parentNode==node.parentNode && airportCode==node.airportCode
               && airlineCode==node.airlineCode && successors==node.successors
               && stops == node.stops;
    }

    int hashCode(){
        return hash(parentNode, airportCode, airlineCode, stops, successors);
    }

    Node getParentNode() {
        return parentNode;
    }

    void setParentNode(Node parentNode) {
        this->parentNode = parentNode;
    }

    string getAirportCode() {
        return airportCode;
    }

    void setAirportCode(string airportCode) {
        this->airportCode = airportCode;
    }

    string getAirlineCode() {
        return airlineCode;
    }

    void setAirlineCode(string airlineCode) {
        this->airlineCode = airlineCode;
    }

    int getStops() {
        return stops;
    }

    void setStops(int stops) {
        this->stops = stops;
    }

    vector<Routes> getSuccessors() {
        return successors;
    }

    void setSuccessors(vector<Routes> successors) {
        this->successors = successors;
    }


    /**
     * This function takes the current node  and returns an ArrayList of Strings from the start node to the current node
     *
     * @return The solution path is being returned.
     */

    vector<string> solutionPath(){
        vector<string> airportCodes;
        vector<string> airlineCodes;
        vector<string> solution;
        vector<int> stops;
        Node thisNode = this;

        while(thisNode != nullptr){
            airlineCodes.push_back(thisNode.getAirlineCode());
            airportCodes.push_back(thisNode.getAirportCode());
            stops.push_back(thisNode.getStops());
            thisNode = thisNode.parentNode;
        }
        reverse(airlineCodes.begin(), airlineCodes.end());
        reverse(airportCodes.begin(), airportCodes.end());

        for (int i = 0;i < airlineCodes.size()-1;i++){
            string result = airlineCodes.at(i+1) + " from " + airportCodes.at(i) + " to " +
                    airportCodes.at(i+1) + " " + to_string(stops.at(i)) + " stops.";
            solution.push_back(result);
        }

        return solution;

    }
};