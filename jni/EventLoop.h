/*
 * EventLoop.h
 *
 *  Created on: 19-sep.-2013
 *      Author: Pieter Vantorre
 *  Edited by
 *  	Simon Vanhauwaert
 */

#ifndef _EVENTLOOP_
#define _EVENTLOOP_

#include "defines.h"
#include <android_native_app_glue.h>
#include "MainGame.h"
#include "Context.h"
#include "TimeManager.h"

class SceneManager;

namespace star
{
	class EventLoop
	{
	public:
		static android_app* mApplicationPtr;

		EventLoop(android_app* pApplication);

		void run();
		void end();

		//[COMMENT] Scanning through the sample files, these methodes are private. can they be moved?
	protected:
		static void activityCallback(android_app* pApplication, int32_t pCommand);
		static int32 inputCallback(android_app* pApplication, AInputEvent* pEvent);

	private:

		bool mMainGameInitialized;
		bool mEnabled;
		bool mQuit;
		MainGame* mMainGame;
		TimeManager* mTimeManager;
		Context mContext;
	};
}

#endif
