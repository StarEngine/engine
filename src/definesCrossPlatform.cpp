#include "definesCrossPlatform.h"
#include "Helpers/Helpers.h"

BreakInformation::BreakInformation()
	: line(-1)
	, file(EMPTY_STRING) 
{
}

BreakInformation::BreakInformation(
	int32 line,
	const sstring& fileName
	)
	: line(line)
	, file(EMPTY_STRING) 
{
	file = star::string_cast<tstring>(fileName);
	file = star::GetFileName(file);
}
