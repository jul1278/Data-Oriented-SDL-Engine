//
// Created by Julian  on 18/11/15.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class Vector2D
{
public:

    Vector2D() : x(0.0), y(0.0) {}
    Vector2D(float x, float y) : x(x), y(y) { }

    Vector2D(float angle)
    {
        this->y = sinf(angle);
        this->x = cosf(angle);
    }

    float x;
    float y;

    Vector2D operator+(const Vector2D& rhs) const
    {
        Vector2D v(this->x + rhs.x, this->y + rhs.y);
        return v;
    }

	void operator+=(const Vector2D& rhs)
	{
		this->x += rhs.x; 
		this->y += rhs.y; 
	}

    Vector2D operator*(const float lhs) const
    {
        Vector2D v(lhs*this->x, lhs*this->y);
        return v;
    }

	void operator*=(const float lhs)
	{
		this->x *= lhs; 
		this->y *= lhs; 
	}

    Vector2D operator-(const Vector2D& rhs) const
    {
        Vector2D v(this->x - rhs.x, this->y - rhs.y);
        return v;
    }

	void operator-=(const Vector2D& rhs)
	{
		this->x -= rhs.x; 
		this->y -= rhs.y; 
	}

	bool operator==(const Vector2D& rhs) const
	{
		return ((this->x == rhs.x) && (this->y == rhs.y)); 
	}

	bool operator!=(const Vector2D& rhs) const
	{
		return !((*this) == rhs); 
	}

    float Length() const { return sqrtf( x*x + y*y );}
    float Angle() const { return atan2f(this->y, this->x); }

};

#endif //VECTOR_H_H
