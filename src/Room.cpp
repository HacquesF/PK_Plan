#include "Room.hpp"

Room::Room(std::vector<Line*> lines){
    //Find the direction around the vector
    //  Find the highest X
    int maxX = 0;
    int maxL;
    for(unsigned int i = 0; i < lines.size();++i){
        if(lines[i]->getA_X() > maxX){
            maxL = i;
            maxX = lines[i]->getA_X();
        }
    }
    //Save the last A_X to understand the direction
    int lastAX = maxX;
    //For the highest point, the direction starts under or None
    if(lines[maxL]->isVert()){
        _sides.emplace_back(lines[maxL],dNone);
    }else{
       _sides.emplace_back(lines[maxL],dUnder); 
    }
    //We need to cycle through the vector until we get back to the starting line
    unsigned int curr = (maxL+1 == lines.size())? 0: maxL+1;
    while(curr != maxL){
        //If the current line is vertical
        if(lines[curr]->isVert()){
            //Had a line without direction
            _sides.emplace_back(lines[curr], dNone);
        }else{
            //We look for the direction of the line
            //  If we are going forward
            if(lastAX == lines[curr]->getB_X()){
                _sides.emplace_back(lines[curr], dUnder);
            //If we are going forward
            }else if (lastAX == lines[curr]->getA_X()){
                _sides.emplace_back(lines[curr], dUpper);
            }else{
                //The last X doesn't match any ends of the current line
                //There is a problem with the lines given
                std::cerr<<"Bad vector for rooms, lines don't follow"<< std::endl;
                return;
            }
            lastAX = lines[curr]->getA_X();
        }
        //Going to the next line while taking care of the cycling
        curr = (curr+1 == lines.size()) ? 0 : curr+1;
    }
}

Room::~Room(){}

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
