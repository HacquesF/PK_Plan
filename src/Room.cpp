#include "Room.hpp"
//TODO:Remove copy of i is B... from vertical and normal
Room::Room(std::vector<Line*> lines){
    //Find the direction around the vector
    //  Find the lowest Y
    int minY = lines[0]->getA_Y();
    unsigned int maxL=0;
    for(unsigned int i = 0; i < lines.size();++i){
        if(lines[i]->getA_Y() < minY){
            maxL = i;
            minY = lines[i]->getA_Y();
        }
    }
    //For the highest point, the direction starts under or None
    if(lines[maxL]->isVert()){
        _sides.emplace_back(lines[maxL],dNone);
    }else{
       _sides.emplace_back(lines[maxL],dUnder); 
    }
    //Need lastY for center and area with vertical lines to reconise i and i+1
    double lastY = lines[maxL]->getA_Y();
    //Save the last A_X to understand the direction
    double lastX = lines[maxL]->getA_X();
    bool clockWise = true;
    
    //Center and Area from: https://en.wikipedia.org/wiki/Polygon#Area_and_centroid
    double repeatArea;
    
    //We need to cycle through the vector until we get back to the starting line
    unsigned int curr = (maxL+1 == lines.size())? 0: maxL+1;
    if(!(lines[curr]->getA_X()==lastX || lines[curr]->getB_X()==lastX)){
        lastX = lines[maxL]->getB_X();
        lastY = lines[maxL]->getB_Y();
        clockWise = false;
        
        //i is A, i+1 is B
        repeatArea = lines[maxL]->getA_X() * lines[maxL]->getB_Y() - lines[maxL]->getB_X() * lines[maxL]->getA_Y();
    }else{
        //i is B, i+1 is A
        repeatArea = lines[maxL]->getB_X() * lines[maxL]->getA_Y() - lines[maxL]->getA_X() * lines[maxL]->getB_Y();
    }
    _area = repeatArea;
    _centerX = (lines[maxL]->getB_X() + lines[maxL]->getA_X()) * repeatArea;
    _centerY = (lines[maxL]->getB_Y() + lines[maxL]->getA_Y()) * repeatArea;
    
    while(curr != maxL){
        //If the current line is verticals
        if(lines[curr]->isVert()){
            //Had a line without direction
            _sides.emplace_back(lines[curr], dNone);
            if(lastY == lines[curr]->getB_Y()){
                //i is B, i+1 is A
                repeatArea = lastX * (lines[curr]->getA_Y() - lines[curr]->getB_Y());
                _area += repeatArea;
                _centerX += lastX * 2 * repeatArea;
                _centerY += (lines[curr]->getB_Y() + lines[curr]->getA_Y()) * repeatArea;
                
                lastY = lines[curr]->getA_Y();
            }else if(lastY == lines[curr]->getA_Y()){
                //i is A, i+1 is B
                repeatArea = lastX * (lines[curr]->getB_Y() - lines[curr]->getA_Y());
                _area += repeatArea;
                _centerX += lastX * 2 * repeatArea;
                _centerY += (lines[curr]->getB_Y() + lines[curr]->getA_Y()) * repeatArea;
                 
                 lastY = lines[curr]->getB_Y();
            }else{
                //The last Y doesn't match any ends of the current line
                //There is a problem with the lines given
                std::cerr<<"Bad vector for rooms, vertical lines don't follow :"<<lastY<<" != ( "<<lines[curr]->getA_Y()<<"; "<<lines[curr]->getB_Y()<<")"<< std::endl;
                return;
            }
        }else{
            //We look for the direction of the line
            //  If we are going forward
            if(lastX == lines[curr]->getB_X()){
                if(clockWise){
                    _sides.emplace_back(lines[curr], dUnder);
                }else{
                    _sides.emplace_back(lines[curr], dUpper);
                }
                lastX = lines[curr]->getA_X();
                lastY = lines[curr]->getA_Y();
                //i is B, i+1 is A
                repeatArea = lines[curr]->getB_X() * lines[curr]->getA_Y() - lines[curr]->getA_X() * lines[curr]->getB_Y();
                _area += repeatArea;
                _centerX += (lines[curr]->getB_X() + lines[curr]->getA_X()) * repeatArea;
                _centerY += (lines[curr]->getB_Y() + lines[curr]->getA_Y()) * repeatArea;
            //If we are going forward
            }else if (lastX == lines[curr]->getA_X()){
                if(clockWise){
                    _sides.emplace_back(lines[curr], dUpper);
                }else{
                    _sides.emplace_back(lines[curr], dUnder);
                }
                lastX = lines[curr]->getB_X();
                lastY = lines[curr]->getB_Y();
                //i is A, i+1 is B
                repeatArea = lines[curr]->getA_X() * lines[curr]->getB_Y() - lines[curr]->getB_X() * lines[curr]->getA_Y();
                _area += repeatArea;
                _centerX += (lines[curr]->getB_X() + lines[curr]->getA_X()) * repeatArea;
                _centerY += (lines[curr]->getB_Y() + lines[curr]->getA_Y()) * repeatArea;
            }else{
                //The last X doesn't match any ends of the current line
                //There is a problem with the lines given
                std::cerr<<"Bad vector for rooms, lines don't follow :"<<lastX<<" != ( "<<lines[curr]->getA_X()<<"; "<<lines[curr]->getB_X()<<")"<< std::endl;
                return;
            }
        }
        //Going to the next line while taking care of the cycling
        curr = (curr+1 == lines.size()) ? 0 : curr+1;
    }
    _area = _area / 2.0;
    _centerX = _centerX / (6.0*_area);
    _centerY = _centerY / (6.0*_area);
    _area = _area < 0 ? -_area : _area;
    //------------Debug-------
                for(auto it = _sides.begin();it!=_sides.end();++it){
                    std::cout<<"( "<<it->lin->getA_X()<<", "<<it->lin->getA_Y()<<")"<<" : "<<"( "<<it->lin->getB_X()<<", "<<it->lin->getB_Y()<<")"<<" "<<it->dir<<std::endl;
                }
                std::cout<<"("<<_centerX<<", "<<_centerY<<")" << " "<<_area<<std::endl;
                std::cout<<"----------"<<std::endl;
}

