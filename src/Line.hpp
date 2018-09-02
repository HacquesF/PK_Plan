#ifndef LINE_H
#define LINE_H

#include "Point.hpp"
#include "Geom.hpp"
#include <algorithm> //min/max 
class Line : public Geom{
   private:
      Point* _a;
      Point* _b;
      double _slope, _bonus;
   public:
      Line(Point*,Point*);
      ~Line();
      bool onIt(double,double,int approx=0);
      int getA_X();
      int getA_Y();
      int getB_X();
      int getB_Y();
      double getSlope() const;
      double getBonus() const;
      bool endsWith(Point*);
      
      bool operator<(const Line&) const;
      bool operator>(const Line&) const;
      bool operator==(const Line&) const;

};

#endif
