#pragma once

#include "../defines.h"
#include "../Helpers/Filepath.h"

#include <map>

namespace star
{
	class Object;

	class Level
	{
	public:
		Level(const tstring & file, float level_scale = 1.0f);
		virtual ~Level();

		virtual void Initialize(); 

	protected:
		Filepath m_LevelFile;
		float m_LevelScale;
		std::map<tstring, Object*> m_Objects;

	private:
		Level(const Level &);
		Level(Level &&);
		Level & operator=(const Level &);
	};
}