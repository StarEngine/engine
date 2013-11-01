#pragma once

#include "glm\glm.h"
#include <algorithm>
#include "..\Logger.h"

namespace star
{
	class AARect
	{
	public:
		AARect();
		AARect(int x, int y, int width, int height);
		AARect(const vec2& location,const vec2& size);

		int GetLeft() const;
		int GetTop() const;
		int GetRight() const;
		int GetBottom() const;

		bool Equals(const AARect& rect) const;
		bool Contains(int x, int y) const;
		bool Contains(const vec2& pt) const;
		bool Contains(AARect& rect) const;
		bool Intersect(const AARect& rect);

		static bool Intersect(const AARect& a, const AARect& b);

	private:
		int m_X;
		int m_Y;
		int m_Width;
		int m_Height;
	};
}
