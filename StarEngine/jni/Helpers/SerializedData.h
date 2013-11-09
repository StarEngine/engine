#pragma once

namespace star
{
	struct SerializedData
	{
		char * data;
		unsigned int size;

		SerializedData();
		SerializedData(char * buffer, unsigned int n);
	};
}
