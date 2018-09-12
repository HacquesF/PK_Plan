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

void Point::drawOn(const Cairo::RefPtr<Cairo::Context>& cr){
    cr->move_to(getX(),getY());
    cr->arc(getX(),getY(),7.0,0.0,2.0*M_PI);
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

