#include "SerializedData.h"

namespace star
{
	SerializedData::SerializedData()
		: data(nullptr)
		, size(0)
	{

	}

	SerializedData::SerializedData(char * buffer, unsigned int n)
		: data(buffer)
		, size(n)
	{

	}
}
