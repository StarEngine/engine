#pragma once

#include "Dictionary.h"
#include "SpriteAnimation.h"

namespace star
{
	class XMLContainer;

	class SpriteSheet final : public Dictionary<tstring, SpriteAnimation>
	{
	public:
		SpriteSheet();
		SpriteSheet(XMLContainer & spritesheet);
		SpriteSheet(const SpriteSheet & yRef);
		SpriteSheet(SpriteSheet && yRef);
		SpriteSheet(iterator begin, iterator end);
		~SpriteSheet();

		SpriteSheet & operator=(const SpriteSheet& yRef);
		SpriteSheet & operator=(SpriteSheet&& yRef);

		void SetName(const tstring & name);
		const tstring & GetName() const;

		const tstring & GetDefaultAnimation() const;

		int32 GetFramesHorizontal() const;
		int32 GetFramesVertical() const;
		
	private:
		tstring m_Name;
		tstring m_DefaultAnimation;
		int32 m_FramesHorizontal;
		int32 m_FramesVertical;
	};
}
