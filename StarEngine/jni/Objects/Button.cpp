#include "Button.h"
#include "../StarComponents.h"

enum ButtonInput
{
	LeftButtonPressed,
	LeftButtonReleased,
};

namespace star
{
	Button::Button(const tstring& assetFile, const tstring& spriteName, 
		bool isSpriteSheet, int32 heightSegments,  bool isHudElement)
		: Object()
		, m_OnClick(nullptr)
		, m_OnHover(nullptr)
		, m_OnLeave(nullptr)
		, m_bIsSpriteSheet(isSpriteSheet)
		, m_bIsHudElement(isHudElement)
		, m_bIsHovered(false)
		, m_FilePath(assetFile)
		, m_SpriteName(spriteName)
		, m_HeightSegments(heightSegments)
	{
		
	}


	Button::~Button(void)
	{
	}

	void Button::Initialize()
	{
		SpriteComponent* spriteSheetComp = nullptr;
		if(m_bIsSpriteSheet)
		{
			spriteSheetComp = new SpriteComponent(m_FilePath, 
				m_SpriteName,m_bIsHudElement,1,m_HeightSegments);
		}
		else
		{
			spriteSheetComp = new SpriteComponent(m_FilePath, 
				m_SpriteName,m_bIsHudElement);
		}
		AddComponent(spriteSheetComp);
		/*
		SpriteComponent::InitializeComponent();

		m_HitRegion = new GameHitRegion2D();
		m_pParentGameObject->AddChild(m_HitRegion);
		m_HitRegion->CanDraw(true);

		ID3D10Resource *resource;
		ID3D10Texture2D *tex2D;
		D3D10_TEXTURE2D_DESC tex2DDesc;
		m_SpriteInfo.pTexture->GetResource(&resource);
		tex2D = static_cast<ID3D10Texture2D*>(resource);
		tex2D->GetDesc(&tex2DDesc);

		m_Width = (int32)tex2DDesc.Width;
		//Set Dimensions after the button texture is loaded, otherwise we can't extract the width and height
		if(m_IsSpriteSheet)
		{
			m_Height = (int32)tex2DDesc.Height/3;

			//Only use these rectangle properties when the button texture is a spriteSheet
			m_NormalRect =	GameRectangle(	0,		0,									(int32)tex2DDesc.Width,	(int32)(tex2DDesc.Height / 3.0f));
			m_HoverRect =	GameRectangle(	0,		(int32)(tex2DDesc.Height / 3.0f),		(int32)tex2DDesc.Width,	2*(int32)(tex2DDesc.Height / 3.0f));
			m_PressedRect = GameRectangle(	0,		2*(int32)(tex2DDesc.Height / 3.0f),	(int32)tex2DDesc.Width,	(int32)(tex2DDesc.Height));

			m_SpriteInfo.DrawRect = GameRectangle::AsRect(m_NormalRect);
		}
		else
			m_Height = (int32)tex2DDesc.Height;

		m_HitRegion->SetDimensions(m_Width, m_Height);*/

	}

	void Button::Update(const Context& context)
	{/*
		SpriteComponent::Update(context);
		m_HitRegion->SetDimensions(m_Width, m_Height);
	*/

	
	}

	void Button::Draw(const Context& context)
	{/*
		SpriteComponent::Draw(context);

		POINT currMousePos = context.Input->GetMousePosition();
		if(!m_IsHovered)
		{
			if(m_HitRegion->HitTest(currMousePos.x, currMousePos.y))
			{
				m_IsHovered = true;

				OnHover();
				m_SpriteInfo.DrawRect = GameRectangle::AsRect(m_HoverRect);
			}
		}
		else
		{
			m_SpriteInfo.DrawRect = GameRectangle::AsRect(m_HoverRect);

			if(!m_HitRegion->HitTest(currMousePos.x, currMousePos.y))
			{
				m_IsHovered = false;

				OnLeave();
				m_SpriteInfo.DrawRect = GameRectangle::AsRect(m_NormalRect);

			}
			else if(context.Input->IsMouseButtonDown(VK_LBUTTON))
			{
				m_SpriteInfo.DrawRect = GameRectangle::AsRect(m_PressedRect);
			}
			else if(!context.Input->IsMouseButtonDown(VK_LBUTTON) && context.Input->IsMouseButtonDown(VK_LBUTTON,true))
			{
				OnClick();
				m_SpriteInfo.DrawRect = GameRectangle::AsRect(m_NormalRect);
			}
		}*/
	}

	void Button::OnClick()
	{
		if(m_OnClick) m_OnClick();
	}

	void Button::OnHover()
	{
		if(m_OnHover) m_OnHover();
	}

	void Button::OnLeave()
	{
		if(m_OnLeave) m_OnLeave();
	}

	void Button::SetOnHoverCallback(ButtonAction onHover)
	{
		m_OnHover = onHover;
	}
	void Button::SetOnClickCallback(ButtonAction onClick)
	{
		m_OnClick = onClick;
	}
	void Button::SetOnLeaveCallback(ButtonAction onLeave)
	{
		m_OnLeave = onLeave;
	}
}
