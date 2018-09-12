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

class MyArea : public Gtk::DrawingArea{
   public:
     MyArea();
     virtual ~MyArea();
     void setLineWidth(double);
     void chgAction(actChoice);
     void deleteSel();
     void loadPlan(std::string);

   protected:
     //Override default signal handler:
     bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
     bool on_button_press_event(GdkEventButton * event);
     void force_redraw();
     
  private:
      std::vector<Line*> _lines;
      std::vector<Room*> _rooms;
      std::shared_ptr<Point> _waiter;
      std::shared_ptr<Point> _startPoint;
      double _lineWidth;
      actChoice _curAct;
      std::set<Room*> _selectedRoom;
      Glib::RefPtr<Gdk::Pixbuf> _plan;
      
      //Return the object under some position including the approx
      Room* underPos(double,double);
      //Add a rectangle to draw between both points
      void drawRect(std::shared_ptr<Point>,std::shared_ptr<Point>);
      //.
      void clearSelected();
      //Removing points and lines
      //TODO: transform in a go back 1 line (remove the last line from _lines
      void deleteLine(Line*);
};

#endif
