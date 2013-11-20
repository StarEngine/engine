#pragma once

#include "../defines.h"
#include "../Graphics/Shader.h"
#include "../Helpers/Filepath.h"
#ifdef _WIN32
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#endif

namespace star
{
	class LoadScreen
	{
	public:
		LoadScreen(const tstring& filePath, const tstring& spriteName);
		virtual ~LoadScreen();

		virtual void Draw();
		virtual void Initialize();

	protected:
		void CreateSquare();

		Shader m_Shader;
		Filepath m_FilePath;
		tstring m_SpriteName;
		
		int32 m_Width;
		int32 m_Heigth;

		GLfloat m_Vertices[8];
		GLfloat m_UvCoords[8];

	private:
		LoadScreen(const LoadScreen &);
		LoadScreen(LoadScreen &&);
		LoadScreen & operator=(const LoadScreen &);
		LoadScreen & operator=(LoadScreen &&);
	};
}
