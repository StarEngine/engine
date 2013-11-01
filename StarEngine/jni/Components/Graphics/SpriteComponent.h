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
		SpriteComponent(const tstring& filepath, const tstring& spriteName, bool bIsHUDElement = false, int widthSegments = 1, int heightSegments = 1);
		virtual ~SpriteComponent();

		void Draw();
		virtual void Update(const Context& context) {};

		const tstring& GetFilePath() const;
		const tstring& GetName() const;
		int32 GetWidth() const;
		int32 GetHeight() const;
		std::vector<GLfloat> GetVertices() const;
		std::vector<GLfloat> GetUVCoords() const;
		
		void SetCurrentSegment(int widthSegment, int heightSegment);

	protected:
		virtual void InitializeComponent();
		virtual void CreateVertices();
		virtual void CreateIndices();

		GLfloat m_Vertices[12];
		GLfloat m_UvCoords[8];
		int32 m_Width, m_WidthSegments, m_CurrentWidthSegment;
		int32 m_Heigth, m_HeightSegments, m_CurrentHeightSegment;
	private:
		
		mat4x4 InverseMatrix(const mat4x4& matrix);

		Shader m_Shader;
		Filepath m_FilePath;
		tstring m_SpriteName;
		bool m_bIsHudElement;
		
		

		

		SpriteComponent(const SpriteComponent &);
		SpriteComponent(SpriteComponent &&);
		SpriteComponent & operator=(const SpriteComponent &);
	};
}
