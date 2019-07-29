#pragma once


struct Point{
    int x;
    int y;
};

class Position
{

    public:

        Position(){}
        
        Position(int x, int y, double velocity, double acceleration) :
            _point{x,y}, _velocity(velocity), _acceleration(acceleration) 
            {}

        void setPosition(int x, int y){
            _point.x = x;
            _point.y = y;
        }

    private:

        Point _point;
        double _velocity;
        double _acceleration;
};
