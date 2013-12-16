#include "../Logger.h"
#include "../Context.h"
#include "BaseScene.h"
#include "../Objects/Object.h"
#include "../Graphics/GraphicsManager.h"
#include "../Graphics/TextureManager.h"
#include "../Sound/AudioManager.h"
#include "../Graphics/SpriteBatch.h"
#include "../Input/InputManager.h"
#include "../Graphics/UI/UICursor.h"
#include "../Graphics/UI/UIBaseCursor.h"

namespace star
{
	template <typename T>
	T* SceneManager::GetScene(const tstring & name)
	{
		T* scene = dynamic_cast<T*>(GetScene(name));
		Logger::GetInstance()->Log(!scene,
			_T("SceneManager::GetScene<T>: Dynamic casting of scene '")
				+ name + _T("' failed."));
		return scene;
	}
}
