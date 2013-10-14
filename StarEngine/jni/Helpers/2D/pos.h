#pragma once

#include "../../defines.h"

namespace star
{
	struct pos
	{
		float x, y;
		lay l;

		pos();
		pos(const vec2 & vec, lay layer = LAYER_DEF);
		pos(double X, double Y, lay layer = LAYER_DEF);
		pos(float X, float Y, lay layer = LAYER_DEF);
		pos(int X, int Y, lay layer = LAYER_DEF);
		pos(long X, long Y, lay layer = LAYER_DEF);
		pos(const pos & yRef);
		pos(pos && yRef);

		bool operator==(const pos & yRef) const;
		bool operator!=(const pos & yRef) const;

		pos & operator=(const pos & yRef);
		pos & operator+=(const pos & yRef);
		pos & operator-=(const pos & yRef);
		pos operator+(const pos & yRef) const;
		pos operator-(const pos & yRef) const;

		vec2 pos2D() const;
		vec3 pos3D() const;

		float length() const;
	};
	
	pos & operator*=(pos & yRef, unsigned int n);
	pos & operator*=(pos & yRef, unsigned long n);
	pos & operator*=(pos & yRef, int n);
	pos & operator*=(pos & yRef, long n);
	pos & operator*=(pos & yRef, float n);
	pos & operator*=(pos & yRef, double n);
	
	pos & operator/=(pos & yRef, unsigned int n);
	pos & operator/=(pos & yRef, unsigned long n);
	pos & operator/=(pos & yRef, int n);
	pos & operator/=(pos & yRef, long n);
	pos & operator/=(pos & yRef, float n);
	pos & operator/=(pos & yRef, double n);
	
	pos operator*(pos & yRef, unsigned int n);
	pos operator*(pos & yRef, unsigned long n);
	pos operator*(pos & yRef, int n);
	pos operator*(pos & yRef, long n);
	pos operator*(pos & yRef, float n);
	pos operator*(pos & yRef, double n);
	
	pos operator/(pos & yRef, unsigned int n);
	pos operator/(pos & yRef, unsigned long n);
	pos operator/(pos & yRef, int n);
	pos operator/(pos & yRef, long n);
	pos operator/(pos & yRef, float n);
	pos operator/(pos & yRef, double n);
}
