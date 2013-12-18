#pragma once

#include "../../defines.h"
#include "../BaseComponent.h"
#include "../../Helpers/FilePath.h"
#include "../../Graphics/Color.h"

namespace star
{

	/// <summary>
	/// Information of a sprite. 
	/// Gets sent to the <see cref="SpriteBatch"> to process it correctly.
	/// Contains the width and height of the sprite, 
	/// the UVs, textureID, pointer to the <see cref="TransformComponent">,
	/// color multiplier and a bool to check if the sprite is a HUD element.
	/// </summary>
	struct SpriteInfo
	{
		SpriteInfo()
			: vertices()
			, uvCoords()
			, textureID()
			, transformPtr(nullptr)
			, colorMultiplier(Color::White)
			, bIsHud(false)
		{

		}

		vec2 vertices;
		vec4 uvCoords;
		uint32 textureID;
		TransformComponent* transformPtr;
		Color colorMultiplier;
		bool bIsHud;
	};

	/// <summary>
	/// Graphics component used to draw a texture or part of a texture.
	/// </summary>
	class SpriteComponent : public BaseComponent
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="SpriteComponent"/> class.
		/// </summary>
		/// <param name="filepath">
		/// Path to the asset, starting from the path defined in <see cref="DirectoryMode::assets"/>.
		/// </param>
		/// <param name="spriteName">Name of the sprite.</param>
		/// <param name="widthSegments">Amount of width segments. Default set to 1</param>
		/// <param name="heightSegments">Amount of height segments. Default set to 1</param>
		SpriteComponent(
			const tstring& filepath,
			const tstring& spriteName,
			uint32 widthSegments = 1,
			uint32 heightSegments = 1
			);

		/// <summary>
		/// Finalizes an instance of the <see cref="SpriteComponent"/> class.
		/// </summary>
		virtual ~SpriteComponent();

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
		/// Gets the file path of the texture.
		/// </summary>
		/// <returns>the file path.</returns>
		const tstring& GetFilePath() const;

		/// <summary>
		/// Gets the name of the sprite.
		/// </summary>
		/// <returns>name of the sprite</returns>
		const tstring& GetName() const;
		
		/// <summary>
		/// Sets the current segment to draw.
		/// </summary>
		/// <param name="widthSegment">The width segment.</param>
		/// <param name="heightSegment">The height segment.</param>
		void SetCurrentSegment(uint32 widthSegment, uint32 heightSegment);

		/// <summary>
		/// Sets the color multiplier for this sprite.
		/// </summary>
		/// <param name="color">The color.</param>
		void SetColorMultiplier(const Color & color);

		/// <summary>
		/// Sets this Sprite as a HUD element
		/// </summary>
		/// <param name="enabled">True to become a HUD element.</param>
		void SetHUDOptionEnabled(bool enabled);

		/// <summary>
		/// Determines whether this Sprite is a HUD element.
		/// </summary>
		/// <returns></returns>
		bool IsHUDOptionEnabled() const;

		/// <summary>
		/// Sets the texture of this sprite. Usefull if you want to change the texture at runtime.
		/// </summary>
		/// <param name="filepath">Path to the asset, starting from the path defined in <see cref="DirectoryMode::assets"/>.</param>
		/// <param name="spriteName">Name of the sprite.</param>
		/// <param name="widthSegments">Amount of width segments. Default set to 1.</param>
		/// <param name="heightSegments">Amount of height segments. Default set to 1.</param>
		void SetTexture(
			const tstring& filepath,
			const tstring& spriteName,
			uint32 widthSegments = 1,
			uint32 heightSegments = 1
			);

	protected:
		/// <summary>
		/// Initializes the component.
		/// </summary>
		virtual void InitializeComponent();
		/// <summary>
		/// Creates the uv coordinates.
		/// </summary>
		virtual void CreateUVCoords();
		/// <summary>
		/// Sets the uv coordinates.
		/// </summary>
		/// <param name="coords">The uv coordinatess.</param>
		void SetUVCoords(const vec4& coords);
		/// <summary>
		/// Fills the sprite information struct, to send to the <see cref="SpriteBatch"/>
		/// </summary>
		virtual void FillSpriteInfo();

		uint32	m_WidthSegments,
				m_HeightSegments, 
				m_CurrentWidthSegment,
				m_CurrentHeightSegment;

	private:

		FilePath m_FilePath;
		tstring m_SpriteName;
		
		SpriteInfo* m_SpriteInfo;

		SpriteComponent(const SpriteComponent &);
		SpriteComponent(SpriteComponent &&);
		SpriteComponent& operator=(const SpriteComponent &);
		SpriteComponent& operator=(SpriteComponent &&);
	};
}
