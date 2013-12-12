#include "SpriteComponent.h"
#include "../../Logger.h"
#include "../../Assets/TextureManager.h"
#include "../TransformComponent.h"
#include "../../Graphics/SpriteBatch.h"

namespace star
{
	SpriteComponent::SpriteComponent(
		const tstring& filepath,
		const tstring& spriteName,
		uint32 widthSegments,
		uint32 heightSegments
		)
		: BaseComponent()
		, m_WidthSegments(widthSegments)
		, m_HeightSegments(heightSegments)
		, m_CurrentWidthSegment(0)
		, m_CurrentHeightSegment(0)
		, m_Width(0)
		, m_Height(0)
		, m_FilePath(filepath)
		, m_SpriteName(spriteName)
		, m_SpriteInfo(nullptr)
	{
		m_SpriteInfo = new SpriteInfo();
	}

	void SpriteComponent::InitializeComponent()
	{	
		TextureManager::GetInstance()->LoadTexture(
			m_FilePath.GetAssetsPath(),
			m_SpriteName
			);

		m_Width = TextureManager::GetInstance()->
			GetTextureDimensions(m_SpriteName).x /
			m_WidthSegments;
		m_Height =  TextureManager::GetInstance()->
			GetTextureDimensions(m_SpriteName).y /
			m_HeightSegments;

		CreateUVCoords();
		FillSpriteInfo();
	}

	void SpriteComponent::FillSpriteInfo()
	{
		m_SpriteInfo->textureID = 
			TextureManager::GetInstance()->GetTextureID(m_SpriteName);
		m_SpriteInfo->vertices = vec2(m_Width, m_Height);		
	}

	SpriteComponent::~SpriteComponent()
	{
		delete m_SpriteInfo;
	}

	void SpriteComponent::CreateUVCoords()
	{
		float32 startX =
			float32(m_CurrentWidthSegment) /
			float32(m_WidthSegments);
		float32 endX = 1.0f / m_WidthSegments;
		float32 startY =
			float32(m_CurrentHeightSegment) /
			float32(m_HeightSegments);
		float32 endY = 1.0f / m_HeightSegments;

		SetUVCoords(vec4(startX, startY, endX, endY));
	}

	void SpriteComponent::SetUVCoords(const vec4& coords)
	{
		m_SpriteInfo->uvCoords = coords;
	}

	void SpriteComponent::Draw()
	{
		m_SpriteInfo->transformPtr = GetTransform();
		SpriteBatch::GetInstance()->AddSpriteToQueue(m_SpriteInfo);
	}

	void SpriteComponent::Update(const Context & context)
	{
		//[COMMENT] Temp hotfix!
#ifdef ANDROID
		FillSpriteInfo();
#endif
	}
	
	bool SpriteComponent::CheckCulling(
		float left,
		float right,
		float top,
		float bottom
		) const
	{
		//Always draw hudObjects
		if(m_SpriteInfo->bIsHud)
		{
			return true;
		}

		float32 spriteWidth, spriteHeight;

		pos objectPos = GetTransform()->GetWorldPosition();
		
		if(m_SpriteInfo->bIsHud)
		{
			objectPos.x += left;
			objectPos.y += bottom;
		}

		spriteWidth = float32(GetWidth()) * GetTransform()->GetWorldScale().x;
		spriteHeight = float32(GetHeight()) * GetTransform()->GetWorldScale().y;
		float32 objRight = objectPos.x + spriteWidth;
		float32 objTop = objectPos.y + spriteHeight;

		return
			(objRight >= left && objectPos.x <= right)
			&&
			(objTop >= bottom && objectPos.y <= top);
	}

	const tstring& SpriteComponent::GetFilePath() const
	{
		return m_FilePath.GetPath();
	}

	const tstring& SpriteComponent::GetName() const
	{
		return m_SpriteName;
	}

	int32 SpriteComponent::GetWidth() const
	{
		return m_Width;
	}

	int32 SpriteComponent::GetHeight() const
	{
		return m_Height; 
	}

	void SpriteComponent::SetCurrentSegment(uint32 widthSegment, uint32 heightSegment)
	{
		m_CurrentWidthSegment = widthSegment;
		m_CurrentHeightSegment = m_HeightSegments - heightSegment - 1;
		CreateUVCoords();
	}

	void SpriteComponent::SetColorMultiplier(const Color & color)
	{
		m_SpriteInfo->colorMultiplier = color;
	}

	void SpriteComponent::SetHUDOptionEnabled(bool enabled)
	{
		m_SpriteInfo->bIsHud = enabled;
	}

	bool SpriteComponent::IsHUDOptionEnabled() const
	{
		return m_SpriteInfo->bIsHud;
	}

	void SpriteComponent::SetTexture(
		const tstring& filepath,
		const tstring& spriteName,
		uint32 widthSegments,
		uint32 heightSegments
		)
	{
		m_Width = 0;
		m_WidthSegments = widthSegments;
		m_CurrentWidthSegment = 0;
		m_Height = 0;
		m_HeightSegments = heightSegments;
		m_CurrentHeightSegment = 0;
		m_FilePath = Filepath(filepath);
		m_SpriteName = spriteName;

		TextureManager::GetInstance()->LoadTexture(m_FilePath.GetAssetsPath(),m_SpriteName);
		m_Width = TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).x / m_WidthSegments;
		m_Height =  TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).y / m_HeightSegments;
		
		CreateUVCoords();
		FillSpriteInfo();
	}

}
