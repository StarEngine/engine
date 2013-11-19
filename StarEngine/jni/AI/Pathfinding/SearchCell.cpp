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

	float32 SearchCell::GetF() const
	{
		return G + H;
	}

	float32 SearchCell::ManhattanDistance(SearchCell *nodeEnd)
	{
		float32 x = static_cast<float32>(
			fabs(static_cast<float32>(X - nodeEnd->X))
			);
		float32 y = static_cast<float32>(
			fabs(static_cast<float32>(Y - nodeEnd->Y))
			);

		return std::max(x,y);
	}
}
