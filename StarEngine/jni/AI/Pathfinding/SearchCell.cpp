#include "SearchCell.h"
#include <algorithm>

namespace star
{
	SearchCell::SearchCell():
		X(0),
		Y(0),
		Id(0),
		Parent(nullptr),
		G(0),
		H(0)
	{
	}

	SearchCell::SearchCell(int32 x, int32 y, SearchCell *parent):
		X(x),
		Y(y),
		Id(y * WORLD_SIZE + x),
		Parent(parent),
		G(0),
		H(0)
	{
	}
	
	SearchCell::~SearchCell()
	{
	}

	float SearchCell::GetF() const
	{
		return G + H;
	}

	float SearchCell::ManhattanDistance(SearchCell *nodeEnd)
	{
		float x = static_cast<float>(
			fabs(static_cast<float>(X - nodeEnd->X))
			);
		float y = static_cast<float>(
			fabs(static_cast<float>(Y - nodeEnd->Y))
			);

		return std::max(x,y);
	}
}
