#include <iostream>
using namespace std;

class Airport{
public:
    string airportID;
    string airportName;
    string airportCity;
    string country;
    string IACOCode;


    Airport(string airportID,string airportName,string airportCity, string country,string IACOCode){
        this->airportID = airportID;
        this->airportName =airportName;
        this->airportCity = airportCity;
        this->country = country;
        this->IACOCode =IACOCode;
    }

    string getAirportId()  {
        return airportID;
    }

    string getAirportName()  {
        return airportName;
    }

    string getAirportCity()  {
        return airportCity;
    }

   string getCountry() {
        return country;
    }

   string getIACOCode()  {
        return IACOCode;
    }

    void setAirportId(string airportId) {
        airportID = airportId;
    }

    void setAirportName(string airportName) {
       airportName = airportName;
    }

    void setAirportCity(string airportCity) {
        airportCity = airportCity;
    }

    void setCountry( string country) {
       country = country;
    }

    void setIACOCode(string IACOCode) {
        IACOCode = IACOCode;
    }

};


