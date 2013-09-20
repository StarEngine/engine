#include "BaseScene.h"
#include <map>

namespace star 
{
	class SceneManager
	{
	public:
		virtual ~SceneManager(void);

		static SceneManager* GetInstance();

		BaseScene* GetActiveScene(){ return m_ActiveScene; }
		BaseScene* GetScene(const tstring & name);
		bool SetActiveScene(const tstring & name);
		bool AddScene(const tstring & name, BaseScene* scene);
		//bool RemoveScene(const char* name){};

		status Update(float deltatime);
		status Draw();

	#ifndef _WIN32
		void ProcessActivityEvent(int32_t pCommand){};
	#endif
	/*
	protected:
		void Activate();
		void Deactivate();

		void ProcessActivityEvent(int32_t pCommand);
	*/
	private:
		//Data Members
		static SceneManager* m_pSceneManager;

		BaseScene	*m_ActiveScene, 
					*m_NewActiveScene;
		std::map<tstring,BaseScene*> m_SceneList;
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