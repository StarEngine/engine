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
		pos(int32 X, int32 Y, lay layer = LAYER_DEF);
		pos(long X, long Y, lay layer = LAYER_DEF);
		pos(const pos & yRef);
		pos(pos && yRef);

		bool operator==(const pos & yRef) const;
		bool operator==(const vec2 & yRef) const;
		bool operator!=(const pos & yRef) const;
		bool operator!=(const vec2 & yRef) const;

		pos & operator=(const pos & yRef);
		pos & operator=(const vec2 & yRef);
		pos & operator+=(const pos & yRef);
		pos & operator+=(const vec2 & yRef);
		pos & operator-=(const pos & yRef);
		pos & operator-=(const vec2 & yRef);
		pos operator+(const pos & yRef) const;
		pos operator+(const vec2 & yRef) const;
		pos operator-(const pos & yRef) const;
		pos operator-(const vec2 & yRef) const;
	
		pos & operator*=(uint32 n);
		pos & operator*=(unsigned long n);
		pos & operator*=(int32 n);
		pos & operator*=(long n);
		pos & operator*=(float n);
		pos & operator*=(double n);
	
		pos & operator/=(uint32 n);
		pos & operator/=(unsigned long n);
		pos & operator/=(int32 n);
		pos & operator/=(long n);
		pos & operator/=(float n);
		pos & operator/=(double n);
	
		pos operator*(uint32 n);
		pos operator*(unsigned long n);
		pos operator*(int32 n);
		pos operator*(long n);
		pos operator*(float n);
		pos operator*(double n);
	
		pos operator/(uint32 n);
		pos operator/(unsigned long n);
		pos operator/(int32 n);
		pos operator/(long n);
		pos operator/(float n);
		pos operator/(double n);

		vec2 pos2D() const;
		vec3 pos3D() const;

		float length() const;
	
		friend pos operator*(uint32 n, const pos & yRef);
		friend pos operator*(unsigned long n, const pos & yRef);
		friend pos operator*(int32 n, const pos & yRef);
		friend pos operator*(long n, const pos & yRef);
		friend pos operator*(float n, const pos & yRef);
		friend pos operator*(double n, const pos & yRef);
		friend pos operator*(const vec2 & v, const pos & yRef);
	
		friend pos operator/(uint32 n, const pos & yRef);
		friend pos operator/(unsigned long n, const pos & yRef);
		friend pos operator/(int32 n, const pos & yRef);
		friend pos operator/(long n, const pos & yRef);
		friend pos operator/(float n, const pos & yRef);
		friend pos operator/(double n, const pos & yRef);
		friend pos operator/(const vec2 & v, const pos & yRef);

		friend bool operator==(const vec2 & lRef, const pos & rRef);
		friend bool operator!=(const vec2 & lRef, const pos & rRef);
	};
}
