#include "Point.hpp"

Point::Point(int a, int b) : _x(a), _y(b){
}

Point::~Point(){
}

int Point::getX() const{
   return _x;
}

int Point::getY() const{
   return _y;
}

bool Point::onIt(double x, double y, int approx){
   return (x+approx >= _x) && (x-approx <= _x) && (y+approx >= _y) && (y-approx <= _y);
}

void Point::addNeighb(Point* p){
    _neighb.insert(p);
}

void Point::removeNeighb(Point* p){
    _neighb.erase(p);
}

std::set<Point*> Point::getNeighb(){
    return _neighb;
}

bool Point::operator<(const Point& other) const{
   return (_x < other._x) || (_x == other._x && _y < other._y);
}
bool Point::operator>(const Point& other) const{
   return (_x > other._x) || (_x == other._x && _y > other._y);
}
bool Point::operator==(const Point& other) const{
   return (_x == other._x) && (_y == other._y);
}
bool Point::operator!=(const Point& other) const{
   return !(*this == other);
}

