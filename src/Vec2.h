#ifndef VEC2_H
#define VEC2_H

class Vec2{

public:
    float x = 0;
    float y = 0;

    Vec2();

    Vec2(float x_in, float y_in);

    Vec2 operator + (const Vec2 &rhs) const;
    Vec2 operator - (const Vec2 &rhs) const;
    Vec2 operator * (const Vec2 &rhs) const;
    Vec2 operator / (const Vec2 &rhs) const;

    Vec2 operator += (const Vec2 &rhs);
    Vec2 operator -= (const Vec2 &rhs);
    Vec2 operator *= (const Vec2 &rhs);
    Vec2 operator /= (const Vec2 &rhs);

    float distance(const Vec2 & rhs) const;
};

#endif