#include "MyArea.hpp"

MyArea::MyArea()
{
   add_events(Gdk::BUTTON_PRESS_MASK);
   _lineWidth=10.0;
   _waiter= NULL;
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
   _curAct = act;
}

void MyArea::deleteSel(){
    std::cout<<"Delete activated"<<std::endl;
    if(!_selectedLine.empty()){
        std::set<LineSelector>::iterator itL;
        while(!_selectedLine.empty()){
            itL = _selectedLine.begin();
            deleteLine(itL->lineSel);
            _selectedLine.erase(itL);
        }
    }
    if(!_selectedPoint.empty()){
        std::set<PointSelector>::iterator itP;
        while(!_selectedPoint.empty()){
            itP = _selectedPoint.begin();
            deletePoint(itP->pointSel);
            _selectedPoint.erase(itP);
        }
    }
    std::cout<<"Points"<<std::endl;
    for(auto it= _points.begin();it!=_points.end();++it){
        std::cout<<*it<<std::endl;
    }/*
    std::cout<<"Lines"<<std::endl;
    for(auto it= _lines.begin();it!=_lines.end();++it){
        std::cout<<*it<<std::endl;
    }*/
    force_redraw();
}

//-------Protected
bool MyArea::on_button_press_event(GdkEventButton *event){
  // Check if the event is a left(1) button click.
    if( (event->type == GDK_BUTTON_PRESS) && (event->button == 1) )
    {
      
      if(_curAct==Select){
        _lastTouched = underPos(event->x, event->y);
        if(_lastTouched != NULL){
            switch(_lastTouched->type){
              case gPoint :
                _selectedPoint.insert((Point*)_lastTouched->geomSel);
                break;
              case gLine :
                _selectedLine.insert((Line*)_lastTouched->geomSel);
                break;
              default :
                  std::cout<<"Can't select that" <<std::endl;
                  break;
            }
            _lastTouched = NULL;
            
            std::set<LineSelector>::iterator itL;
            std::cout<<"Lines"<<std::endl;
              for(itL = _selectedLine.begin(); itL != _selectedLine.end(); ++itL){
                std::cout<<itL->lineSel<<std::endl;
            }
            std::set<PointSelector>::iterator itP;
            std::cout<<"Points"<<std::endl;
              for(itP = _selectedPoint.begin(); itP != _selectedPoint.end(); ++itP){
                std::cout<<itP->pointSel<<std::endl;
            }
            
            this->force_redraw();
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
       if(_waiter==NULL){
         //save the first point
        _waiter = addPoint(event->x,event->y);
       }else{
         //get the second point
         Point* a;
         a = addPoint(event->x, event->y);
         
         if(_curAct==dLine){
            //Seve the new line
            Line* l= new Line(_waiter,a);
            _lines.push_back(l);
         }
         else if(_curAct==dRect){
            drawRect(_waiter,a);
         }
         
         _waiter= NULL;
         this->force_redraw();
         
         //Debug, show neighb of points
//          std::set<Point*> tmpN;
//          for(auto itP= _points.begin(); itP != _points.end(); ++itP){
//              tmpN = (*itP)->getNeighb();
//              std::cout<<*itP<<" = ";
//             for(auto itN=tmpN.begin(); itN!= tmpN.end();++itN){
//                 std::cout<<*itN<<" : ";
//             }
//             std::cout<<std::endl;
//          }
         
       }
       return true;
    }
  return false;
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
   //help: https://developer.gnome.org/gtkmm-tutorial/stable/sec-cairo-drawing-lines.html.en

  cr->set_line_width(_lineWidth);
  //Draw lines
   if(!_lines.empty()){
      cr->save();
      cr->set_source_rgb(0.8, 0.0, 0.0);
     std::vector<Line*>::iterator it;
     for(it=_lines.begin();it!=_lines.end();++it){
         cr->move_to((*it)->getA_X(),(*it)->getA_Y());
         cr->line_to((*it)->getB_X(),(*it)->getB_Y());
     }
     cr->stroke();
     cr->restore();
     //
  }
  
  //Highlight selected lines
  if(!_selectedLine.empty()){
    cr->save();
    cr->set_source_rgba(0.0, 0.8, 0.0, 0.6);
    std::set<LineSelector>::iterator itSL;
    for(itSL=_selectedLine.begin();itSL!=_selectedLine.end();++itSL){
      cr->move_to(itSL->lineSel->getA_X(),itSL->lineSel->getA_Y());
      cr->line_to(itSL->lineSel->getB_X(),itSL->lineSel->getB_Y());
    }
    cr->stroke();
    cr->restore();
  }
  
  //Draw points
  if(!_points.empty()){
      //std::cout<<_points.size()<<std::endl;
     cr->save();
     cr->set_line_width(_lineWidth/2);
     std::vector<Point*>::iterator itP;
     for(itP=_points.begin();itP!=_points.end();++itP){
          cr->move_to((*itP)->getX(),(*itP)->getY());
         cr->arc((*itP)->getX(),(*itP)->getY(),7.0,0.0,2.0*M_PI);
     }
     cr->set_source_rgb(0.0, 0.0, 0.0);
     cr->stroke();
     cr->restore();
  }
  
  //Highlight selected points
  if(!_selectedPoint.empty()){
    cr->save();
    std::set<PointSelector>::iterator itSP;
    for(itSP=_selectedPoint.begin();itSP!=_selectedPoint.end();++itSP){
      cr->move_to(itSP->pointSel->getX(),itSP->pointSel->getY());
      cr->arc(itSP->pointSel->getX(),itSP->pointSel->getY(),7.0,0.0,2.0*M_PI);
    }
    cr->set_source_rgba(0.0, 0.8, 0.0, 0.6);
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
GeomSelector* MyArea::underPos(double x, double y){
   GeomSelector* res = NULL;
   int approx = _lineWidth / 2;
   //Look on the points
   
   //find all the points around the position
   std::vector<Point*>::iterator itP = _points.begin();
   bool found = false;
   while(!found && itP != _points.end()){
      found = (*itP)->onIt(x,y,approx);
      ++itP;
   }
   if(found){
      --itP;
      res = new GeomSelector(*itP,gPoint);
   }
   
   //Didn't found points, look for lines
   if(res == NULL){
      std::vector<Line*>::iterator it=_lines.begin();
      while(!found && it != _lines.end()){
         found = (*it)->onIt(x,y,approx);
         ++it;
      }
      if(found){
         --it;
         res = new GeomSelector(*it,gLine);
      }
   }
   return res;
   //Finding something faster/lighter could be good
}

void MyArea::drawRect(Point* upL,Point* downR){

   //Fine the two other points
    Point* b = addPoint(downR->getX(), upL->getY());
    Point* c = addPoint(upL->getX(), downR->getY());
   
   //Save the 4 lines
   Line* up= new Line(upL, b);
   Line* left= new Line(upL,c);
   Line* down= new Line(downR,c);
   Line* right= new Line(downR,b);
   _lines.push_back(up);
   _lines.push_back(left);
   _lines.push_back(right);
   _lines.push_back(down);
}

void MyArea::clearSelected(){
   _selectedLine.clear();
   _selectedPoint.clear();
   this->force_redraw();
}

void MyArea::deleteLine(Line* l){
    //Faster to search if each line is selected?(other way around)
    std::vector<Line*>::iterator it = _lines.begin();
    while((*it)!=l && it!=_lines.end()){
        ++it;
    }
    delete *it;
    _lines.erase(it);
}

void MyArea::deleteLinesWith(Point* p){
    Line* tmp;
    std::vector<Line*>::iterator it = _lines.begin();
    while(it!=_lines.end()){
        tmp = *it;
        if(tmp->endsWith(p)){
             delete tmp;
             _lines.erase(it);
             --it;
        }
        ++it;
    }

}

void MyArea::deletePoint(Point* p){
    std::vector<Point*>::iterator itP = _points.begin();
    while((*itP)!=p && itP!=_points.end()){
        ++itP;
    }
    deleteLinesWith(*itP);
    delete *itP;
    _points.erase(itP);
}

Point* MyArea::addPoint(double x, double y){
    Point* res;
    GeomSelector* uP;
    uP = underPos(x,y);
    if(uP != NULL && uP->type == gPoint){
        res = (Point*)uP->geomSel;
    }else{
        res = new Point(x,y);
        _points.push_back(res);
    }
    delete uP;
    return res;
}










//mouse events: https://stackoverflow.com/questions/24661901/gtkmm-draw-line-with-mouse-events
