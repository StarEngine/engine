#include "SerializedData.h"

namespace star
{
	SerializedData::SerializedData()
		: data(nullptr)
		, size(0)
	{

	}

	SerializedData::SerializedData(schar * buffer, unsigned int n)
		: data(buffer)
		, size(n)
	{

	}
}
