#include "SerializedData.h"

namespace star
{
	SerializedData::SerializedData()
		: data(nullptr)
		, size(0)
	{

	}

	SerializedData::SerializedData(schar * buffer, uint32 n)
		: data(buffer)
		, size(n)
	{

	}
}
