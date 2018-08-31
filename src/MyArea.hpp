#ifndef MYAREA_HPP
#define MYAREA_HPP

#include <gtkmm.h>
#include <set>
#include "Point.hpp"
#include "Line.hpp"
#include "Geom.hpp"

enum actChoice { dRect, dLine, Select};
enum GeomPos { gLine, gPoint};

struct GeomSelector{
   Geom* geomSel;
   GeomPos type;
   GeomSelector(Geom* g, GeomPos t) : geomSel(g), type(t){}
};

struct LinkedGeomSelector{
   GeomSelector* elt;
   LinkedGeomSelector* up;
   LinkedGeomSelector* down;
};

class MyArea : public Gtk::DrawingArea{
   public:
     MyArea();
     virtual ~MyArea();
     void setLineWidth(double);
     void chgAction(actChoice);

   protected:
     //Override default signal handler:
     bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
     bool on_button_press_event(GdkEventButton * event);
     void force_redraw();
     
  private:
      std::vector<Point*> _points;
      std::vector<Line> _lines;
      Point* _waiter;
      double _lineWidth;
      actChoice _curAct;
      GeomSelector* _lastTouched;
      LinkedGeomSelector* _selected;
      
      //Return the object under some position including the approx
      GeomSelector* underPos(double,double);
      //Add a rectangle to draw between both points
      void drawRect(Point*,Point*);
};

#endif
