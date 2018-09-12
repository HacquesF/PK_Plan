#ifndef LINE_H
#define LINE_H

#include "Point.hpp"
#include "Geom.hpp"//Direction
#include <algorithm> //min/max 
class Point;
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
      // =/
      Point* getA();
      Point* getB();
      double getSlope() const;
      double getBonus() const;
      bool endsWith(Point*);
      Point* endsWith(double,double,int approx = 0);
      //Find how to protect
      //NULL if line doesn't end with point
      Point* getOtherEnd(Point*);
      bool isVert();
      //Return true if dNone as direction
      bool validate(double,double,Direction,int approx=0);
      void drawOn(const Cairo::RefPtr<Cairo::Context>&);
      Point* drawFrom(Point*,const Cairo::RefPtr<Cairo::Context>&);
      
      bool operator<(const Line&) const;
      bool operator>(const Line&) const;
      bool operator==(const Line&) const;

};

#endif
