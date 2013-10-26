#include "TextComponent.h"
#include "../../Logger.h"
#include "../../Assets/TextureManager.h"
#include "../../Graphics/GraphicsManager.h"
#include "../TransformComponent.h"
#include "../../Objects/FreeCamera.h"
#include "../CameraComponent.h"
#include "../../Objects/Object.h"
#include "../../Graphics/SpriteBatch.h"
#include "../../Assets/FontManager.h"

namespace star
{
	TextComponent::TextComponent(const tstring& fileName,const tstring& tag, int fontSize)
		: BaseComponent()
		, m_FontSize(fontSize)
		, m_FileName(fileName)
		, m_Tag(tag)
		, m_TextColor()
		, m_MaxWidth()
		, m_Text()
	{
	}

	void TextComponent::InitializeComponent()
	{
		FontManager::GetInstance()->LoadFont(m_FileName,m_Tag,m_FontSize);
		m_MaxWidth = GraphicsManager::GetInstance()->GetWindowWidth();
	}

	TextComponent::~TextComponent()
	{

	}


	void TextComponent::Draw()
	{
		TextDesc desc;
		desc.Text = m_Text;
		desc.Fontname = m_Tag;
		desc.Position = m_pParentObject->GetTransform()->GetWorldPosition().pos2D();
		desc.TextColor = m_TextColor;
		desc.MaxWidth = m_MaxWidth;
		FontManager::GetInstance()->DrawText(desc);
	}

	void TextComponent::Update(const Context& context)
	{

	}

	void TextComponent::SetText(const tstring& text)
	{
		m_Text = text;
	}

	const tstring& TextComponent::GetText() const
	{
		return m_Text;
	}

	void TextComponent::SetColor(const Color& color)
	{
		m_TextColor = color;
	}

	const Color& TextComponent::GetColor() const
	{
		return m_TextColor;
	}
}
