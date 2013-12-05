#include "FontManager.h"
#include "../Helpers/Filepath.h"
#include "../Logger.h"
#include "../Context.h"
#include "../Graphics/GraphicsManager.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/BaseScene.h"
#include "../Components/CameraComponent.h"
#include "../Objects/FreeCamera.h"
#include "../Helpers/Math.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif

namespace star 
{
	FontManager * FontManager::mFontManager = nullptr;


	FontManager * FontManager::GetInstance()
	{
		if(mFontManager == nullptr)
		{
			mFontManager = new FontManager();
		}
		return (mFontManager);
	}

	FontManager::FontManager():
		mLibrary(0),
		mFontPath(_T("Fonts/"))
	{
		auto error = FT_Init_FreeType(&mLibrary);
		if(error)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Font Manager : Could not initialize FreeType library"),
				STARENGINE_LOG_TAG);
		}

		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Font Manager : Initialized FreeType library"),
			STARENGINE_LOG_TAG);
	}

	FontManager::~FontManager()
	{

	}

	void FontManager::EraseFonts()
	{
		for(const auto& font : mFontList)
		{
			font.second->DeleteFont();
			delete font.second;
		}
		mFontList.clear();
		
		FT_Done_FreeType(mLibrary);
	}

	bool FontManager::LoadFont(const tstring& path, const tstring& name, uint32 size)
	{
		if(mFontList.find(name) != mFontList.end())
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Info,
				_T("Font Manager : Font ") + name + _T(" already exist, using that"),
				STARENGINE_LOG_TAG);
			return true;
		}

		star::Filepath filepath(mFontPath, path);

		Font* tempFont = new Font();
		if(tempFont->Init(filepath.GetAssetsPath(), size, mLibrary))
		{
			mFontList[name] = tempFont;

		}
		else
		{
			delete tempFont;
			return false;
		}
		return true;
	}

	bool FontManager::DeleteFont(const tstring& name)
	{
		auto it = mFontList.find(name);
		if(it != mFontList.end())
		{
			mFontList.erase(it);
			return (true);
		}
		return (false);
	}
	
	void FontManager::SplitIntoLines(std::vector<sstring> & list, const sstring &string )
	{
		sstringstream stream(string);
		sstring line;
		while (std::getline(stream,line))
		{
			list.push_back(line);
		}
	}

	void FontManager::SetFontPath(const tstring & path)
	{
		mFontPath = path;
	}

	const tstring & FontManager::GetFontPath() const
	{
		return mFontPath;
	}

	const Font* FontManager::GetFont(const tstring& name)
	{
		Logger::GetInstance()->Log(mFontList.find(name) != mFontList.end(),_T("No such font"), STARENGINE_LOG_TAG);
		return mFontList[name];
	}
}
