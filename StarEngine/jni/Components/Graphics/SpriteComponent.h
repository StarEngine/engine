#pragma once

#include "../../defines.h"
#include "../../Graphics/Shader.h"
#include "../BaseComponent.h"
#include "../../Helpers/Filepath.h"
#include "../../Graphics/Color.h"
#include <vector>

namespace star
{
	struct SpriteInfo
	{
		SpriteInfo()
			: vertices()
			, uvCoords()
			, spriteName(EMPTY_STRING)
			, transform()
			, colorMultiplier(Color::White)
			, bIsHUD(false)
		{}


		std::vector<GLfloat> vertices;
		std::vector<GLfloat> uvCoords;
		tstring spriteName;
		mat4 transform;
		Color colorMultiplier;
		bool bIsHUD;
	};

	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(
			const tstring& filepath,
			const tstring& spriteName,
			uint32 widthSegments = 1,
			uint32 heightSegments = 1
			);

		virtual ~SpriteComponent();

		void Draw();
		virtual void Update(const Context& context);

		virtual bool CheckCulling(
			float left,
			float right,
			float top,
			float bottom
			) const;

		const tstring& GetFilePath() const;
		const tstring& GetName() const;
		virtual int32 GetWidth() const;
		virtual int32 GetHeight() const;
		
		void SetCurrentSegment(uint32 widthSegment, uint32 heightSegment);
		void SetColorMultiplier(const Color & color);

		void SetHUDOptionEnabled(bool enabled);
		bool IsHUDOptionEnabled() const;

		void SetTexture(
			const tstring& filepath,
			const tstring& spriteName,
			uint32 widthSegments = 1,
			uint32 heightSegments = 1
			);

	protected:
		virtual void InitializeComponent();
		virtual void CreateVertices();
		virtual void CreateUVCoords();
		void SetUVCoords(const vec4& coords);
		virtual void FillSpriteInfo();

		static const int VERTEX_AMOUNT = 12;
		static const int UV_AMOUNT = 8;

		float32 m_Vertices[VERTEX_AMOUNT];
		float32 m_UvCoords[UV_AMOUNT];

		uint32	m_WidthSegments,
				m_HeightSegments, 
				m_CurrentWidthSegment,
				m_CurrentHeightSegment;

		int32 m_Width, m_Height;

	private:

		Filepath m_FilePath;
		tstring m_SpriteName;
		bool m_bIsHudElement;
		
		SpriteInfo m_SpriteInfo;

		SpriteComponent(const SpriteComponent &);
		SpriteComponent(SpriteComponent &&);
		SpriteComponent& operator=(const SpriteComponent &);
		SpriteComponent& operator=(SpriteComponent &&);
	};
}
