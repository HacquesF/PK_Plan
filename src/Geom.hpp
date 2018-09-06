#ifndef GEOM_HPP
#define GEOM_HPP

enum Direction {dUnder, dUpper, dNone };

class Geom{
public:
      virtual ~Geom(){}
      virtual bool onIt(double, double, int) = 0;
};

#endif
