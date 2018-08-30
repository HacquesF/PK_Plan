#ifndef POINT_HPP
#define POINT_HPP

#include "Geom.hpp"

class Point : public Geom{
   private:
      int _x,_y;
   
   public:
      Point( int, int);
      ~Point();
      
      int getX() const;
      int getY() const;
      bool onIt(double, double, int approx=0);
      
      bool operator<(const Point&) const;
      bool operator>(const Point&) const;
      bool operator==(const Point&) const;
};

#endif
