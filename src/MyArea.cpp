#include "MyArea.hpp"
#include <cmath> //M_PI
#include <cairomm/context.h>
#include <iostream>

MyArea::MyArea()
{
   add_events(Gdk::BUTTON_PRESS_MASK);
   _lineWidth=10.0;
}

MyArea::~MyArea()
{
}

void MyArea::setLineWidth(double lw){
   if(lw>0)
      _lineWidth=lw;
}

bool MyArea::on_button_press_event(GdkEventButton *event){
   // Check if the event is a left(1) button click.
    if( (event->type == GDK_BUTTON_PRESS) && (event->button == 1) )
    {
       if(_waiter==NULL){
         _waiter = new Point(event->x, event->y);
       }else{
         Point* a= new Point(event->x, event->y);
         Line l(_waiter,a);
         _lines.push_back(l);
         _points.insert(*a);
         _points.insert(*_waiter);
         _waiter= NULL;
         this->force_redraw();
         return true;
       }
//       Point a(event->x, event->y);
//      _points.insert(a);
//      this->force_redraw();
//      return true;
    }
  return false;
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
   //help: https://developer.gnome.org/gtkmm-tutorial/stable/sec-cairo-drawing-lines.html.en

  cr->set_line_width(_lineWidth);
  
   if(!_lines.empty()){
      cr->save();
      cr->set_source_rgb(0.8, 0.0, 0.0);
     std::vector<Line>::iterator it;
     for(it=_lines.begin();it!=_lines.end();++it){
         cr->move_to(it->getA_X(),it->getA_Y());
         cr->line_to(it->getB_X(),it->getB_Y());
     }
     cr->stroke();
     cr->restore();
     //
  }
  
  if(!_points.empty()){
      cr->save();
     std::set<Point>::iterator itP;
     for(itP=_points.begin();itP!=_points.end();++itP){
         cr->arc(itP->getX(),itP->getY(),7.0,0.0,2.0*M_PI);
         cr->close_path(); 
     }
     cr->fill_preserve();
     cr->restore();
  }
  

  return true;
}

// force the redraw of the image
void MyArea::force_redraw()
{
  auto win = get_window();
  if (win)
  {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
}

//mouse events: https://stackoverflow.com/questions/24661901/gtkmm-draw-line-with-mouse-events
