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
		AARect(int32 x, int32 y, int32 width, int32 height);
		AARect(const vec2& location,const vec2& size);
		~AARect();

		int32 GetLeft() const;
		int32 GetTop() const;
		int32 GetRight() const;
		int32 GetBottom() const;

		void SetLeft(int32 left);
		void SetTop(int32 top);
		void SetRight(int32 right);
		void SetBottom(int32 bottom);

		bool Equals(const AARect& rect) const;
		bool Contains(int32 x, int32 y) const;
		bool Contains(const vec2& pt) const;
		bool Contains(AARect& rect) const;
		bool Intersect(const AARect& rect);

		static bool Intersect(const AARect& a, const AARect& b);

	private:
		int32 m_X;
		int32 m_Y;
		int32 m_Width;
		int32 m_Height;

		int32 m_Left;
		int32 m_Right;
		int32 m_Top;
		int32 m_Bottom;

		AARect* m_IntersectRect;
	};
}
