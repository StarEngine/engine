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
		mLibrary(0)
	{
		auto error = FT_Init_FreeType(&mLibrary);
		if(error)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Font Manager : Could not initialize FreeType library"));
		}

#ifdef _WIN32
		tstring vShader(_T("WinShaders/Font_Shader.vert")),
				fShader(_T("WinShaders/Font_Shader.frag"));
#else
		tstring vShader(_T("AndroidShaders/Font_Shader.vert")),
				fShader(_T("AndroidShaders/Font_Shader.frag"));
#endif
		if(!m_Shader.Init(vShader, fShader))
		{
			Logger::GetInstance()->Log(star::LogLevel::Error,
				_T("Font Manager : Making Shader Failed"));
		}

		star::Logger::GetInstance()->Log(star::LogLevel::Info,
			_T("Font Manager : Initialized FreeType library"));
	}

	void FontManager::EraseFonts()
	{
		auto iter = mFontList.begin();
		for(iter; iter != mFontList.end(); ++iter)
		{
			iter->second.DeleteFont();
		}
		mFontList.clear();
		mPathList.clear();
		
		FT_Done_FreeType(mLibrary);
	}

	bool FontManager::LoadFont(const tstring& path, const tstring& name, int32 size)
	{
		if(mFontManager == nullptr)
		{
			return false;
		}

		if(mFontList.find(name) != mFontList.end())
		{
			return false;
		}

		star::Filepath filepath(_T("Fonts/"),path);

		Font tempfont;
		if(tempfont.Init(filepath.GetAssetsPath(),size,mLibrary))
		{
			mFontList[name] = tempfont;

		}
		else
		{
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
		while (std::getline(stream,line)){
			list.push_back(line);
		}
	}

	const Font& FontManager::GetFont( const tstring& name )
	{
		ASSERT(mFontList.find(name) != mFontList.end(),_T("No such font"));
		return mFontList[name];
	}
}
