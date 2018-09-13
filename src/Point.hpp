#ifndef POINT_HPP
#define POINT_HPP

#include "Geom.hpp"
#include "Line.hpp"
#include <cmath> //M_PI
#include <set>
class Line;
class Point : public Geom{
   private:
      double _x,_y;
   public:
      Point( double, double);
      ~Point();
      
      double getX() const;
      double getY() const;
      bool onIt(double, double, int approx=0);
      void drawOn(const Cairo::RefPtr<Cairo::Context>&);
      
      bool operator<(const Point&) const;
      bool operator>(const Point&) const;
      bool operator==(const Point&) const;
      bool operator!=(const Point&) const;
};

#endif
