#include "Level.h"
#include "Object.h"

namespace star
{
	Level::Level(const tstring & file, float level_scale)
		: m_LevelFile(file)
		, m_LevelScale(level_scale)
		, m_Objects()
	{

	}

	Level::~Level()
	{
		for(auto it = m_Objects.begin(); it != m_Objects.end(); ++it)
		{
			it->second->GetScene()->RemoveObject(it->second);
			delete it->second;
		}
		m_Objects.clear(); 
	}

	void Level::Initialize()
	{

	}
}