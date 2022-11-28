#include <iostream>
#include <string>
#include <any>
using namespace std;

class Routes
{
    // instance variables of the Routes class
    protected:
    string airlineCode;
    string airlineID;
    string destinationAirportCode;
    int stops;
    
    public :
    // constructor method for the instance variables
    Routes(string airlineCode, string airlineID, string destinationAirportCode, int stops)
    {
        this->airlineCode = airlineCode;
        this->airlineID = airlineID;
        this->destinationAirportCode = destinationAirportCode;
        this->stops = stops;
    }

    string getAirlineCode();
    void setAirlineCode(string airlineCode);

    string getAirlineID();
    void setAirlineID(string airlineID);

    string getDestinationAirportCode();
    void setDestinationAirportCode(string destinationAirportCode);

    int getStops();
    void setStops(int stops);

};

string Routes:: getAirlineCode(){
    return airlineCode;
}

void Routes:: setAirlineCode(string airlineCode){
    this->airlineCode = airlineCode;
}

string Routes:: getAirlineID(){
    return airlineID;
}

void Routes:: setAirlineID(string airlineID){
    this->airlineID = airlineID;
}

string Routes:: getDestinationAirportCode(){
    return destinationAirportCode;
}

void Routes:: setDestinationAirportCode(string destinationAirportCode){
    this->destinationAirportCode = destinationAirportCode;
}

int Routes:: getStops(){
    return stops;
}

void Routes:: setStops(int stops){
    this->stops = stops;
}