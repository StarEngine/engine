#pragma once

#include "../../defines.h"
#include "../../Graphics/Shader.h"
#include "../BaseComponent.h"
#include "../../Helpers/Filepath.h"
#include <vector>
#ifdef ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#endif

namespace star
{
	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(const tstring& filepath, const tstring& spriteName);
		virtual ~SpriteComponent();

		void Draw();
		virtual void Update(const Context& context) {};

		const tstring& GetFilePath() const;
		const tstring& GetName() const;
		int32 GetWidth() const;
		int32 GetHeight() const;
		std::vector<GLfloat> GetVertices() const;
		std::vector<GLfloat> GetUVCoords() const;

	protected:
		virtual void InitializeComponent();
		virtual void CreateVertices();
		virtual void CreateIndices();

		GLfloat m_Vertices[12];
		GLfloat m_UvCoords[8];
		int32 m_Width;
		int32 m_Heigth;
	private:
		
		mat4x4 InverseMatrix(const mat4x4& matrix);

		Shader m_Shader;
		Filepath m_FilePath;
		tstring m_SpriteName;
		
		

		

		SpriteComponent(const SpriteComponent &);
		SpriteComponent(SpriteComponent &&);
		SpriteComponent & operator=(const SpriteComponent &);
	};
}
