#include "Line.hpp"

Line::Line(std::shared_ptr<Point> a, std::shared_ptr<Point> b) : _a(a), _b(b){
   int aX,bX,aY,bY;
   aX = a->getX();
   bX = b->getX();
   aY = a->getY();
   bY = b->getY();
   //Always put the highest point in _a
   if(aX < bX){
       _a.swap(_b);
   }
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
   return _a.get()->getX();
}

int Line::getA_Y(){
   return _a.get()->getY();
}

int Line::getB_X(){
   return _b.get()->getX();
}

int Line::getB_Y(){
   return _b.get()->getY();
}

Point* Line::getA(){
    return _a.get();
}

Point* Line::getB(){
    return _b.get();
}
double Line::getSlope() const{
   return _slope;
}

double Line::getBonus() const{
   return _bonus;
}

bool Line::endsWith(Point* p){
    return (_a.get() == p) || (_b.get() == p);
}

std::shared_ptr<Point> Line::endsWith(double x,double y,int approx){
    if(_a.get()->onIt(x,y,approx)){
        return _a;
    }else if(_b.get()->onIt(x,y,approx)){
        return _b;
    }
    return NULL;
}

Point* Line::getOtherEnd(Point* a){
    if(a == _a.get()){
        return _b.get();
    }else if(a == _b.get()){
        return _a.get();
    }
    return NULL;
}

bool Line::isVert(){
    return _a.get()->getX() == _b.get()->getX();
}

bool Line::validate(double x, double y, Direction dir, int approx){
    if(x>getA_X() || x < getB_X()) return true;
    
    double hypY = x*_slope + _bonus;
    //Y grow when going down
    if(dir == dUnder){
        return hypY <= y+approx;
    }else if(dir == dUpper){
        return hypY >= y-approx;
    }
    return true;
}

void Line::drawOn(const Cairo::RefPtr<Cairo::Context>& cr){
    cr->move_to(getA_X(),getA_Y());
    cr->line_to(getB_X(),getB_Y());
}

Point* Line::drawFrom(Point* p,const Cairo::RefPtr<Cairo::Context>& cr){
    Point* dest = getOtherEnd(p);
    if(dest != NULL) cr->line_to(dest->getX(), dest->getY());
    return dest;
}

bool Line::operator<(const Line& other) const{
   if(this == &other) return false;
   Point* minT, *maxT, *minO, *maxO;
   if(*_a.get() < *_b.get()){
      minT = _a.get();
      maxT = _b.get();
   }else{
      minT = _b.get();
      maxT = _a.get();
   }
   if(*other._a.get() < *other._b.get()){
      minO = other._a.get();
      maxO = other._b.get();
   }else{
      minO = other._b.get();
      maxO = other._a.get();
   }
   return *maxT < *maxO || ( (*maxT == *maxO) && (*minT < *minO));
}
bool Line::operator>(const Line& other) const{
   if(this == &other) return false;
   Point* minT, *maxT, *minO, *maxO;
   if(*_a.get() < *_b.get()){
      minT = _a.get();
      maxT = _b.get();
   }else{
      minT = _b.get();
      maxT = _a.get();
   }
   if(*other._a.get() < *other._b.get()){
      minO = other._a.get();
      maxO = other._b.get();
   }else{
      minO = other._b.get();
      maxO = other._a.get();
   }
   return *maxT > *maxO || ( (*maxT == *maxO) && (*minT>*minO));
}
bool Line::operator==(const Line& other) const{
   if(this == &other) return true;
   Point* minT, *maxT, *minO, *maxO;
   if(*_a.get() < *_b.get()){
      minT = _a.get();
      maxT = _b.get();
   }else{
      minT = _b.get();
      maxT = _a.get();
   }
   if(*other._a.get() < *other._b.get()){
      minO = other._a.get();
      maxO = other._b.get();
   }else{
      minO = other._b.get();
      maxO = other._a.get();
   }
   return *maxT == *maxO && *minT == *minO;
}
