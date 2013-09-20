/*
 * EventLoop.h
 *
 *  Created on: 19-sep.-2013
 *      Author: Pieter Vantorre
 */

#pragma once

#include "defines.h"
#include <android_native_app_glue.h>

namespace star
{
	class EventLoop
	{
	public:
		EventLoop(android_app* pApplication);

		void run();

	private:
		android_app* mApplicationPtr;
	};
}

