#pragma once

#include "../defines.h"
#include <memory>
#include <map>
#include "../Helpers/Spritesheet.h"

namespace star
{
	class SpriteAnimationManager final
	{
	public:
		~SpriteAnimationManager();

		void AddSpritesheet(const tstring & file);
		const Spritesheet & GetSpritesheet(const tstring & name) const;

		static std::shared_ptr<SpriteAnimationManager> GetInstance();

	private:
		static std::shared_ptr<SpriteAnimationManager> m_pManager;
		std::map<tstring, Spritesheet> m_Spritesheets;

		SpriteAnimationManager();

		SpriteAnimationManager(const SpriteAnimationManager &);
		SpriteAnimationManager(SpriteAnimationManager &&);
		SpriteAnimationManager & operator=(const SpriteAnimationManager &);
	};
}