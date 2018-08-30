#ifndef MYAREA_HPP
#define MYAREA_HPP

#include <gtkmm.h>
#include <set>
#include "Point.hpp"
#include "Line.hpp"
class MyArea : public Gtk::DrawingArea{
   public:
     MyArea();
     virtual ~MyArea();
     void setLineWidth(double);

   protected:
     //Override default signal handler:
     bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
     bool on_button_press_event(GdkEventButton * event);
     void force_redraw();
     
  private:
      std::set<Point> _points;
      std::vector<Line> _lines;
      Point* _waiter;
      double _lineWidth;
};

#endif
