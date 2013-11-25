#include "Rect.h"
#include "Math.h"

namespace star
{
	Rect::Rect()
		: m_LeftTop()
		, m_RightTop()
		, m_LeftBottom()
		, m_RightBottom()
		, m_Width()
		, m_Height()
		, m_Diagonal()
	{
		 
	}

	Rect::Rect(const vec2& leftBottom, const vec2& rightBottom, 
		const vec2& leftTop, const vec2& rightTop)
		: m_LeftTop(leftTop)
		, m_RightTop(rightTop)
		, m_LeftBottom(leftBottom)
		, m_RightBottom(rightBottom)
		, m_Width()
		, m_Height()
		, m_Diagonal()
	{
		//[COMMENT] This assert is temporarely disabled because of strange scale issues
		/*
	//Check if the rect is a  rect! (all angles ~90°)	
		float32 dot1 = Dot(rightTop - leftTop , leftBottom - leftTop);
		float32 dot2 = Dot(leftTop - rightTop , rightBottom - rightTop);
		float32 dot3 = Dot(rightTop - rightBottom, leftBottom - rightBottom);
		
		float32 tolerance = 0.1f;
		Logger::GetInstance()->Log((abs(dot1) < 0 + tolerance
			|| abs(dot2) < 0 + tolerance
			|| abs(dot3) < 0 + tolerance)
			, _T("The Rect is not a rectangle!!"));*/
			
		m_Width = m_RightTop.x - m_LeftTop.x;
		m_Height = m_RightTop.y - m_LeftTop.y;
		m_Diagonal = Mag(m_RightBottom - m_LeftTop);
	}

	Rect Rect::operator=(const Rect& yRef)
	{
		m_Diagonal = yRef.m_Diagonal;
		m_Height = yRef.m_Height;
		m_LeftBottom = yRef.m_LeftBottom;
		m_LeftTop = yRef.m_LeftTop;
		m_RightBottom = yRef.m_RightBottom;
		m_RightTop = yRef.m_RightTop;
		m_Width = yRef.m_Width;
		return *this;
	}

	Rect Rect::operator*(mat4 matrix) const
	{
		matrix = Transpose(matrix);
		vec4 returnVec1 = Mul(vec4(m_LeftBottom.x, m_LeftBottom.y, 0, 1), matrix);
		vec4 returnVec2 = Mul(vec4(m_RightBottom.x, m_RightBottom.y, 0, 1), matrix);
		vec4 returnVec3 = Mul(vec4(m_LeftTop.x, m_LeftTop.y, 0, 1), matrix);
		vec4 returnVec4 = Mul(vec4(m_RightTop.x, m_RightTop.y, 0, 1), matrix);

		return Rect(vec2(returnVec1.x , returnVec1.y),
					vec2(returnVec2.x , returnVec2.y),
					vec2(returnVec3.x , returnVec3.y),
					vec2(returnVec4.x , returnVec4.y));
	}

	Rect Rect::operator*(float32 constant) const
	{
		Rect temp;
		temp.m_LeftBottom = m_LeftBottom * constant;
		temp.m_LeftTop = m_LeftTop * constant;
		temp.m_RightBottom = m_RightBottom * constant;
		temp.m_RightTop = m_RightTop * constant;
		temp.m_Width = temp.m_RightTop.x - temp.m_LeftTop.x;
		temp.m_Height = temp.m_RightTop.y - temp.m_LeftTop.y;
		temp.m_Diagonal = Mag(temp.m_RightBottom - temp.m_LeftTop);

		return temp;
	}

	Rect Rect::operator/(float32 constant) const
	{
		Rect temp;
		temp.m_LeftBottom = m_LeftBottom / constant;
		temp.m_LeftTop = m_LeftTop / constant;
		temp.m_RightBottom = m_RightBottom / constant;
		temp.m_RightTop = m_RightTop / constant;
		temp.m_Width = temp.m_RightTop.x - temp.m_LeftTop.x;
		temp.m_Height = temp.m_RightTop.y - temp.m_LeftTop.y;
		temp.m_Diagonal = Mag(temp.m_RightBottom - temp.m_LeftTop);

		return temp;
	}

