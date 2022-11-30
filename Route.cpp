#include <string>
#include <vector>
#pragma once

using namespace std;

class Route{
private:
    string airlineCode;
    string destinationAirportCode;
    int stops;

public:
    Route(string airlineCode,string destinationAirportCode,int stops){
        this->airlineCode = airlineCode;
        this->destinationAirportCode = destinationAirportCode;
        this->stops = stops;
    }



    string getAirlineCode()  {
        return airlineCode;
    }

    string getDestinationAirportCode() {
        return destinationAirportCode;
    }

    int getStops()  {
        return stops;
    }

};
