#pragma once

#include "../defines.h"
#include "../Shaders/Shader.h"
#include "BaseComponent.h"
#ifdef _WIN32
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#endif

namespace star
{
	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(const tstring& filePath, const tstring& spriteName);
		~SpriteComponent();

		void Draw();

	protected:
		virtual void InitializeComponent();
	private:
		void CreateSquare();

		Shader m_Shader;
		tstring m_FilePath;
		tstring m_SpriteName;
		

		GLfloat m_Vertices[12];
		GLfloat m_UvCoords[8];

		SpriteComponent(const SpriteComponent &);
		SpriteComponent(SpriteComponent &&);
		SpriteComponent & operator=(const SpriteComponent &);
	};
}
