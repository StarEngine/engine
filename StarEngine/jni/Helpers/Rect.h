#pragma once

#include <algorithm>
#include "../Logger.h"
#include "../defines.h"

namespace star
{
	class Rect
	{
	public:
		Rect();
		Rect(const vec2& leftBottom, const vec2& rightBottom, 
		const vec2& leftTop, const vec2& rightTop);
		Rect operator=(const Rect& yRef);
		//[TODO] write operators and copy + move constructors (and non member operators)

		Rect operator*(mat4 matrix) const;
		Rect operator*(float32 constant) const;

		Rect operator/(float32 constant) const;

		Rect& operator*=(mat4 matrix);		
		Rect& operator*=(float32 constant);


		float32 GetWidth() const;
		float32 GetHeight() const;
		float32 GetDiagonal() const;

		const vec2& GetLeftTop() const;
		const vec2& GetRightTop() const;
		const vec2& GetLeftBottom() const;
		const vec2& GetRightBottom() const;

		vec2 GetCenterPoint() const;

		float32 GetRealLeft() const;
		float32 GetRealRight() const;
		float32 GetRealTop() const;
		float32 GetRealBottom() const;

		void SetPoints(const vec2& leftBottom, const vec2& rightBottom, 
		const vec2& leftTop, const vec2& rightTop);
		void SetLeftTop(const vec2& pos);
		void SetLeftBottom(const vec2& pos);
		void SetRightTop(const vec2& pos);
		void SetRightBottom(const vec2& pos);

	private:
		vec2 m_LeftTop;
		vec2 m_RightTop;
		vec2 m_LeftBottom;
		vec2 m_RightBottom;

		float32 m_Width;
		float32 m_Height;
		float32 m_Diagonal;
	};
}
