#include "lab11.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

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
bool Lot::operator==(const Lot& l) const {
    if (this->lat != l.lat) {
        return false;
    }
    if (this->lon != l.lon) {
        return false;
    }
    if (this->width != l.width) {
        return false;
    }
    if (this->length != l.length) {
        return false;
    }
    return true;
}
bool Lot::operator<(const Lot& l) const {
    if (this->value() < l.value()) {
        return true;
    }
    return false;
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
    vector<shared_ptr<Lot>>* arr = new vector<shared_ptr<Lot>>;
    this->lots = arr;
}

//Destructor
Block::~Block() {
    delete this->lots;
    delete this;
}

//Methods
void Block::add_lot(Lot* l) {
    shared_ptr<Lot> p1(l);
    this->lots->push_back(p1);
}
double Block::total_value() const {
    double value = 0;
    for (vector<shared_ptr<Lot>>::iterator it = this->lots->begin(); it != this->lots->end(); it++) {
        value += (*it)->value();
    }
    return value;
}
void Block::sort(bool order) {
    if (order == false) {
        std::sort(this->lots->begin(), this->lots->end());
    }
    else if (order == true) {
        std::sort(this->lots->begin(), this->lots->end(), ReverseOrder());
    }
}