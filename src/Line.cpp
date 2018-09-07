#include "Line.hpp"

Line::Line(Point* a, Point* b){
   int aX,bX,aY,bY;
   aX = a->getX();
   bX = b->getX();
   aY = a->getY();
   bY = b->getY();
   //Always put the highest point in _a
   if(aX < bX){
       _a = b;
       _b = a;
   }else{
        _a = a;
        _b = b;
   }
   if(aX != bX){
      _slope = (double)(bY - aY) / (double)(bX - aX);
      _bonus = aY - _slope*aX;
   }else{
      //Find a value
      _slope = 0;
      _bonus = 0;
   }
   _a->addNeighb(this);
   _b->addNeighb(this);
   
}

Line::~Line(){
   //I need to keep the objects
   _a->removeNeighb(this);
   _b->removeNeighb(this);
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

Point* Line::getA(){
    return _a;
}

Point* Line::getB(){
    return _b;
}
double Line::getSlope() const{
   return _slope;
}

double Line::getBonus() const{
   return _bonus;
}

bool Line::endsWith(Point* p){
    return (_a == p) || (_b == p);
}

Point* Line::getOtherEnd(Point* a){
    if(a == _a){
        return _b;
    }else if(a == _b){
        return _a;
    }
    return NULL;
}

bool Line::isVert(){
    return _a->getX() == _b->getX();
}

bool Line::validate(double x, double y, Direction dir, int approx){
    double hypY = x*_slope + _bonus;
    if(dir == dUnder){
        return hypY >= y-approx;
    }else if(dir == dUpper){
        return hypY <= y+approx;
    }
    return true;
}

void Line::drawOn(const Cairo::RefPtr<Cairo::Context>& cr){
    cr->move_to(getA_X(),getA_Y());
    cr->line_to(getB_X(),getB_Y());
}

bool Line::operator<(const Line& other) const{
   if(this == &other) return false;
   Point* minT, *maxT, *minO, *maxO;
   if(*_a < *_b){
      minT = _a;
      maxT = _b;
   }else{
      minT = _b;
      maxT = _a;
   }
   if(*other._a < *other._b){
      minO = other._a;
      maxO = other._b;
   }else{
      minO = other._b;
      maxO = other._a;
   }
   return *maxT < *maxO || ( (*maxT == *maxO) && (*minT < *minO));
}
bool Line::operator>(const Line& other) const{
   if(this == &other) return false;
   Point* minT, *maxT, *minO, *maxO;
   if(*_a < *_b){
      minT = _a;
      maxT = _b;
   }else{
      minT = _b;
      maxT = _a;
   }
   if(*other._a < *other._b){
      minO = other._a;
      maxO = other._b;
   }else{
      minO = other._b;
      maxO = other._a;
   }
   return *maxT > *maxO || ( (*maxT == *maxO) && (*minT>*minO));
}
bool Line::operator==(const Line& other) const{
   if(this == &other) return true;
   Point* minT, *maxT, *minO, *maxO;
   if(*_a < *_b){
      minT = _a;
      maxT = _b;
   }else{
      minT = _b;
      maxT = _a;
   }
   if(*other._a < *other._b){
      minO = other._a;
      maxO = other._b;
   }else{
      minO = other._b;
      maxO = other._a;
   }
   return *maxT == *maxO && *minT == *minO;
}
