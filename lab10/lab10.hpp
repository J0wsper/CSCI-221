#ifndef _LAB10_HPP_
#define _LAB10_HPP_

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
    unsigned length;
    Lot** arr;
public:
    Block();
    ~Block();
    void add_lot(Lot*);
    double total_value() const;
};

#endif