Room::~Room(){
    for(auto it = _sides.begin();it!=_sides.end();++it){
        delete it->lin;
    }
}

bool Room::onIt(double x, double y, int approx){
    if(_sides.empty()){
        return false;
    }
     int maxX = _sides[0].lin->getA_X();
     int minX = _sides[0].lin->getB_X();
    bool vali = true;
    unsigned int i =0;
    while(vali && i < _sides.size()){
        if(maxX < _sides[i].lin->getA_X()){
            maxX = _sides[i].lin->getA_X();
        }
        if(minX > _sides[i].lin->getB_X()){
            minX = _sides[i].lin->getB_X();
        }
        if(_sides[i].dir != dNone){
            vali = _sides[i].lin->validate(x,y,_sides[i].dir,approx);
        }
        ++i;
    }
    return vali && x <= (maxX+approx) && x >= (minX-approx);
}

//TODO: avoid copy for
void Room::drawOn(const Cairo::RefPtr<Cairo::Context>& cr){
    Point* curr = _sides[0].lin->getB();
    _sides[0].lin->drawOn(cr);
    if(_sides[1].lin->endsWith(curr)){
        std::vector<DirLine>::iterator it = _sides.begin() +1;
        std::vector<DirLine>::iterator itEnd = _sides.end();
        for(;it != itEnd; ++it){
            curr = it->lin->drawFrom(curr,cr);
            if(curr == NULL){
                std::cerr<<"Lines don't line up"<<std::endl;
                return;
            }
        }
        
    }else if(_sides[_sides.size()-1].lin->endsWith(curr)){
        std::vector<DirLine>::reverse_iterator it = _sides.rbegin();
        std::vector<DirLine>::reverse_iterator itEnd = _sides.rend()-1;
        for(;it != itEnd; ++it){
            curr = it->lin->drawFrom(curr,cr);
            if(curr == NULL){
                std::cerr<<"Lines don't line up"<<std::endl;
                return;
            }
        }
    }else{
        std::cerr<<"First line goes nowhere"<<std::endl;
        return;
    }
    
    //Draw center (debug)
    cr->arc(_centerX,_centerY,7.0,0.0,2.0*M_PI);    
}
