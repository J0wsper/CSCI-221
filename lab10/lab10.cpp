#include "lab10.hpp"
#include <iostream>
#include <math.h>

//Lot below

//Constructor
Lot::Lot(double lat, double lon, double width, double length) {
    this->lat = lat;
    this->lon = lon;
    this->width = width;
    this->length = length;
}

//Methods
double Lot::land_area() const {
    return this->width*this->length;
}
double Lot::value() const {
    return (this->land_area()*16);
}


//DevelopedLot below

//Constructor
DevelopedLot::DevelopedLot(double lat, double lon, double width, double length, double footprint, unsigned floors)
: Lot(lat, lon, width, length) {
    this->footprint = footprint;
    this->floors = floors;
}

//Methods
double DevelopedLot::floor_area_ratio() const {
    return (this->floors*this->footprint)/(this->land_area());
}
double DevelopedLot::value() const {
    double land_value = this->land_area()*16;
    return (100*this->floors*this->footprint)+land_value;
}


//Offices below

//Constructor
Office::Office(double lat, double lon, double width, double length, double footprint, unsigned floors, unsigned offices) 
: DevelopedLot(lat, lon, width, length, footprint, floors) {
    this->offices = offices;
}

//Methods
double Office::value() const {
    double land_area = pow(this->floor_area_ratio(),-1)*(this->floors*this->footprint);
    double land_value = land_area * 16;
    double building_value = (100*this->floors*this->footprint)+land_value;
    return (200*this->offices)+building_value;
}



//Blocks below

//Constructor
Block::Block() {
    this->length = 0;
    Lot** arr = new Lot*[20]();
    this->arr = arr;
}

//Destructor
Block::~Block() {
    unsigned i = 0;
    while (i < this->length) {
        delete this->arr[i];
        i++;
    }
    delete this->arr;
}

//Methods
void Block::add_lot(Lot* Lot) {
    this->arr[this->length] = Lot;
    this->length++;
}
double Block::total_value() const {
    unsigned i = 0;
    double value = 0;
    while (i < this->length) {
        value += this->arr[i]->value();
        i++;
    }
    return value;
}