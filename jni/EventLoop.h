/*
 * EventLoop.h
 *
 *  Created on: 19-sep.-2013
 *      Author: Pieter Vantorre
 */

#pragma once

#include "defines.h"
#include <android_native_app_glue.h>

class SceneManager;

namespace star
{
	class EventLoop
	{
	public:
		EventLoop(android_app* pApplication);

		void run();

	protected:
		static void activityCallback(android_app* pApplication, int32_t pCommand);

	private:
		android_app* mApplicationPtr;
		bool mEnabled;
		bool mQuit;
		SceneManager* mSceneManager;
	};
}

