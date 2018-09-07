#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>
#include <iostream>
#include "Line.hpp"
#include "Geom.hpp"//Direction

struct DirLine{
    Line* lin;
    Direction dir;
    DirLine(Line* l, Direction d) : lin(l),dir(d){}
};

class Room : public Geom {
private:
    std::vector<DirLine> _sides;
    
public:
    Room(std::vector<Line*>);
    ~Room();
    bool onIt(double,double,int);
    void drawOn(const Cairo::RefPtr<Cairo::Context>&);
};
#endif
