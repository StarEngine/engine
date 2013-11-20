#pragma once

#include "../definesTypes.h"

namespace star
{
	struct SerializedData
	{
		schar * data;
		uint32 size;

		SerializedData();
		SerializedData(schar * buffer, uint32 n);
	};
}
