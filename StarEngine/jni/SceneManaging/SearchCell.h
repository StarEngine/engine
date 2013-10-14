#pragma once
#include <math.h>

namespace star
{
	struct SearchCell
	{
		int X, Y, Id;
		SearchCell* Parent;
		float G, H; //f(x) = g(x) + h(x)
		static const int WORLD_SIZE = 15;

		SearchCell();
		SearchCell(int x, int y, SearchCell *parent);
		float GetF() const;
		float ManhattanDistance(SearchCell *nodeEnd);
	};
}
