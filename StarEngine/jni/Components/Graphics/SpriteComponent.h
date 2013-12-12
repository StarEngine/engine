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
			, textureID()
			, transformPtr(nullptr)
			, colorMultiplier(Color::White)
			, bIsHud(false)
		{}

		vec2 vertices;
		vec4 uvCoords;
		uint32 textureID;
		TransformComponent* transformPtr;
		Color colorMultiplier;
		bool bIsHud;
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
		virtual void CreateUVCoords();
		void SetUVCoords(const vec4& coords);
		virtual void FillSpriteInfo();

		uint32	m_WidthSegments,
				m_HeightSegments, 
				m_CurrentWidthSegment,
				m_CurrentHeightSegment;

	private:

		Filepath m_FilePath;
		tstring m_SpriteName;
		
		SpriteInfo* m_SpriteInfo;

		SpriteComponent(const SpriteComponent &);
		SpriteComponent(SpriteComponent &&);
		SpriteComponent& operator=(const SpriteComponent &);
		SpriteComponent& operator=(SpriteComponent &&);
	};
}
