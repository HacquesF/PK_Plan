#include "Room.hpp"

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
    //Save the last A_X to understand the direction
    int lastAX = lines[maxL]->getA_X();
    //For the highest point, the direction starts under or None
    if(lines[maxL]->isVert()){
        _sides.emplace_back(lines[maxL],dNone);
    }else{
       _sides.emplace_back(lines[maxL],dUnder); 
    }
    //We need to cycle through the vector until we get back to the starting line
    unsigned int curr = (maxL+1 == lines.size())? 0: maxL+1;
    bool clockWise = true;
    if(!(lines[curr]->getA_X()==lastAX || lines[curr]->getB_X()==lastAX)){
        lastAX = lines[maxL]->getB_X();
        clockWise = false;
    }
    while(curr != maxL){
        //If the current line is vertical
        if(lines[curr]->isVert()){
            //Had a line without direction
            _sides.emplace_back(lines[curr], dNone);
        }else{
            //We look for the direction of the line
            //  If we are going forward
            if(lastAX == lines[curr]->getB_X()){
                if(clockWise){
                    _sides.emplace_back(lines[curr], dUnder);
                }else{
                    _sides.emplace_back(lines[curr], dUpper);
                }
                lastAX = lines[curr]->getA_X();
            //If we are going forward
            }else if (lastAX == lines[curr]->getA_X()){
                if(clockWise){
                    _sides.emplace_back(lines[curr], dUpper);
                }else{
                    _sides.emplace_back(lines[curr], dUnder);
                }
                lastAX = lines[curr]->getB_X();
            }else{
                //The last X doesn't match any ends of the current line
                //There is a problem with the lines given
                std::cerr<<"Bad vector for rooms, lines don't follow :"<<lastAX<<" != ( "<<lines[curr]->getA_X()<<"; "<<lines[curr]->getB_X()<<")"<< std::endl;
                return;
            }
        }
        //Going to the next line while taking care of the cycling
        curr = (curr+1 == lines.size()) ? 0 : curr+1;
    }
    //------------Debug-------
                for(auto it = _sides.begin();it!=_sides.end();++it){
                    std::cout<<it->lin->getA_X()<<" : "<<it->lin->getB_X()<<" "<<it->dir<<std::endl;
                }
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
    
}
