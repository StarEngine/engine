#pragma once
#include <math.h>

// [COMMENT] if you have a struct with public datamembers.
//			 Please make them more easier to use. (e.g.: X instead of m_X)
//			 This feels more natural to use and looks more beautifull as well...
struct SearchCell
{
public : 
	//Datamembers
	int m_X, m_Y, m_Id;
	SearchCell* m_pParent;
	float m_G, m_H; //f(x) = g(x) + h(x)
	static const int WORLD_SIZE = 15;

	//Functions
	SearchCell():
		m_X(0),
		m_Y(0),
		m_Id(0),
		m_pParent(nullptr),
		m_G(0),
		m_H(0)
	{
	}

	SearchCell(int x, int y, SearchCell *parent):
		m_X(x),
		m_Y(y),
		m_Id(y * WORLD_SIZE + x),
		m_pParent(parent),
		m_G(0),
		m_H(0)
	{
	}

	float GetF() const {return m_G+m_H;};
	float ManhattanDistance(SearchCell *nodeEnd)
	{
		float x = static_cast<float>(fabs(static_cast<float>(this->m_X - nodeEnd->m_X)));
		float y = static_cast<float>(fabs(static_cast<float>(this->m_Y - nodeEnd->m_Y)));

		return max(x,y);
	}
};