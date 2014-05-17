#include "SearchCell.h"
#include <algorithm>
#include "../../Helpers/Math.h"

namespace star
{
	SearchCell::SearchCell():
		x(0),
		y(0),
		id(0),
		parent(nullptr),
		g(0),
		h(0)
	{
	}

	SearchCell::SearchCell(int32 x, int32 y, SearchCell *parent):
		x(x),
		y(y),
		id(y * WORLD_SIZE + x),
		parent(parent),
		g(0),
		h(0)
	{
	}
	
	SearchCell::~SearchCell()
	{
	}

	float32 SearchCell::GetF() const
	{
		return g + h;
	}

	float32 SearchCell::ManhattanDistance(SearchCell *nodeEnd)
	{
		float32 tempX = static_cast<float32>(
			fabs(static_cast<float32>(x - nodeEnd->x))
			);
		float32 tempY = static_cast<float32>(
			fabs(static_cast<float32>(y - nodeEnd->y))
			);

		return std::max(tempX, tempY);
	}
}
