#ifndef GEOM_HPP
#define GEOM_HPP

#include <cairomm/context.h>

enum Direction {dUnder, dUpper, dNone };

class Geom{
public:
      virtual ~Geom(){}
      virtual bool onIt(double, double, int) = 0;
      virtual void drawOn(const Cairo::RefPtr<Cairo::Context>&) = 0;
};

#endif
