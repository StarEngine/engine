#pragma once

#include "Dictionary.h"
#include "SpriteAnimation.h"

namespace star
{
	class XMLContainer;

	class Spritesheet final : public Dictionary<tstring, SpriteAnimation>
	{
	public:
		Spritesheet();
		Spritesheet(XMLContainer & spritesheet);
		Spritesheet(const Spritesheet & yRef);
		Spritesheet(Spritesheet && yRef);
		Spritesheet(iterator begin, iterator end);
		~Spritesheet();

		Spritesheet & operator=(const Spritesheet& yRef);
		Spritesheet & operator=(Spritesheet&& yRef);

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
