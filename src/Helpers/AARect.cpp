#include "AARect.h"

namespace star
{
	AARect::AARect():
		m_X(0),
		m_Y(0),
		m_Width(0),
		m_Height(0)
	{
	}

	AARect::AARect(int32 x, int32 y, int32 width, int32 height):
		m_X(x),
		m_Y(y),
		m_Width(width),
		m_Height(height)
	{
		ASSERT_LOG(m_Width >= 0,
			_T("Width can't be negative!"), STARENGINE_LOG_TAG);
		ASSERT_LOG(m_Height >= 0,
			_T("Height can't be negative!"), STARENGINE_LOG_TAG);
	}

	AARect::AARect(const vec2& location,const vec2& size)
	{
		m_X = static_cast<int32>(location.x);
		m_Y = static_cast<int32>(location.y);
		m_Width = static_cast<int32>(size.x);
		m_Height = static_cast<int32>(size.y);
	}

	AARect::~AARect()
	{

	}

	int32 AARect::GetLeft() const
	{
		return m_X;
	}

	int32 AARect::GetTop() const
	{
		return m_Y;
	}

	int32 AARect::GetRight() const
	{
		return m_X + m_Width;
	}

	int32 AARect::GetBottom() const
	{
		return m_Y + m_Height;
	}

	void AARect::SetLeft(int32 left)
	{
		m_X = left;
	}

	void AARect::SetTop(int32 top)
	{
		m_Height = top - m_Y;
	}

	void AARect::SetRight(int32 right)
	{
		m_Width = right - m_X;
	}

	void AARect::SetBottom(int32 bottom)
	{
		m_Y = bottom;
	}

	bool AARect::Equals(const AARect& rect) const
	{
		return m_X == rect.m_X &&
			m_Y == rect.m_Y &&
			m_Width == rect.m_Width &&
			m_Height == rect.m_Height;
	}

	bool AARect::Contains(int32 x, int32 y) const
	{
		return x >= m_X && x < (m_X + m_Width) &&
			y >= m_Y && y < (m_Y + m_Height);
	}

	bool AARect::Contains(const vec2& pt) const
	{
		return Contains(int32(pt.x), int32(pt.y));
	}

	bool AARect::Contains(AARect& rect) const
	{
		return (m_X <= rect.m_X) && (rect.GetRight() <= GetRight()) &&
				(m_Y <= rect.m_Y) && (rect.GetBottom() <= GetBottom());
	}

	bool AARect::Intersect(const AARect& rect)
	{
		return Intersect(*this, rect);
	}

	bool AARect::Intersect(const AARect& a, const AARect& b)
	{
		int32 right = min(a.GetRight(), b.GetRight());
		int32 bottom = min(a.GetBottom(), b.GetBottom());
		int32 left = max(a.GetLeft(), b.GetLeft());
		int32 top = max(a.GetTop(), b.GetTop());

		AARect c(
		left,
		top,
		right - left,
		bottom - top);

		return !(c.m_Width <= 0 || c.m_Height <= 0);
	}
}
