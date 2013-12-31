#pragma once
#include "UIBaseCursor.h"
#include "../Color.h"

#include <unordered_map>

namespace star
{
	class SpriteSheetComponent;

	class UICursor : public UIBaseCursor
	{
	public:
		UICursor(
			const tstring & name,
			const tstring & spriteFile,
			const tstring & spritesheetName
			);

		UICursor(
			const tstring & name,
			const tstring & spriteFile,
			const tstring & spriteName,
			const tstring & spritesheetName
			);

		virtual ~UICursor();

		void SetCenterPoint(const vec2 & center);
		void SetCenterPoint(float32 x, float32 y);
		void SetCenterX(float32 x);
		void SetCenterY(float32 y);

		void SetDefaultCenterPosition(const vec2 & center);
		void SetDefaultCenterPosition(float32 x, float32 y);

		virtual void SetState(const tstring & state);

		void SetStateOffset(
			const tstring & state,
			const vec2 & offset
			);

		void SetStateOffset(
			const tstring & state,
			float32 x,
			float32 y
			);

		void SetColorMultiplier(const Color & color);

	protected:
		virtual void Update(const Context & context);

		SpriteSheetComponent * m_pCursorSprite;
		std::unordered_map<tstring, vec2> m_Offsets;
		vec2 m_DefaultOffset;

	private:
		UICursor(const UICursor &);
		UICursor(UICursor &&);
		UICursor & operator=(const UICursor &);
		UICursor & operator=(UICursor&&);
	};
}
