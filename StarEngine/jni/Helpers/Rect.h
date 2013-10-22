#pragma once

#include "glm\glm.h"
#include <algorithm>
#include "..\Logger.h"

namespace star
{
	class Rect
	{
	public:
		Rect();
		Rect(int x, int y, int width, int height);
		Rect(const vec2& location,const vec2& size);

		int GetLeft() const;
		int GetTop() const;
		int GetRight() const;
		int GetBottom() const;

		bool Equals(const Rect& rect) const;
		bool Contains(int x, int y) const;
		bool Contains(const vec2& pt) const;
		bool Contains(Rect& rect) const;
		bool Intersect(const Rect& rect);

		static bool Intersect(const Rect& a, const Rect& b);

	private:
		int m_X;
		int m_Y;
		int m_Width;
		int m_Height;
	};
}
