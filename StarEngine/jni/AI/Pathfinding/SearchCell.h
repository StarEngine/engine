#pragma once
#include <math.h>
#include "../../defines.h"

namespace star
{
	struct SearchCell
	{
		int32 x, y, id;
		SearchCell* parent;
		float32 g, h; //f(x) = g(x) + h(x)
		static const int32 WORLD_SIZE = 15;

		SearchCell();
		SearchCell(int32 x, int32 y, SearchCell *parent);
		~SearchCell();
		float32 GetF() const;
		float32 ManhattanDistance(SearchCell *nodeEnd);
	};
}
