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
		Rect(const vec2& leftTop, const vec2& rightTop, const vec2& leftBottom, const vec2& rightBottom);
		//[TODO] write operators and copy constructors

		const vec2& GetLeftTop() const;
		const vec2& GetRightTop() const;
		const vec2& GetLeftBottom() const;
		const vec2& GetRightBottom() const;

		int GetRealLeft() const;
		int GetRealRight() const;
		int GetRealTop() const;
		int GetRealBottom() const;

	private:
		vec2 m_LeftTop;
		vec2 m_RightTop;
		vec2 m_LeftBottom;
		vec2 m_RightBottom;
	};
}
