/*
 * EventLoop.h
 *
 *  Created on: 19-sep.-2013
 *      Author: Simon Vanhauwaert
 */

#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include "BaseScene.h"
#include "Logger.h"
#include <map>

using namespace std;

class SceneManager
{
	public:

		virtual ~SceneManager(void);

		static SceneManager* GetInstance();

		BaseScene* GetActiveScene(){return m_ActiveScene;}
		BaseScene* GetScene(tstring name);
		bool SetActiveScene(tstring name);
		bool AddScene(tstring name,BaseScene* scene);
		//bool RemoveScene(const char* name){};

		status Update(float deltatime){return STATUS_OK;};
		status Draw(){return STATUS_OK;};

#ifndef _WIN32
		void processActivityEvent(int32_t pCommand){};
#endif
/*	protected:
		void activate();
		void deactivate();

		void processActivityEvent(int32_t pCommand);

	private:
			static void activityCallback(android_app* pApplication, int32_t pCommand);
*/


	private:
		//Data Members
		static SceneManager* m_pSceneManager;
		static const int32 MAX_SCENES;

		BaseScene* m_ActiveScene;
		BaseScene* m_NewActiveScene;
		map<tstring,BaseScene*> m_SceneList;
		bool m_bSwitchingScene;
		bool m_bInitialized;
		tstring CurrentSceneName;

		//Private Functions
		//bool InitializeCurScene(){};
		SceneManager(void);


		//disabling default copy constructor
		SceneManager(const SceneManager& yRef);
		SceneManager& operator=(const SceneManager& yRef);

};


#endif
