#pragma once

#include "../../defines.h"
#include "../../Graphics/Shader.h"
#include "../BaseComponent.h"
#include "../../Helpers/Filepath.h"
#include "../../Graphics/SpriteInfo.h"


namespace star
{
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
		void SetCurrentHorizontalSegment(uint32 segment);
		void SetCurrentVerticalSegment(uint32 segment);

		void SetTexture(const tstring& filepath, const tstring& spriteName, uint32 widthSegments = 1, uint32 heightSegments = 1);

	protected:
		virtual void InitializeComponent();
		virtual void CreateVertices();
		virtual void CreateUVCoords();
		virtual void FillSpriteInfo();

		float32 m_Vertices[12];
		float32 m_UvCoords[8];

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
