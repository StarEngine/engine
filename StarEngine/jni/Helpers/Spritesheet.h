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

		void SetName(const tstring & name);
		const tstring & GetName() const;

		const tstring & GetDefaultAnimation() const;

		int GetFramesHorizontal() const;
		int GetFramesVertical() const;
		
	private:
		tstring m_Name;
		tstring m_DefaultAnimation;
		int m_FramesHorizontal;
		int m_FramesVertical;
	};
}
