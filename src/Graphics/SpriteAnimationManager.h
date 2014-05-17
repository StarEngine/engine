#pragma once

#include "../defines.h"
#include "../Helpers/SpriteSheet.h"
#include "../Helpers/Singleton.h"
#include <map>

namespace star
{
	class SpriteAnimationManager final : public Singleton<SpriteAnimationManager>
	{
	public:
		friend Singleton<SpriteAnimationManager>;

		void AddSpritesheet(const tstring & file,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE);
		void AddSpritesheet(const tstring & file,
			const tstring & binary_file,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE);

		const SpriteSheet & GetSpritesheet(const tstring & name) const;

		void Clear();

	private:
		static SpriteAnimationManager * m_pManager;
		std::map<tstring, SpriteSheet> m_Spritesheets;

		SpriteAnimationManager();
		~SpriteAnimationManager();

		SpriteAnimationManager(const SpriteAnimationManager &);
		SpriteAnimationManager(SpriteAnimationManager &&);
		SpriteAnimationManager & operator=(const SpriteAnimationManager &);
		SpriteAnimationManager & operator=(SpriteAnimationManager&&);
	};
}