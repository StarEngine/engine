#pragma once

#include <map>
#include "../defines.h"
#include <memory>

#ifdef ANDROID
#include <android_native_app_glue.h>
#endif

namespace star
{
	struct Context;
	class BaseScene;

	class SceneManager
	{
	public:
		~SceneManager();

		static std::shared_ptr<SceneManager> GetInstance();

		BaseScene* GetActiveScene();
		BaseScene* GetScene(const tstring & name);
		bool SetActiveScene(const tstring & name);
		bool AddScene(const tstring & name, BaseScene* scene);
		bool RemoveScene(const tstring & name);

		status Update(const Context& context);
		status Draw();

#ifdef ANDROID
		void processActivityEvent(int32 pCommand, android_app* pApplication);
		int32 processInputEvent(AInputEvent* pEvent);
		void Activate();
		void DeActivate();

	private:
		android_app* mApplicationPtr;
#endif
	private:
		static std::shared_ptr<SceneManager> m_pSceneManager;

		BaseScene	*m_ActiveScene, 
					*m_NewActiveScene;

		std::map<tstring, BaseScene*> m_SceneList;
		bool m_bSwitchingScene,
			 m_bInitialized,
			 m_bDestroyRequested;
		tstring m_CurrentSceneName;

		bool InitializeCurScene(const Context& context);

		SceneManager();

		SceneManager(const SceneManager& yRef);
		SceneManager(SceneManager&& yRef);
		SceneManager& operator=(const SceneManager& yRef);
	};
}
