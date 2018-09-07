#ifndef MYAREA_HPP
#define MYAREA_HPP

#include <gtkmm.h>
#include <set>
#include <cairomm/context.h>
#include <iostream>
#include "Point.hpp"
#include "Line.hpp"
#include "Room.hpp"
#include "Geom.hpp"

enum actChoice { dRect, dLine, Select};
enum GeomPos { gLine, gPoint};

struct GeomSelector{
   Geom* geomSel;
   GeomPos type;
   GeomSelector(Geom* g, GeomPos t) : geomSel(g), type(t){}
};

struct LineSelector{
   Line* lineSel;
   LineSelector(Line* l) : lineSel(l){}
   bool operator>(const LineSelector& other) const{return (*lineSel) > (*other.lineSel); }
   bool operator<(const LineSelector& other) const{return (*lineSel) > (*other.lineSel); }
};

struct PointSelector{
   Point* pointSel;
   PointSelector(Point* p) : pointSel(p){}
   bool operator>(const PointSelector& other) const{return (*pointSel) > (*other.pointSel); }
   bool operator<(const PointSelector& other) const{return (*pointSel) > (*other.pointSel); }
};

class MyArea : public Gtk::DrawingArea{
   public:
     MyArea();
     virtual ~MyArea();
     void setLineWidth(double);
     void chgAction(actChoice);
     void deleteSel();

   protected:
     //Override default signal handler:
     bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
     bool on_button_press_event(GdkEventButton * event);
     void force_redraw();
     
  private:
      std::vector<Point*> _points;
      std::vector<Line*> _lines;
      std::vector<Room*> _rooms;
      Point* _waiter;
      double _lineWidth;
      actChoice _curAct;
      GeomSelector* _lastTouched;
      std::set<PointSelector> _selectedPoint;
      std::set<LineSelector> _selectedLine;
      
      //Return the object under some position including the approx
      GeomSelector* underPos(double,double);
      //Add a rectangle to draw between both points
      void drawRect(Point*,Point*);
      //.
      void clearSelected();
      //Removing points and lines
      void deleteLine(Line*);
      void deleteLinesWith(Point*);
      void deletePoint(Point*);
      //Add the point to _points if not already in, return a pointer to it
      Point* addPoint(double,double);
      //Make rooms with cycle it finds containing Point
      std::set<Point*> cyclePoints(Point*,Point*, std::set<Point*> checked = {}, std::vector<Line*> parents = {});
};

#endif
