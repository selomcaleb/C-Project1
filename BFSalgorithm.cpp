#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <iterator>
#include "Routes.cpp"
#include "Node.cpp"
#include <memory>


class BFS
{
    
    protected:
    string initialLoc;
    string destinationLoc;
    deque<shared_ptr<Node>> frontier;
    unordered_set<string> exploredSet;
    vector<string> airports;
    unordered_map<string, string> airportsToPlaces;
    unordered_map<string, vector<string>> locationToAirportsMap;
    unordered_map<string, vector<shared_ptr<Routes>>> routesMap;

    public:
    BFS(unordered_map<string, string> airportsMap, unordered_map<string, vector<string>> locationsMap);

    bool contains(deque<shared_ptr<Node>> aQueue, shared_ptr<Node> aNode);

    bool contains(unordered_set<string> aSet, string stringItem);

    bool equals(shared_ptr<Node> node1, shared_ptr<Node> node2);

    bool equals(string firstString, string secondString);

    bool equals(vector<Routes> firstList, any secondItem);

    vector<string> breadthFirstSearch(string initialLoc, string destinationLoc);

};


BFS::BFS (unordered_map<string, string> airportsMap, unordered_map<string, vector<string>> locationsMap){
        this-> airportsToPlaces = airportsMap;
        this->locationToAirportsMap = locationsMap;
}

bool BFS::contains(deque<shared_ptr<Node>> aQueue, shared_ptr<Node> aNode){
    bool check;
    deque<shared_ptr<Node>> newQueueCopy = aQueue;
    while(!newQueueCopy.empty())
    {
        shared_ptr<Node> item = newQueueCopy.front();
        check = equals(item, aNode);
    }
    return check;
}


bool BFS::contains(unordered_set<string> aSet, string stringItem){
    bool check;
    for(auto item : aSet)
    {
        check = (item == stringItem);
        if(check == true)
            break;
    }
    return check;
}


bool BFS::equals(shared_ptr<Node> firstNode, shared_ptr<Node> secNode)
{
    return (typeid(firstNode) == typeid(secNode));
}

bool BFS::equals(string firstString, string secondString)
{
    return (firstString == secondString);
}

bool BFS::equals(vector<Routes> firstList, any secondItem)
{
    return (typeid(firstList) == typeid(secondItem));
}


vector<string> BFS::breadthFirstSearch(string initialLoc, string destinationLoc)
{
    vector<string>airports = locationToAirportsMap[initialLoc];

    if (!airports.empty()){
        for(string airport:airports)
        {
            shared_ptr<Node> airportNode(nullptr);
            airportNode = make_shared<Node>(nullptr, airport, nullptr, 0, nullptr);
            frontier.push_back(airportNode);
        }
    }

    while(!frontier.empty())
    {
        shared_ptr<Node> currentNode = frontier.front();
        frontier.pop_front();
        vector<shared_ptr<Routes>> successorStates = routesMap[currentNode->getAirportCode()];
        if (currentNode == nullptr){
            continue;
        }

        exploredSet.insert(currentNode->getAirportCode());


        vector<shared_ptr<Routes>> successorStates = routesMap[currentNode->getAirportCode()];       
        if (!successorStates.empty()){
            for(shared_ptr<Routes> successorState: successorStates)
            {
                shared_ptr<Node> child= make_shared<Node>(currentNode, successorState->getDestinationAirportCode(), successorState->getAirlineCode(), successorState->getStops(), nullptr);

                string destinationName = airportsToPlaces[child->getAirportCode()];
                if (destinationName == destinationLoc){
                    return child->solutionPath();
                }

                if (!(contains(frontier, child)) && !(contains(exploredSet, child->getAirportCode()))){
                    
                   frontier.push_back(child);
                }
                
            }
        }
        cout << "Sorry, no solution found!"<<endl;
        return vector<string>();
    }
}