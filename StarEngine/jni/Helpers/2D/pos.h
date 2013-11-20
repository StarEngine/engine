#pragma once

#include "../../defines.h"

namespace star
{
	struct pos
	{
		float32 x, y;
		lay l;

		pos();
		explicit pos(const vec2 & vec, lay layer = LAYER_DEF);
		pos(float64 X, float64 Y, lay layer = LAYER_DEF);
		pos(float32 X, float32 Y, lay layer = LAYER_DEF);
		pos(int32 X, int32 Y, lay layer = LAYER_DEF);
		pos(int64 X, int64 Y, lay layer = LAYER_DEF);
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
		pos & operator*=(uint64 n);
		pos & operator*=(int32 n);
		pos & operator*=(int64 n);
		pos & operator*=(float32 n);
		pos & operator*=(float64 n);
	
		pos & operator/=(uint32 n);
		pos & operator/=(uint64 n);
		pos & operator/=(int32 n);
		pos & operator/=(int64 n);
		pos & operator/=(float32 n);
		pos & operator/=(float64 n);
	
		pos operator*(uint32 n);
		pos operator*(uint64 n);
		pos operator*(int32 n);
		pos operator*(int64 n);
		pos operator*(float32 n);
		pos operator*(float64 n);
	
		pos operator/(uint32 n);
		pos operator/(uint64 n);
		pos operator/(int32 n);
		pos operator/(int64 n);
		pos operator/(float32 n);
		pos operator/(float64 n);

		vec2 pos2D() const;
		vec3 pos3D() const;

		float32 length() const;
	
		friend pos operator*(uint32 n, const pos & yRef);
		friend pos operator*(uint64 n, const pos & yRef);
		friend pos operator*(int32 n, const pos & yRef);
		friend pos operator*(int64 n, const pos & yRef);
		friend pos operator*(float32 n, const pos & yRef);
		friend pos operator*(float64 n, const pos & yRef);
		friend pos operator*(const vec2 & v, const pos & yRef);
	
		friend pos operator/(uint32 n, const pos & yRef);
		friend pos operator/(uint64 n, const pos & yRef);
		friend pos operator/(int32 n, const pos & yRef);
		friend pos operator/(int64 n, const pos & yRef);
		friend pos operator/(float32 n, const pos & yRef);
		friend pos operator/(float64 n, const pos & yRef);
		friend pos operator/(const vec2 & v, const pos & yRef);

		friend bool operator==(const vec2 & lRef, const pos & rRef);
		friend bool operator!=(const vec2 & lRef, const pos & rRef);
	};
}
