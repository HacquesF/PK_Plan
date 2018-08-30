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

