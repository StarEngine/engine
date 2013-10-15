#include "Rect.h"

namespace star
{
	Rect::Rect():
		m_X(0),
		m_Y(0),
		m_Width(0),
		m_Height(0)
	{
	}

	Rect::Rect(int x, int y, int width, int height):
		m_X(x),
		m_Y(y),
		m_Width(width),
		m_Height(height)
	{
		ASSERT(m_Width >= 0, _T("Width can't be negative!"));
		ASSERT(m_Height >= 0, _T("Height can't be negative!"));

		tstringstream str;
		str << _T("Rect Created \t");
		str << _T("(") << x << _T(", ") << y << _T(", ") << width << _T(", ") << height << _T(")");
		Logger::GetInstance()->Log(LogLevel::Info,str.str());
	}

	Rect::Rect(const vec2& location,const vec2& size)
	{
		m_X = static_cast<int>(location.x);
		m_Y = static_cast<int>(location.y);
		m_Width = static_cast<int>(size.x);
		m_Height = static_cast<int>(size.y);
	}

	int Rect::GetLeft() const
	{
		return m_X;
	}

	int Rect::GetTop() const
	{
		return m_Y;
	}

	int Rect::GetRight() const
	{
		return m_X + m_Width;
	}

	int Rect::GetBottom() const
	{
		return m_Y + m_Height;
	}

	bool Rect::Equals(const Rect& rect) const
	{
		return m_X == rect.m_X &&
			m_Y == rect.m_Y &&
			m_Width == rect.m_Width &&
			m_Height == rect.m_Height;
	}

	bool Rect::Contains(int x, int y) const
	{
		return x >= m_X && x < m_X + m_Width &&
			y >= m_Y && y < m_Y + m_Height;
	}

	bool Rect::Contains(const glm::vec2& pt) const
	{
		return Contains(static_cast<int>(pt.x), static_cast<int>(pt.y));
	}

	bool Rect::Contains(Rect& rect) const
	{
		return (m_X <= rect.m_X) && (rect.GetRight() <= GetRight()) &&
				(m_Y <= rect.m_Y) && (rect.GetBottom() <= GetBottom());
	}

	bool Rect::Intersect(const Rect& rect)
	{
		return Intersect(*this, rect);
	}

	bool Rect::Intersect(const Rect& a, const Rect& b)
	{
		int right = min(a.GetRight(), b.GetRight());
		int bottom = min(a.GetBottom(), b.GetBottom());
		int left = max(a.GetLeft(), b.GetLeft());
		int top = max(a.GetTop(), b.GetTop());

		Rect c;
		c.m_X = left;
		c.m_Y = top;
		c.m_Width = right - left;
		c.m_Height = bottom - top;

		return !(c.m_Width <= 0 || c.m_Height <= 0);
	}
}
