//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/   
#pragma once
#include "glm\glm.h"
#include <algorithm>
using namespace std;

#include "..\Logger.h"

class Rect
{
public:

	Rect()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}

	Rect(int left,int top,int width,int height)
    {
        x = left;
        y = top;

		//Assert(width >= 0, _T("Width negative!"));
		//Assert(height >= 0, _T("Height negative!"));

        width = width;
        height = height;

		tstringstream str;
		str << _T("Rect Created \t");
		str << _T("(") << x << _T(", ") << y << _T(", ") << width << _T(", ") << height << _T(")");
		star::Logger::GetSingleton()->Log(star::LogLevel::Info,str.str());
    }

	Rect(const glm::vec2& location,const glm::vec2& size)
    {
		x = static_cast<int>(location.x);
		y = static_cast<int>(location.y);
        width = static_cast<int>(size.x);
        height = static_cast<int>(size.y);
    }

    int GetLeft() const
    {
        return x;
    }

    int GetTop() const
    {
        return y;
    }

    int GetRight() const
    {
        return x+width;
    }

    int GetBottom() const
    {
        return y+height;
    }

    bool Equals(const Rect& rect) const
    {
        return x == rect.x &&
               y == rect.y &&
               width == rect.width &&
               height == rect.height;
    }

    bool Contains(int x, int y) const
    {
        return x >= x && x < x+width &&
               y >= y && y < y+height;
    }

    bool Contains(const glm::vec2& pt) const
    {
        return Contains(static_cast<int>(pt.x), static_cast<int>(pt.y));
    }

    bool Contains(Rect& rect) const
    {
        return (x <= rect.x) && (rect.GetRight() <= GetRight()) &&
               (y <= rect.y) && (rect.GetBottom() <= GetBottom());
    }

    bool Intersect(const Rect& rect)
    {
        return Intersect(*this, rect);
    }

    static bool Intersect(const Rect& a, const Rect& b)
    {
		int right = min(a.GetRight(), b.GetRight());
        int bottom = min(a.GetBottom(), b.GetBottom());
        int left = max(a.GetLeft(), b.GetLeft());
        int top = max(a.GetTop(), b.GetTop());

		Rect c;
        c.x = left;
        c.y = top;
        c.width = right - left;
        c.height = bottom - top;
        
		if(c.width <= 0 || c.height <= 0)
			return false;

		return true;
    }

public:
    int x;
    int y;
    int width;
    int height;
};