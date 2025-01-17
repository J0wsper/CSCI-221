#ifndef _LAB11_HPP_
#define _LAB11_HPP_
#include <vector>
#include <memory>
#include <optional>
#include <iostream>

class Lot {

private:
    double lat;
    double lon;
    double width;
    double length;

protected:
    double land_area() const;

public:

    //Constructors
    Lot(double, double, double, double);
    Lot() : lat(0), lon(0), width(0), length(0) {};

    //Destructor
    virtual ~Lot() {};

    //Methods
    virtual double value() const;
    bool operator==(const Lot&) const;
    bool operator<(const Lot&) const;
};

class DevelopedLot : public Lot {

protected:
    double footprint;
    unsigned floors;
    double floor_area_ratio() const;

public:

    //Constructors
    DevelopedLot(double, double, double, double, double, unsigned);
    DevelopedLot() : Lot(), footprint(0), floors(0) {};

    //Destructor
    virtual ~DevelopedLot() {};

    //Methods
    double value() const override; 
};

class Office : public DevelopedLot {
private:
    unsigned offices;
public:

    //Constructors
    Office(double, double, double, double, double, unsigned, unsigned);
    Office() : DevelopedLot(), offices(0) {};

    //Destructor
    virtual ~Office() {};

    //Methods
    double value() const override;
};

class Block {
private:
    std::vector<std::shared_ptr<Lot>>* lots;
public:
    Block();
    ~Block();
    void add_lot(Lot*);
    double total_value() const;
    void sort(bool);
};

class ReverseOrder {
public:
    bool operator()(const std::shared_ptr<Lot> l1, const std::shared_ptr<Lot> l2) {
        if (*l1 < *l2) {
            return false;
        }
        else {
            return true;
        }
    }
};

template<typename K, typename V>
class Map {
private:
    std::vector<std::shared_ptr<std::pair<K,V>>>* list;
public:
    Map() {
        this->list = new std::vector<std::shared_ptr<std::pair<K,V>>>;
    }
    void insert(const K& k, const V& v) {
        for (typename std::vector<std::shared_ptr<std::pair<K,V>>>::iterator it = this->list->begin(); it != this->list->end(); it++) {
            if ((*it)->first == k) {
                (*it)->second = v;
                return;
            }
        }
        std::shared_ptr<std::pair<K,V>> ptr = std::make_shared<std::pair<K,V>> (k,v);
        this->list->push_back(ptr);
    }
    std::optional<V> operator[](const K& k) {
        for (typename std::vector<std::shared_ptr<std::pair<K,V>>>::iterator it = this->list->begin(); it != this->list->end(); it++) {
            if ((*it)->first == k) {
                return (*it)->second;
            }
        }
        return {};
    }
};

#endif