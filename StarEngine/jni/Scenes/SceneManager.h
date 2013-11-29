#pragma once

#include "../defines.h"
#include "../Helpers/Stopwatch.h"
#include <memory>
#include <map>
#include <vector>

#ifdef ANDROID
#include <android_native_app_glue.h>
#endif

namespace star
{
	struct Context;
	class BaseScene;
	class UIBaseCursor;
	class Object;

	class SceneManager final
	{
	public:
		~SceneManager();

		static SceneManager * GetInstance();

		BaseScene* GetActiveScene();
		BaseScene* GetScene(const tstring & name);
		bool SetActiveScene(const tstring & name);
		bool AddScene(const tstring & name, BaseScene* scene);
		bool RemoveScene(const tstring & name);

		void Update(const Context& context);
		void Draw();

		void DrawDefaultCursor();
		void UpdateDefaultCursor(const Context & context);

		void SetDefaultCursor(UIBaseCursor * cursor);
		void UnsetDefaultCursor();

		void SetDefaultCursorState(const tstring & state);
		void SetDefaultCursorLocked(bool locked);
		bool IsDefaultCursorLocked() const;
		bool IsDefaultCursorDefined() const;

		void SetSystemCursorHiddenByDefault(bool hidden);

		std::shared_ptr<Stopwatch> GetStopwatch() const;

#ifdef ANDROID
		void processActivityEvent(int32 pCommand, android_app* pApplication);
		int32 processInputEvent(AInputEvent* pEvent);

	private:
		android_app* mApplicationPtr;
#endif
	private:
		static SceneManager * m_pSceneManager;

		BaseScene	*m_ActiveScene, 
					*m_NewActiveScene;

		std::shared_ptr<Stopwatch> m_Stopwatch;

		std::vector<BaseScene*> m_GarbageList;
		std::map<tstring, BaseScene*> m_SceneList;
		bool m_bSwitchingScene,
			 m_bInitialized,
			 m_bDestroyRequested,
			 m_bCursorHiddenByDefault,
			 m_bCustomCursorDefined;
		tstring m_CurrentSceneName;
		UIBaseCursor *m_pDefaultCursor;

		bool InitializeCurScene(const Context& context);

		SceneManager();
		void CreateDefaultCursor();

		SceneManager(const SceneManager& yRef);
		SceneManager(SceneManager&& yRef);
		SceneManager& operator=(const SceneManager& yRef);
		SceneManager& operator=(SceneManager&& yRef);
	};
}
