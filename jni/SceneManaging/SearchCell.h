#pragma once
#include <math.h>

struct SearchCell
{
public : 
	//Datamembers
	int X, Y, Id;
	SearchCell* Parent;
	float G, H; //f(x) = g(x) + h(x)
	static const int WORLD_SIZE = 15;

	//Functions
	SearchCell():
		X(0),
		Y(0),
		Id(0),
		Parent(nullptr),
		G(0),
		H(0)
	{
	}

	SearchCell(int x, int y, SearchCell *parent):
		X(x),
		Y(y),
		Id(y * WORLD_SIZE + x),
		Parent(parent),
		G(0),
		H(0)
	{
	}

	float GetF() const {return G+H;};
	float ManhattanDistance(SearchCell *nodeEnd)
	{
		float x = static_cast<float>(fabs(static_cast<float>(this->X - nodeEnd->X)));
		float y = static_cast<float>(fabs(static_cast<float>(this->Y - nodeEnd->Y)));

		return std::max(x,y);
	}
};