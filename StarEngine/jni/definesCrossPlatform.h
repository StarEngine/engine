#pragma once

#include "definesTypes.h"

struct BreakInformation
{
	BreakInformation();

	BreakInformation(
		int32 line,
		const sstring& fileName
		);

	tstring file;
	int32 line;
};

#define BREAK_INFO() BreakInformation(__LINE__, __FILE__)
