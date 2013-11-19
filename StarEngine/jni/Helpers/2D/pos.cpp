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

	pos::pos(int32 X, int32 Y, lay layer)
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

	bool pos::operator==(const vec2 & yRef) const
	{
		bool is_true(x == yRef.x 
			&& y == yRef.y);
		return is_true;
	}

	bool pos::operator!=(const pos & yRef) const
	{
		return !(*this == yRef);
	}

	bool pos::operator!=(const vec2 & yRef) const
	{
		return !(*this == yRef);
	}

	pos & pos::operator=(const pos & yRef)
	{
		x = yRef.x;
		y = yRef.y;
		l = yRef.l;

		return *this;
	}

	pos & pos::operator=(const vec2 & yRef)
	{
		x = yRef.x;
		y = yRef.y;

		return *this;
	}

	pos & pos::operator+=(const pos & yRef)
	{
		x += yRef.x;
		y += yRef.y;
		
		return *this;
	}

	pos & pos::operator+=(const vec2 & yRef)
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

	pos & pos::operator-=(const vec2 & yRef)
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

	pos pos::operator+(const vec2 & yRef) const
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

	pos pos::operator-(const vec2 & yRef) const
	{
		pos copy(*this);
		copy.x -= yRef.x;
		copy.y -= yRef.y;

		return copy;
	}

	pos pos::operator*(uint32 n)
	{
		pos copy(*this);
		copy *= n;
		
		return copy;
	}

	pos pos::operator*(unsigned long n)
	{
		pos copy(*this);
		copy *= n;
		
		return copy;
	}

	pos pos::operator*(int32 n)
	{
		pos copy(*this);
		copy *= n;
		
		return copy;
	}

	pos pos::operator*(long n)
	{
		pos copy(*this);
		copy *= n;
		
		return copy;
	}

	pos pos::operator*(float n)
	{
		pos copy(*this);
		copy *= n;
		
		return copy;
	}

	pos pos::operator*(double n)
	{
		pos copy(*this);
		copy *= n;
		
		return copy;
	}
	
	pos pos::operator/(uint32 n)
	{
		pos copy(*this);
		copy /= n;
		
		return copy;
	}

	pos pos::operator/(unsigned long n)
	{
		pos copy(*this);
		copy /= n;
		
		return copy;
	}

	pos pos::operator/(int32 n)
	{
		pos copy(*this);
		copy /= n;
		
		return copy;
	}

	pos pos::operator/(long n)
	{
		pos copy(*this);
		copy /= n;
		
		return copy;
	}

	pos pos::operator/(float n)
	{
		pos copy(*this);
		copy /= n;
		
		return copy;
	}

	pos pos::operator/(double n)
	{
		pos copy(*this);
		copy /= n;
		
		return copy;
	}
	
	pos & pos::operator*=(uint32 n)
	{
		x *= (float)n;
		y *= (float)n;

		return *this;
	}

	pos & pos::operator*=(unsigned long n)
	{
		x *= (float)n;
		y *= (float)n;

		return *this;
	}

	pos & pos::operator*=(int32 n)
	{
		x *= (float)n;
		y *= (float)n;

		return *this;
	}

	pos & pos::operator*=(long n)
	{
		x *= (float)n;
		y *= (float)n;

		return *this;
	}

	pos & pos::operator*=(float n)
	{
		x *= n;
		y *= n;

		return *this;
	}

	pos & pos::operator*=(double n)
	{
		x *= (float)n;
		y *= (float)n;

		return *this;
	}
	
	pos & pos::operator/=(uint32 n)
	{
		x /= (float)n;
		y /= (float)n;

		return *this;
	}

	pos & pos::operator/=(unsigned long n)
	{
		x /= (float)n;
		y /= (float)n;

		return *this;
	}

	pos & pos::operator/=(int32 n)
	{
		x /= (float)n;
		y /= (float)n;

		return *this;
	}

	pos & pos::operator/=(long n)
	{
		x /= (float)n;
		y /= (float)n;

		return *this;
	}

	pos & pos::operator/=(float n)
	{
		x /= n;
		y /= n;

		return *this;
	}

	pos & pos::operator/=(double n)
	{
		x /= (float)n;
		y /= (float)n;

		return *this;
	}
	
	pos operator*(uint32 n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}

	pos operator*(unsigned long n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}

	pos operator*(int32 n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}

	pos operator*(long n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}

	pos operator*(float n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x *= n;
		copy.y *= n;

		return copy;
	}

	pos operator*(double n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x *= (float)n;
		copy.y *= (float)n;

		return copy;
	}

	pos operator*(const vec2 & v, const pos & yRef)
	{
		pos copy(yRef);

		copy.x *= v.x;
		copy.y *= v.y;

		return copy;
	}
	
	pos operator/(uint32 n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}

	pos operator/(unsigned long n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}

	pos operator/(int32 n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}

	pos operator/(long n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}

	pos operator/(float n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x /= n;
		copy.y /= n;

		return copy;
	}

	pos operator/(double n, const pos & yRef)
	{
		pos copy(yRef);

		copy.x /= (float)n;
		copy.y /= (float)n;

		return copy;
	}

	pos operator/(const vec2 & v, const pos & yRef)
	{
		pos copy(yRef);

		copy.x /= v.x;
		copy.y /= v.y;

		return copy;
	}

	bool operator==(const vec2 & lRef, const pos & rRef)
	{
		return rRef == lRef;
	}

	bool operator!=(const vec2 & lRef, const pos & rRef)
	{
		return rRef == lRef;
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
}
