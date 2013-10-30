#include "FontManager.h"
#include "../Helpers/Filepath.h"
#include "../Logger.h"
#include "../Context.h"
#include "../Graphics/GraphicsManager.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/BaseScene.h"
#include "../Components/CameraComponent.h"
#include "../Objects/FreeCamera.h"
#include "../Graphics/ScaleSystem.h"

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
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Font Manager : Could not initialize FreeType library"));
		}

#ifdef _WIN32
		Filepath texshaderVertex(_T("WinShaders/"), _T("Font_Shader.vert"));
		Filepath texshaderFrag(_T("WinShaders/"), _T("Font_Shader.frag"));
#else
		Filepath texshaderVertex(_T("AndroidShaders/"), _T("Font_Shader.vert"));
		Filepath texshaderFrag(_T("AndroidShaders/"), _T("Font_Shader.frag"));

#endif
		if(!m_Shader.Init(texshaderVertex.GetFullPath(),texshaderFrag.GetFullPath()))
		{
			Logger::GetInstance()->Log(star::LogLevel::Info, _T("Font Manager : Making Shader Failed"));
		}

		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Font Manager : Initialized FreeType library"));
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
			return (false);
		}

		
		/*if(std::find(mPathList.begin(), mPathList.end(), path)!=mPathList.end())
		{
			return (false);
		}*/

		if(mFontList.find(name) != mFontList.end())
		{
			return (false);
		}

		star::Filepath filepath(_T("Fonts/"),path);

		Font tempfont;
		if(tempfont.Init(filepath.GetFullPath(),size,mLibrary))
		{
			mFontList[name] = tempfont;

		}
		else
		{
			return (false);
		}
		
		//mPathList.push_back(path);

		return (true);
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

	mat4x4 FontManager::InverseMatrix(const mat4x4& matrix)
	{
		float x1, y1, z1, w1,
			x2, y2, z2, w2,
			x3, y3, z3, w3,
			x4, y4, z4, w4;

		x1 = matrix[0][0];
		x2 = matrix[1][0];
		x3 = matrix[2][0];
		x4 = matrix[3][0];

		y1 = matrix[0][1];
		y2 = matrix[1][1];
		y3 = matrix[2][1];
		y4 = matrix[3][1];

		z1 = matrix[0][2];
		z2 = matrix[1][2];
		z3 = matrix[2][2];
		z4 = matrix[3][2];

		w1 = matrix[0][3];
		w2 = matrix[1][3];
		w3 = matrix[2][3];
		w4 = matrix[3][3];

		mat4x4 inverseMatrix
			(
			x1, y1, z1, x4,
			x2, y2, z2, y4,
			x3, y3, z3, z4,
			w1, w2, w3, w4
			);

		return inverseMatrix;
	}

	void FontManager::SplitIntoLines(std::vector<std::string> & list, const std::string &string )
	{
		std::stringstream stream(string);
		std::string line;
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
