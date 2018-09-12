#include "MyArea.hpp"

MyArea::MyArea()
{
   add_events(Gdk::BUTTON_PRESS_MASK);
   _lineWidth=10.0;
   _plan = Gdk::Pixbuf::create_from_file("testPlan.jpeg");
}

MyArea::~MyArea()
{
}

void MyArea::setLineWidth(double lw){
   if(lw>0)
      _lineWidth=lw;
}

void MyArea::chgAction(actChoice act){
  clearSelected();
  for(auto it = _lines.begin();it!=_lines.end();++it){
        delete *it;
  }
  _lines.clear();
    _waiter.reset();
    _startPoint.reset();
   _curAct = act;
}

void MyArea::deleteSel(){
    std::cout<<"Delete activated"<<std::endl;
    if(!_selectedRoom.empty()){
        bool found;
        std::set<Room*>::iterator itR;
        while(!_selectedRoom.empty()){
            itR = _selectedRoom.begin();
            auto it = _rooms.begin();
            found = false;
            while(!found && it!=_rooms.end()){
                found = *it == *itR;
                ++it;
            }
            if(found){
                --it;
                _rooms.erase(it);
            }else{
                std::cerr<<"Deleting unsaved room"<<std::endl;
            }
            delete *itR;
            _selectedRoom.erase(itR);
        }
    }
    force_redraw();
}

//-------Protected


bool MyArea::on_button_press_event(GdkEventButton *event){
  // Check if the event is a left(1) button click.
    if( (event->type == GDK_BUTTON_PRESS) && (event->button == 1) )
    {
      
      if(_curAct==Select){
        Room* r = underPos(event->x,event->y);
        if(r!=NULL){
            _selectedRoom.insert(r);
            force_redraw();
            
        }else{
            clearSelected();
            std::cout<< "Found Nothing"<<std::endl;
        }        
        return true;
      }else{
         clearSelected();
         std::cout<<"Cleaned Selection"<<std::endl;
       }
      //if we are drawing a Line or Rectangle
        //If the line hasn't begu
       if(!_waiter){
         //save the first point
        _waiter.reset (new Point(event->x,event->y));
        if(_lines.empty()){
            _startPoint= _waiter;
        }
       }else{
         //get the second point
         //check if it is starter
         if(!_lines.empty() && _startPoint.get()->onIt(event->x,event->y,_lineWidth/2)){
                Line* l= new Line(_waiter,_startPoint);
                _lines.push_back(l);
                Room* res = new Room(_lines);
                _rooms.push_back(res);
                _lines.clear();
                _waiter.reset();
                _startPoint.reset();
                
                force_redraw();
                return true;
         }
         std::shared_ptr<Point> a (new Point(event->x, event->y));
         
         if(_curAct==dLine){
            //Save the new line
            Line* l= new Line(_waiter,a);
            _lines.push_back(l);
            _waiter= a;
         }else if(_curAct==dRect){
            drawRect(_waiter,a);
         }
         this->force_redraw();
         
       }
       return true;
    }
  return false;
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
   //help: https://developer.gnome.org/gtkmm-tutorial/stable/sec-cairo-drawing-lines.html.en
    Gdk::Cairo::set_source_pixbuf(cr,_plan,0,0);
    cr->paint();
    
  //Draw lines
   if(!_lines.empty()){
      cr->save();
        cr->set_line_width(_lineWidth);
      cr->set_source_rgb(0.8, 0.0, 0.0);
     std::vector<Line*>::iterator it;
     for(it=_lines.begin();it!=_lines.end();++it){
         (*it)->drawOn(cr);
     }
     cr->stroke();
     cr->restore();
     //
  }  
  
    if(!_rooms.empty()){
      cr->save();
        cr->set_line_width(_lineWidth);
      cr->set_source_rgba(0.8, 0.8, 0.0, 0.6);
     std::vector<Room*>::iterator itR;
     for(itR=_rooms.begin();itR!=_rooms.end();++itR){
         (*itR)->drawOn(cr);
     }
//      cr->fill_preserve();
          cr->stroke();
     cr->restore();
     //
  }
  if(!_selectedRoom.empty()){
      cr->save();
        cr->set_line_width(_lineWidth);
      cr->set_source_rgba(0.8, 0.0, 0.0, 0.6);
     std::set<Room*>::iterator itRS;
     for(itRS=_selectedRoom.begin();itRS!=_selectedRoom.end();++itRS){
         (*itRS)->drawOn(cr);
     }
     cr->fill_preserve();

     cr->restore();
     //
  }
  
    //Draw the end/start point
    cr->save();
    cr->set_source_rgb(1.0, 0.5, 0.0);
    if(_startPoint){
        _startPoint.get()->drawOn(cr);
    }
    cr->stroke();
    cr->restore();

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
Room* MyArea::underPos(double x, double y){
   Room* res = NULL;
   int approx = _lineWidth / 2;
   //Look on the points
   
   //find the first room under the pos
   std::vector<Room*>::iterator itR = _rooms.begin();
   bool found = false;
   while(!found && itR != _rooms.end()){
      found = (*itR)->onIt(x,y,approx);
      ++itR;
   }
   if(found){
      --itR;
      res = *itR;
   }
   return res;
}

void MyArea::drawRect(std::shared_ptr<Point> upL,std::shared_ptr<Point> downR){

   //Fine the two other points
    std::shared_ptr<Point> b (new Point(downR.get()->getX(), upL->getY()));
    std::shared_ptr<Point> c (new Point(upL.get()->getX(), downR->getY()));
   
   //Save the 4 lines
   Line* up= new Line(upL, b);
   Line* left= new Line(upL,c);
   Line* down= new Line(downR,c);
   Line* right= new Line(downR,b);
   _lines.push_back(up);
   _lines.push_back(left);
   _lines.push_back(down);
   _lines.push_back(right);   
   
   Room* res = new Room(_lines);
    _rooms.push_back(res);
    _lines.clear();
    _waiter.reset();
    _startPoint.reset();
}

void MyArea::clearSelected(){
   _selectedRoom.clear();
   this->force_redraw();
}

void MyArea::deleteLine(Line* l){
    //Faster to search if each line is selected?(other way around)
    std::vector<Line*>::reverse_iterator it = _lines.rbegin();
    delete *it;
    _lines.pop_back();
}






//mouse events: https://stackoverflow.com/questions/24661901/gtkmm-draw-line-with-mouse-events
