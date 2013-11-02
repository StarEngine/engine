#include "Rect.h"
#include "HelpersMath.h"

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
	//Check if the rect is a  rect! (all angles ~90°)	
		float dot1 = glm::dot(rightTop - leftTop , leftBottom - leftTop);
		float dot2 = glm::dot(leftTop - rightTop , rightBottom - rightTop);
		float dot3 = glm::dot(rightTop - rightBottom, leftBottom - rightBottom);
		float tolerance = 0.01f;
		ASSERT((abs(dot1) < 0 + tolerance
			|| abs(dot2) < 0 + tolerance
			|| abs(dot3) < 0 + tolerance)
			, _T("The Rect is not a rectangle!!"));
			
		m_Width = m_RightTop.x - m_LeftTop.x;
		m_Height = m_RightTop.y - m_LeftTop.y;
		m_Diagonal = glm::length(m_RightBottom - m_LeftTop);
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

	Rect Rect::operator*(glm::mat4x4 matrix) const
	{
		matrix = TransposeMatrix(matrix);
		vec4 returnVec1 = glm::mul(vec4(m_LeftBottom.x, m_LeftBottom.y, 0, 1), matrix);
		vec4 returnVec2 = glm::mul(vec4(m_RightBottom.x, m_RightBottom.y, 0, 1), matrix);
		vec4 returnVec3 = glm::mul(vec4(m_LeftTop.x, m_LeftTop.y, 0, 1), matrix);
		vec4 returnVec4 = glm::mul(vec4(m_RightTop.x, m_RightTop.y, 0, 1), matrix);

		return Rect(vec2(returnVec1.x , returnVec1.y),
					vec2(returnVec2.x , returnVec2.y),
					vec2(returnVec3.x , returnVec3.y),
					vec2(returnVec4.x , returnVec4.y));
	}

	Rect& Rect::operator*=(const glm::mat4x4 matrix)
	{
		vec4 returnVec1 = glm::mul(vec4(m_LeftBottom.x, m_LeftBottom.y, 0, 0), matrix);
		vec4 returnVec2 = glm::mul(vec4(m_RightBottom.x, m_RightBottom.y, 0, 0), matrix);
		vec4 returnVec3 = glm::mul(vec4(m_LeftTop.x, m_LeftTop.y, 0, 0), matrix);
		vec4 returnVec4 = glm::mul(vec4(m_RightTop.x, m_RightTop.y, 0, 0), matrix);

		m_LeftBottom = vec2(returnVec1.x, returnVec1.y);
		m_RightBottom = vec2(returnVec2.x , returnVec2.y);
		m_LeftTop = vec2(returnVec3.x , returnVec3.y);
		m_RightTop = vec2(returnVec4.x , returnVec4.y);
		return *this;
	}

	float Rect::GetWidth() const
	{
		return m_Width;
	}

	float Rect::GetHeight() const
	{
		return m_Height;
	}

	float Rect::GetDiagonal() const
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

	float Rect::GetRealLeft() const
	{
		float realLeft(m_LeftTop.x);
		if(realLeft > m_LeftBottom.x)
		{
			realLeft = m_LeftBottom.x;
		}
		if(realLeft > m_RightBottom.x)
		{
			realLeft = m_RightBottom.x;
		}
		if(realLeft > m_RightTop.x)
		{
			realLeft = m_RightTop.x;
		}
		return realLeft;
	}

	float Rect::GetRealRight() const
	{
		float realRight(m_RightTop.x);
		if(realRight < m_LeftBottom.x)
		{
			realRight = m_LeftBottom.x;
		}
		if(realRight < m_RightBottom.x)
		{
			realRight = m_RightBottom.x;
		}
		if(realRight < m_LeftTop.x)
		{
			realRight = m_LeftTop.x;
		}
		return realRight;
	}

	float Rect::GetRealTop() const
	{
		float realTop(m_RightTop.y);
		if(realTop < m_LeftBottom.y)
		{
			realTop = m_LeftBottom.y;
		}
		if(realTop < m_RightBottom.y)
		{
			realTop = m_RightBottom.y;
		}
		if(realTop < m_LeftTop.y)
		{
			realTop = m_LeftTop.y;
		}
		return realTop;
	}

	float Rect::GetRealBottom() const
	{
		float realBottom(m_LeftBottom.y);
		if(realBottom > m_LeftTop.y)
		{
			realBottom = m_LeftTop.y;
		}
		if(realBottom > m_RightBottom.y)
		{
			realBottom = m_RightBottom.y;
		}
		if(realBottom > m_RightTop.y)
		{
			realBottom = m_RightTop.y;
		}
		return realBottom;
	}

	void Rect::SetPoints(const vec2& leftBottom, const vec2& rightBottom, 
	const vec2& leftTop, const vec2& rightTop)
	{
		m_LeftBottom = leftBottom;
		m_LeftTop = leftTop;
		m_RightBottom = rightBottom;
		m_RightTop = rightTop;
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
