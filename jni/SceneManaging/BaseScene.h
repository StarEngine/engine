/*
 * EventLoop.h
 *
 *  Created on: 19-sep.-2013
 *      Author: Simon Vanhauwaert
 */

#ifndef _BASE_SCENE_
#define _BASE_SCENE_

#include "../defines.h"

class BaseScene
{
public:

	BaseScene(tstring Name);
	virtual ~BaseScene(){}

	virtual status onActivate(){return STATUS_OK;};
	virtual void onDeactivate(){};
	virtual status onStep(){return STATUS_OK;};

	virtual void onStart() {};
	virtual void onResume() {};
	virtual void onPause() {};
	virtual void onStop() {};
	virtual void onDestroy() {};

	virtual void onSaveState(void** pData,size_t* pSize) {};
	virtual void onConfigurationChanged() {};
	virtual void onLowMemory() {};

	virtual void onCreateWindow() {};
	virtual void onDestroyWindow() {};
	virtual void onGainFocus() {};
	virtual void onLostFocus() {};

	tstring getName(){return mName;}
	bool IsInitialized(){return bInitialized;}

private:
	tstring mName;
	bool bInitialized;
};


#endif
