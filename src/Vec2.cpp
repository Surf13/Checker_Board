#include <cmath>
#include "Vec2.h"


    Vec2::Vec2() {}

    Vec2::Vec2(float x, float y)
        : x(x), y(y) {} 

    Vec2 Vec2::operator + (const Vec2 &rhs) const
    {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2 Vec2::operator - (const Vec2 &rhs) const
    {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2 Vec2::operator * (const Vec2 &rhs) const
    {
        return Vec2(x * rhs.x, y *rhs.y);
    }

    Vec2 Vec2::operator / (const Vec2 &rhs) const
    {
        return Vec2(x / rhs.x, y /rhs.y);
    }

    Vec2 Vec2::operator += (const Vec2 &rhs)
    {
        x = x+rhs.x;
        y = y+rhs.y;
        return Vec2(x,y);
    }

    Vec2 Vec2::operator -= (const Vec2 &rhs) 
    {
        x = x-rhs.x;
        y = y-rhs.y;
        return Vec2(x,y);
    }

    Vec2 Vec2::operator *= (const Vec2 &rhs)
    {
        x = x*rhs.x;
        y = y*rhs.y;
        return Vec2(x,y);
    }

    Vec2 Vec2::operator /= (const Vec2 &rhs) 
    {
        x = x/rhs.x;
        y = y/rhs.y;
        return Vec2(x,y);
    }

    float Vec2::distance(const Vec2 & rhs) const
    {
        return sqrt((x-rhs.x)*(x-rhs.x) +(y-rhs.y)*(y-rhs.y));
    }
