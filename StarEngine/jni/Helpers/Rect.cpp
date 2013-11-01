#include "Rect.h"

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
	//Check if the rect is a  rect! (all angles 90°)	
		ASSERT(glm::dot(rightTop - leftTop , leftBottom - leftTop) == 0 
			|| glm::dot(leftTop - rightTop , rightBottom - rightTop) == 0 
			|| glm::dot(rightTop - rightBottom, leftBottom - rightBottom) == 0
			, _T("The Rect is not a rectangle!!"));

		m_Width = m_RightTop.x - m_LeftTop.x;
		m_Height = m_RightTop.y - m_LeftTop.y;
		m_Diagonal = glm::length(m_RightBottom - m_LeftTop);
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
