#include "Rect.h"

namespace star
{
	Rect::Rect()
		: m_LeftTop()
		, m_RightTop()
		, m_LeftBottom()
		, m_RightBottom()
	{
	}

	Rect::Rect(const vec2& leftTop, const vec2& rightTop, 
		const vec2& leftBottom, const vec2& rightBottom):
		m_LeftTop(leftTop),
		m_RightTop(rightTop),
		m_LeftBottom(leftBottom),
		m_RightBottom(rightBottom)
	{
	//Check if the rect is a  rect! (all angles 90°)	
		ASSERT(glm::dot(rightTop - leftTop , leftBottom - leftTop) == 0 
			|| glm::dot(leftTop - rightTop , rightBottom - rightTop) == 0 
			|| glm::dot(rightTop - rightBottom, leftBottom - rightBottom) == 0
			, _T("The Rect is not a rectangle!!"));
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

	int Rect::GetRealLeft() const
	{
		int realLeft(int(m_LeftTop.x));
		if(realLeft > m_LeftBottom.x)
		{
			realLeft = int(m_LeftBottom.x);
		}
		if(realLeft > m_RightBottom.x)
		{
			realLeft = int(m_RightBottom.x);
		}
		if(realLeft > m_RightTop.x)
		{
			realLeft = int(m_RightTop.x);
		}
		return realLeft;
	}

	int Rect::GetRealRight() const
	{
		int realRight(int(m_RightTop.x));
		if(realRight < m_LeftBottom.x)
		{
			realRight = int(m_LeftBottom.x);
		}
		if(realRight < m_RightBottom.x)
		{
			realRight = int(m_RightBottom.x);
		}
		if(realRight < m_LeftTop.x)
		{
			realRight = int(m_LeftTop.x);
		}
		return realRight;
	}

	int Rect::GetRealTop() const
	{
		int realTop(int(m_RightTop.y));
		if(realTop < m_LeftBottom.y)
		{
			realTop = int(m_LeftBottom.y);
		}
		if(realTop < m_RightBottom.y)
		{
			realTop = int(m_RightBottom.y);
		}
		if(realTop < m_LeftTop.y)
		{
			realTop = int(m_LeftTop.y);
		}
		return realTop;
	}

	int Rect::GetRealBottom() const
	{
		int realBottom(int(m_LeftBottom.y));
		if(realBottom > m_LeftTop.y)
		{
			realBottom = int(m_LeftTop.y);
		}
		if(realBottom > m_RightBottom.y)
		{
			realBottom = int(m_RightBottom.y);
		}
		if(realBottom > m_RightTop.y)
		{
			realBottom = int(m_RightTop.y);
		}
		return realBottom;
	}
}