	Rect& Rect::operator*=(mat4 matrix)
	{
		matrix = Transpose(matrix);
		vec4 returnVec1 = Mul(vec4(m_LeftBottom.x, m_LeftBottom.y, 0, 0), matrix);
		vec4 returnVec2 = Mul(vec4(m_RightBottom.x, m_RightBottom.y, 0, 0), matrix);
		vec4 returnVec3 = Mul(vec4(m_LeftTop.x, m_LeftTop.y, 0, 0), matrix);
		vec4 returnVec4 = Mul(vec4(m_RightTop.x, m_RightTop.y, 0, 0), matrix);

		m_LeftBottom = vec2(returnVec1.x, returnVec1.y);
		m_RightBottom = vec2(returnVec2.x , returnVec2.y);
		m_LeftTop = vec2(returnVec3.x , returnVec3.y);
		m_RightTop = vec2(returnVec4.x , returnVec4.y);

		m_Width = m_RightTop.x - m_LeftTop.x;
		m_Height = m_RightTop.y - m_LeftTop.y;
		m_Diagonal = Mag(m_RightBottom - m_LeftTop);

		return *this;
	}

	Rect& Rect::operator*=(float32 constant)
	{
		m_LeftBottom *= constant;
		m_LeftTop *= constant;
		m_RightTop *= constant;
		m_RightBottom *= constant;

		m_Width = m_RightTop.x - m_LeftTop.x;
		m_Height = m_RightTop.y - m_LeftTop.y;
		m_Diagonal = Mag(m_RightBottom - m_LeftTop);

		return *this;
	}

	float32 Rect::GetWidth() const
	{
		return m_Width;
	}

	float32 Rect::GetHeight() const
	{
		return m_Height;
	}

	float32 Rect::GetDiagonal() const
	{
		return m_Diagonal;
	}

	const vec2& Rect::GetLeftTop() const
	{
		return m_LeftTop;
	}

	const vec2& Rect::GetRightTop() const
	{
		return m_RightTop;
	}

	const vec2& Rect::GetRightBottom() const
	{
		return m_RightBottom;
	}

	const vec2& Rect::GetLeftBottom() const
	{
		return m_LeftBottom;
	}

	vec2 Rect::GetCenterPoint() const
	{
		vec2 centerPos;
		centerPos.x = (GetRealLeft() + GetRealRight()) / 2.0f;
		centerPos.y = (GetRealTop() + GetRealBottom()) / 2.0f;
		return centerPos;
	}

	float32 Rect::GetRealLeft() const
	{
		float32 realLeft(m_LeftTop.x);
		realLeft = realLeft > m_LeftBottom.x ? m_LeftBottom.x : realLeft;
		realLeft = realLeft > m_RightBottom.x ? m_RightBottom.x : realLeft;
		realLeft = realLeft > m_RightTop.x ? m_RightTop.x : realLeft;
		return realLeft;
	}

	float32 Rect::GetRealRight() const
	{
		float32 realRight(m_RightTop.x);
		realRight = realRight < m_LeftBottom.x ? m_LeftBottom.x : realRight;
		realRight = realRight < m_RightBottom.x ? m_RightBottom.x : realRight;
		realRight = realRight < m_LeftTop.x ? m_LeftTop.x : realRight;
		return realRight;
	}

	float32 Rect::GetRealTop() const
	{
		float32 realTop(m_RightTop.y);
		realTop = realTop < m_LeftBottom.y ? m_LeftBottom.y : realTop;
		realTop = realTop < m_RightBottom.y ? m_RightBottom.y : realTop;
		realTop = realTop < m_LeftTop.y ? m_LeftTop.y : realTop;
		return realTop;
	}

	float32 Rect::GetRealBottom() const
	{
		float32 realBottom(m_LeftBottom.y);
		realBottom = realBottom > m_LeftTop.y ? m_LeftTop.y : realBottom;
		realBottom = realBottom > m_RightBottom.y ? m_RightBottom.y : realBottom;
		realBottom = realBottom > m_RightTop.y ? m_RightTop.y : realBottom;
		return realBottom;
	}

	void Rect::SetPoints(const vec2& leftBottom, const vec2& rightBottom, 
	const vec2& leftTop, const vec2& rightTop)
	{
		m_LeftBottom = leftBottom;
		m_LeftTop = leftTop;
		m_RightBottom = rightBottom;
		m_RightTop = rightTop;
		
		m_Width = m_RightTop.x - m_LeftTop.x;
		m_Height = m_RightTop.y - m_LeftTop.y;
		m_Diagonal = Mag(m_RightBottom - m_LeftTop);
	}

	void Rect::SetLeftTop(const vec2& pos)
	{
		m_LeftTop = pos;
	}

	void Rect::SetLeftBottom(const vec2& pos)
	{
		m_LeftBottom = pos;
	}

	void Rect::SetRightTop(const vec2& pos)
	{
		m_RightTop = pos;
	}

	void Rect::SetRightBottom(const vec2& pos)
	{
		m_RightBottom = pos;
	}
}
