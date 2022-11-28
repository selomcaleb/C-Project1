//
// Created by Selom Caleb Arcmann-Ackummey on 28/11/2022.
//
#include <iostream>
using namespace std;


class Airport{
public:
    //member variables for the Airport class
    string airportID;
    string airportName;
    string airportCity;
    string country;
    string ICAOCode;


    //member functions for the Airport class
    string getAirportID();
    string setAirportID(string airportID);

    void setAirportName(string airportName);
    string getAirportName();

    string getCity();
    void setCity(string airportCity);

    string getCountry();
    void setCountry(string Country);

    string getICAOCode();
    void setICAOCode(string IACOCode);

    string toString();

    Airport(string ID, string name,string city,string country,string IACO){
        this->airportName =  name;
        this->airportID = ID;
        this->airportCity = city;
        this->country = country;
        this->ICAOCode = IACO;
    }
};

string Airport::getAirportID() {
    return airportID;
}

string Airport::setAirportID(string airportID) {
    this->airportID = airportID;
}

string Airport::getCity() {
    return airportCity;
}

void Airport::setCity(string airportCity) {
    this->airportCity = airportCity;
}

string Airport::getAirportName() {
    return airportName;
}

void Airport::setAirportName(string airportName) {
    this->airportName=airportName;
}

string Airport::getCountry() {
    return country;
}

void Airport::setCountry(string Country) {
    this->country = Country;
}

string Airport::getICAOCode() {
    return ICAOCode;
}

void Airport::setICAOCode(string IACOCode) {
    this->ICAOCode = IACOCode;

}

string Airport:: toString(){
    return this->airportID + " " + airportName + " "  + airportCity + " " + country + " " + ICAOCode;
}





