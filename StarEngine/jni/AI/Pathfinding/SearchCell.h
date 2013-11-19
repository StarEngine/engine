#pragma once
#include <math.h>
#include "../../defines.h"

namespace star
{
	struct SearchCell
	{
		int32 X, Y, Id;
		SearchCell* Parent;
		float G, H; //f(x) = g(x) + h(x)
		static const int32 WORLD_SIZE = 15;

		SearchCell();
		SearchCell(int32 x, int32 y, SearchCell *parent);
		~SearchCell();
		float GetF() const;
		float ManhattanDistance(SearchCell *nodeEnd);
	};
}
