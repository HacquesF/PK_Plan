#ifndef POINT_HPP
#define POINT_HPP

#include "Geom.hpp"
#include <set>

class Point : public Geom{
   private:
      int _x,_y;
        std::set<Line*> _neighb;
   public:
      Point( int, int);
      ~Point();
      
      int getX() const;
      int getY() const;
      bool onIt(double, double, int approx=0);
      void addNeighb(Line*);
      void removeNeighb(Line*);
      std::set<Line*> getNeighb();
      
      bool operator<(const Point&) const;
      bool operator>(const Point&) const;
      bool operator==(const Point&) const;
      bool operator!=(const Point&) const;
};

#endif
