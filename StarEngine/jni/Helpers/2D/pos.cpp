#include "pos.h"

namespace star
{
	pos::pos()
		: x(0)
		, y(0)
		, l(0)
	{

	}

	pos::pos(const vec2 & vec, lay layer)
		: x(vec.x)
		, y(vec.y)
		, l(layer)
	{

	}

	pos::pos(int X, int Y, lay layer)
		: x((float)X)
		, y((float)Y)
		, l(layer)
	{

	}

	pos::pos(long X, long Y, lay layer)
		: x((float)X)
		, y((float)Y)
		, l(layer)
	{

	}

	pos::pos(float X, float Y, lay layer)
		: x(X)
		, y(Y)
		, l(layer)
	{

	}

	pos::pos(double X, double Y, lay layer)
		: x((float)X)
		, y((float)Y)
		, l(layer)
	{

	}

	pos::pos(const pos & yRef)
		: x(yRef.x)
		, y(yRef.y)
		, l(yRef.l)
	{

	}

	pos::pos(pos && yRef)
		: x(yRef.x)
		, y(yRef.y)
		, l(yRef.l)
	{

	}

	bool pos::operator==(const pos & yRef) const
	{
		bool is_true(x == yRef.x 
			&& y == yRef.y
			&& l == yRef.l);
		return is_true;
	}

	bool pos::operator!=(const pos & yRef) const
	{
		return !(operator==(yRef));
	}

	pos & pos::operator=(const pos & yRef)
	{
		x = yRef.x;
		y = yRef.y;
		l = yRef.l;

		return *this;
	}

	pos & pos::operator+=(const pos & yRef)
	{
		x += yRef.x;
		y += yRef.y;
		
		return *this;
	}

	pos & pos::operator-=(const pos & yRef)
	{
		x -= yRef.x;
		y -= yRef.y;

		return *this;
	}

	pos pos::operator+(const pos & yRef) const
	{
		pos copy(*this);
		copy.x += yRef.x;
		copy.y += yRef.y;

		return copy;
	}

	pos pos::operator-(const pos & yRef) const
	{
		pos copy(*this);
		copy.x -= yRef.x;
		copy.y -= yRef.y;

		return copy;
	}

	vec2 pos::pos2D() const
	{
		vec2 vec(x,y);
		return vec;
	}

	vec3 pos::pos3D() const
	{
		vec3 vec(x,y,(float)l);
		vec.z *= LAYER_HEIGHT;
		return vec;
	}

	float pos::length() const
	{
		return sqrt(pow(x,2) + pow(y,2));
	}
	
	pos & operator*=(pos & yRef, unsigned int n)
	{
		yRef.x *= (float)n;
		yRef.y *= (float)n;

		return yRef;
	}

	pos & operator*=(pos & yRef, unsigned long n)
	{
		yRef.x *= (float)n;
		yRef.y *= (float)n;

		return yRef;
	}

	pos & operator*=(pos & yRef, int n)
	{
		yRef.x *= (float)n;
		yRef.y *= (float)n;

		return yRef;
	}

	pos & operator*=(pos & yRef, long n)
	{
		yRef.x *= (float)n;
		yRef.y *= (float)n;

		return yRef;
	}

	pos & operator*=(pos & yRef, float n)
	{
		yRef.x *= n;
		yRef.y *= n;

		return yRef;
	}

	pos & operator*=(pos & yRef, double n)
	{
		yRef.x *= (float)n;
		yRef.y *= (float)n;

		return yRef;
	}
	
	pos & operator/=(pos & yRef, unsigned int n)
	{
		yRef.x /= (float)n;
		yRef.y /= (float)n;

		return yRef;
	}

	pos & operator/=(pos & yRef, unsigned long n)
	{
		yRef.x /= (float)n;
		yRef.y /= (float)n;

		return yRef;
	}

	pos & operator/=(pos & yRef, int n)
	{
		yRef.x /= (float)n;
		yRef.y /= (float)n;

		return yRef;
	}

	pos & operator/=(pos & yRef, long n)
	{
		yRef.x /= (float)n;
		yRef.y /= (float)n;

		return yRef;
	}

	pos & operator/=(pos & yRef, float n)
	{
		yRef.x /= n;
		yRef.y /= n;

		return yRef;
	}

	pos & operator/=(pos & yRef, double n)
	{
		yRef.x /= (float)n;
		yRef.y /= (float)n;

		return yRef;
	}
	
	pos operator*(pos & yRef, unsigned int n)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}

	pos operator*(pos & yRef, unsigned long n)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}

	pos operator*(pos & yRef, int n)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}

	pos operator*(pos & yRef, long n)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}

	pos operator*(pos & yRef, float n)
	{
		pos copy(yRef);

		copy.x *= n;
		copy.y *= n;

		return copy;
	}

	pos operator*(pos & yRef, double n)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}
	
	pos operator/(pos & yRef, unsigned int n)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}

	pos operator/(pos & yRef, unsigned long n)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}

	pos operator/(pos & yRef, int n)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}

	pos operator/(pos & yRef, long n)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}

	pos operator/(pos & yRef, float n)
	{
		pos copy(yRef);

		copy.x /= n;
		copy.y /= n;

		return copy;
	}

	pos operator/(pos & yRef, double n)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}
}
