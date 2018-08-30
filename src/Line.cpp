#include "Line.hpp"

Line::Line(Point* a, Point* b): _a(a),_b(b){
   int aX,bX,aY,bY;
   aX = a->getX();
   bX = b->getX();
   aY = a->getY();
   bY = b->getY();
   if(aX != bX){
      _slope = (double)(bY - aY) / (double)(bX - aX);
      _bonus = aY - _slope*aX;
   }else{
      //Find a value
      _slope = 0;
      _bonus = 0;
   }
   
   
}

Line::~Line(){
   //I need to keep the object
}

bool Line::onIt(double x, double y, int approx){
   int aX,bX,aY,bY;
   aX = getA_X();
   bX = getB_X();
   aY = getA_Y();
   bY = getB_Y();
   //Inside the points?
   if(! ((std::min(aX,bX) <= x+approx) && (std::max(aX,bX) >= x-approx) && (std::min(aY,bY) <= y+approx) && (std::max(aY,bY) >= y-approx) )){
      return false;
   }
   //Is the line vertical
   else if (aX == bX){
      return (aX > x-approx) && (aX < x+approx);
   }
   else{
      //default line
      return (_slope*x+_bonus-y) >= -approx && (_slope*x+_bonus-y) <= approx;
   }
}

int Line::getA_X(){
   return _a->getX();
}

int Line::getA_Y(){
   return _a->getY();
}

int Line::getB_X(){
   return _b->getX();
}

int Line::getB_Y(){
   return _b->getY();
}

double Line::getSlope() const{
   return _slope;
}

double Line::getBonus() const{
   return _bonus;
}

