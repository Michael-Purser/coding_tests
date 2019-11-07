#ifndef POSITION_H_
#define POSITION_H_

class Position
{
    public:
        Position(int x, int y);
        void setX(int value);
        void setY(int value);
        int getX();
        int getY();
    private:
        int x_;
        int y_;
};

#endif