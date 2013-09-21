#pragma once

#include "BaseScene.h"
#include "../Context.h"
#include <map>

#ifndef _WIN32
#include <android_native_app_glue.h>
#endif
namespace star
{
	class SceneManager
	{
	public:
		virtual ~SceneManager(void);

		static SceneManager* GetInstance();

		star::BaseScene* GetActiveScene(){ return m_ActiveScene; }
		star::BaseScene* GetScene(const tstring & name);
		bool SetActiveScene(const tstring & name);
		bool AddScene(const tstring & name, star::BaseScene* scene);
		bool RemoveScene(tstring name);

		status Update(Context& context);
		status Draw();

	#ifndef _WIN32
		void processActivityEvent(int32 pCommand, android_app* pApplication);
	protected:
		void Activate();
		void DeActivate();

		android_app* mApplicationPtr;
#endif
	private:
		//Data Members
		static SceneManager* m_pSceneManager;

		star::BaseScene	*m_ActiveScene, 
						*m_NewActiveScene;

		std::map<tstring,star::BaseScene*> m_SceneList;
		bool m_bSwitchingScene,m_bInitialized;
		tstring m_CurrentSceneName;

		//Private Functions
		//bool InitializeCurScene(){};
		//static void activityCallback(android_app* pApplication, int32_t pCommand);
		SceneManager(void);

		//disabling default copy constructor
		SceneManager(const SceneManager& yRef);
		SceneManager& operator=(const SceneManager& yRef);
	};
}
