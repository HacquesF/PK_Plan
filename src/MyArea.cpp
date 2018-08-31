#include "MyArea.hpp"
#include <cmath> //M_PI
#include <cairomm/context.h>
#include <iostream>

MyArea::MyArea()
{
   add_events(Gdk::BUTTON_PRESS_MASK);
   _lineWidth=10.0;
   _waiter= NULL;
   _selected = NULL;
}

MyArea::~MyArea()
{
}

void MyArea::setLineWidth(double lw){
   if(lw>0)
      _lineWidth=lw;
}

void MyArea::chgAction(actChoice act){
   _curAct = act;
}

//-------Protected
bool MyArea::on_button_press_event(GdkEventButton *event){
   // Check if the event is a left(1) button click.
    if( (event->type == GDK_BUTTON_PRESS) && (event->button == 1) )
    {
       if(_curAct==Select){
         _selected = underPos(event->x, event->y);
         if(_selected != NULL){
            std::cout<< "Found smthing : "<< _selected <<std::endl;
            _selected= NULL;
         }else{
         
         std::cout<< "Found Nothing" <<std::endl;
         
         }return true;
       }
      //if we are drawing a Line or Rectangle
       if(_waiter==NULL){
         //save the first point
         _waiter = new Point(event->x, event->y);
         std::cout << _waiter <<std::endl;
       }else{
         //get the second point
         Point* a= new Point(event->x, event->y);
         
         if(_curAct==dLine){
            //Seve the new line
            Line l(_waiter,a);
            _lines.push_back(l);
            _points.insert(a);
            _points.insert(_waiter);
         }
         else if(_curAct==dRect){
            drawRect(_waiter,a);
         }
         
         _waiter= NULL;
         this->force_redraw();  
       }
       return true;
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
     std::set<Point*>::iterator itP;
     for(itP=_points.begin();itP!=_points.end();++itP){
         cr->arc((*itP)->getX(),(*itP)->getY(),7.0,0.0,2.0*M_PI);
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

//----------------Private
const Geom* MyArea::underPos(double x, double y){
   const Geom* res = NULL;
   int approx = _lineWidth / 2;
   //Look on the points
   
   //find all the points around the position
//   std::set<Point*>::iterator itlow,itup;
//   Point low(x-approx, y-approx);
//   Point up(x+approx, y+approx);
//   std::cout<<x<<" : "<<y<<" :: "<<approx<<std::endl;
   //drawRect(&up,&low);

   

//   itlow = _points.lower_bound(&low);
//   itup = _points.upper_bound(&up);
//   if(*itup != *itlow && (*itlow)->getY()>=y-approx && (*itlow)->getY()<=y+approx){
//      res = *itlow;
//    std::cout<<"Point : "<<res<<";"<<itlow->getX()<<" : "<<itlow->getY()<<";"<<itup->getX()<<" : "<<itup->getY()<<std::endl;
//   }
//   std::set<Point> allFound (itlow,itup);
//   if(!allFound.empty()) res = &(*allFound.begin());
   
   //Need to add the 2 points
//   //Didn't found points, look for lines
//   if(res == NULL){
//      std::vector<Line>::iterator it=_lines.begin();
//      bool found= false;
//      while(!found && it != _lines.end()){
//          it->onIt(x,y,approx);
//         ++it;
//      }
//      if(found){
//         --it;
//         res = &(*it);
//         std::cout<<"Line: "<<res<<std::endl;
//      }
//   }
   return res;
   //Finding something faster/lighter could be good
}

void MyArea::drawRect(Point* upL,Point* downR){

   //Fine the two other points
   Point* b = new Point(downR->getX(), upL->getY());
   Point* c = new Point(upL->getX(), downR->getY());
   
   //Save the 4 lines
   Line up(upL, b);
   Line left(upL,c);
   Line down(downR,c);
   Line right(downR,b);
   _lines.push_back(up);
   _lines.push_back(left);
   _lines.push_back(right);
   _lines.push_back(down);
   
   //Save his created points
   _points.insert(b);
   _points.insert(c);
   _points.insert(downR);
   _points.insert(upL);
}















//mouse events: https://stackoverflow.com/questions/24661901/gtkmm-draw-line-with-mouse-events
