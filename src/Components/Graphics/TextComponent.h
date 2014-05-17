#pragma once

#include "../BaseComponent.h"
#include "../../defines.h"
#include "../../Graphics/Color.h"
#include <vector>

namespace star
{
	class Font;

	/// <summary>
	/// Information of a text element. 
	/// Gets sent to the <see cref="SpriteBatch"> to process it correctly.
	/// Contains the font, a pointer to the <see cref="TransformComponent">,
	/// color multiplier and a bool to check if the sprite is a HUD element.
	/// also holds an offset for every letter, the vertical spacing,
	/// the text and the text height.
	/// </summary>
	struct TextInfo
	{
		TextInfo()
			: font(nullptr)
			, transformPtr(nullptr)
			, colorMultiplier(Color::White)
			, bIsHud(false)
			, horizontalTextOffset()
			, verticalSpacing(10)
			, text()
			, textHeight()
		{}
		const Font* font;
		TransformComponent* transformPtr;
		Color colorMultiplier; 
		bool bIsHud;	
		std::vector<int32> horizontalTextOffset;
		int32 verticalSpacing;
		tstring text;	
		int32 textHeight;
	};

	/// <summary>
	/// Graphics component used to draw text.
	/// </summary>
	class TextComponent : public BaseComponent
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="TextComponent"/> class.
		/// Use this Constructor if you have already loaded a font with this fontName
		/// Through the <see cref="FontManager"/>
		/// </summary>
		/// <param name="fontName">Name of the font.</param>
		TextComponent(
			const tstring& fontName
			);

		/// <summary>
		/// Initializes a new instance of the <see cref="TextComponent"/> class.
		/// Use this Constructor if you have not loaded the font with this fontName yet.
		/// </summary>
		/// <param name="fontPath">
		/// Path to the font, starting from the path defined in <see cref="DirectoryMode::assets"/>.
		/// </param>
		/// <param name="fontName">Name of the font.</param>
		/// <param name="fontSize">Size of the font.</param>
		TextComponent(
			const tstring& fontPath,
			const tstring& fontName,
			uint32 fontSize
			);

		/// <summary>
		/// Finalizes an instance of the <see cref="TextComponent"/> class.
		/// </summary>
		virtual ~TextComponent();

		/// <summary>
		/// Draws this instance.
		/// </summary>
		void Draw();

		/// <summary>
		/// Updates this instance.
		/// </summary>
		/// <param name="context"><see cref="Context"/> containing usefull information.</param>
		virtual void Update(const Context& context);

		/// <summary>
		/// Culling check. The object will not be drawn if it is out of screen.
		/// </summary>
		/// <param name="left">Left of the screen</param>
		/// <param name="right">Right of the screen</param>
		/// <param name="top">Top of the screen</param>
		/// <param name="bottom">Bottom of the screen</param>
		/// <returns>true if the object should be culled</returns>
		virtual bool CheckCulling(
			float32 left,
			float32 right,
			float32 top,
			float32 bottom
			) const;

		/// <summary>
		/// Sets the text.
		/// </summary>
		/// <param name="text">The text.</param>
		void SetText(const tstring& text);

		/// <summary>
		/// Gets the text.
		/// </summary>
		/// <returns>The text.</returns>
		const tstring& GetText() const;

		/// <summary>
		/// Sets the color.
		/// </summary>
		/// <param name="color">The color.</param>
		/// <seealso cref="Color"/>
		void SetColor(const Color& color);
		/// <summary>
		/// Gets the color.
		/// </summary>
		/// <returns>The color.</returns>
		const Color& GetColor() const;
	
		/// <summary>
		/// Sets and toggles the wrap width.
		/// Default set to -1, Set width to -1 to disable wrapping
		/// </summary>
		/// <param name="width">The width. Set to -1 to disable wrapping</param>
		void SetWrapWidth(int32 width);
		/// <summary>
		/// Gets the wrap width.
		/// </summary>
		/// <returns>The wrap width. If width is -1, wrapping is disabled.</returns>
		int32 GetWrapWidth() const;

		/// <summary>
		/// Sets the space between 2 lines.
		/// </summary>
		/// <param name="spacing">The spacing.</param>
		void SetVerticalSpacing(uint32 spacing);

		/// <summary>
		/// Sets this Text as a HUD element
		/// </summary>
		/// <param name="enabled">True to set this as HUD element</param>
		void SetHUDOptionEnabled(bool enabled);

		/// <summary>
		/// Determines whether this Text is a HUD element.
		/// </summary>
		/// <returns>True if HUD element</returns>
		bool IsHUDOptionEnabled() const;

		/// <summary>
		/// Aligns the text as left.
		/// </summary>
		void AlignTextLeft();
		/// <summary>
		/// Aligns the text as center.
		/// </summary>
		void AlignTextCenter();
		/// <summary>
		/// Aligns the text as right.
		/// </summary>
		void AlignTextRight();
		
	protected:
		enum class HorizontalAlignment : byte
		{
			left = 0,
			center,
			right
		};

		/// <summary>
		/// Initializes the component.
		/// </summary>
		virtual void InitializeComponent();

		/// <summary>
		/// Calculates the text dimensions.
		/// </summary>
		void CalculateTextDimensions();
		/// <summary>
		/// Calculates the wrapped text dimensions.
		/// </summary>
		/// <param name="lines">number of lines.</param>
		void CalculateWrappedTextDimensions(uint8 lines);

		/// <summary>
		/// Calculates the height of the text.
		/// </summary>
		void CalculateTextHeight();
		/// <summary>
		/// Cleans up the text.
		/// Converts all \\t characters to a set amount of spaces
		/// defined in <see cref="TAB"/>.
		/// Also calls CalculateHorizontalTextOffset() 
		/// </summary>
		/// <param name="str">The string.</param>
		void CleanUpText(const tstring & str);

		/// <summary>
		/// Calculates the horizontal text offset.
		/// </summary>
		void CalculateHorizontalTextOffset();
		/// <summary>
		/// Gets the longest line.
		/// </summary>
		/// <param name="str">The text.</param>
		/// <returns></returns>
		int32 GetLongestLine(const tstring & str);

		/// <summary>
		/// Fills the text information struct, to send to the <see cref="SpriteBatch"/>
		/// </summary>
		virtual void FillTextInfo();
	
	private:
		uint32	m_FontSize,
				m_StringLength;

		int32 m_WrapWidth;

		tstring m_FileName,
				m_OrigText,
				m_EditText;

		Color m_TextColor;
		TextInfo* m_TextInfo;
		const Font* m_Font;
		HorizontalAlignment m_TextAlignment;

		/// <summary>
		/// Calculates the wrapping.
		/// </summary>
		/// <param name="stringIn">The string in.</param>
		/// <param name="wrapWidth">Width of the wrap.</param>
		/// <returns>a new string, wrapped correctly</returns>
		tstring CheckWrapping(
			const tstring& stringIn,
			int32 wrapWidth
			);

		/// <summary>
		/// Splits the string.
		/// </summary>
		/// <param name="words">The words.</param>
		/// <param name="str">The string.</param>
		/// <param name="delimiter">The delimiter.</param>
		void SplitString(
			PointerArray<tstring, uint32> & words,
			tstring str,
			tchar delimiter
			);

		TextComponent(const TextComponent &);
		TextComponent(TextComponent &&);
		TextComponent& operator=(const TextComponent &);
		TextComponent& operator=(TextComponent &&);
	};
}
