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

		Rect operator*(glm::mat4x4 matrix) const;
		Rect operator*(float constant) const;

		Rect operator/(float constant) const;

		Rect& operator*=(glm::mat4x4 matrix);		
		Rect& operator*=(float constant);


		float GetWidth() const;
		float GetHeight() const;
		float GetDiagonal() const;

		const vec2& GetLeftTop() const;
		const vec2& GetRightTop() const;
		const vec2& GetLeftBottom() const;
		const vec2& GetRightBottom() const;

		vec2 GetCenterPoint() const;

		float GetRealLeft() const;
		float GetRealRight() const;
		float GetRealTop() const;
		float GetRealBottom() const;

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

		float m_Width;
		float m_Height;
		float m_Diagonal;
	};
}
