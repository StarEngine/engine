#pragma once

#include "TimeManager.h"
#include "Helpers/Time.h"
#include "Graphics/TextureManager.h"

namespace star
{
	/// <summary>
	/// Struct that is used to pass around information between all the 
	/// update functions in the engine classes.
	/// </summary>
	/// <seealso cref="TimeManager"></seealso>
	struct Context 
	{
		TimeManager * time;
	};
}
