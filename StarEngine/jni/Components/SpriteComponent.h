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
		virtual ~SpriteComponent();

		void Draw();
		virtual void Update(const Context& context) {};
	protected:
		virtual void InitializeComponent();

		GLfloat m_UvCoords[8];
	private:
		void CreateSquare();
		mat4x4 InverseMatrix(const mat4x4& matrix);

		Shader m_Shader;
		tstring m_FilePath;
		tstring m_SpriteName;
		
		int32 m_Width;
		int32 m_Heigth;

		GLfloat m_Vertices[12];

		SpriteComponent(const SpriteComponent &);
		SpriteComponent(SpriteComponent &&);
		SpriteComponent & operator=(const SpriteComponent &);
	};
}
