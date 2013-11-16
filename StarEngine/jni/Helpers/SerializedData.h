#pragma once

#include "../definesTypes.h"

namespace star
{
	struct SerializedData
	{
		schar * data;
		unsigned int size;

		SerializedData();
		SerializedData(schar * buffer, unsigned int n);
	};
}
