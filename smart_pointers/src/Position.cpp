#include "../include/Position.h"

Position::Position(int x, int y) :
    x_(x),
    y_(y)
{
}

void Position::setX(int value)
{
    x_ = value;
}

void Position::setY(int value)
{
    y_ = value;
}

int Position::getX()
{
    return x_;
}

int Position::getY()
{
    return y_;
}