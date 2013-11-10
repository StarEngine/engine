#pragma once

#include "../defines.h"
#include <map>
#include "../Helpers/Spritesheet.h"

namespace star
{
	class SpriteAnimationManager final
	{
	public:
		~SpriteAnimationManager();

		void AddSpritesheet(const tstring & file);
		void AddSpritesheet(const tstring & file, const tstring & binary_file);
		const Spritesheet & GetSpritesheet(const tstring & name) const;
		static SpriteAnimationManager * GetInstance();
		void Clear();

	private:
		static SpriteAnimationManager * m_pManager;
		std::map<tstring, Spritesheet> m_Spritesheets;

		SpriteAnimationManager();

		SpriteAnimationManager(const SpriteAnimationManager &);
		SpriteAnimationManager(SpriteAnimationManager &&);
		SpriteAnimationManager & operator=(const SpriteAnimationManager &);
	};
}