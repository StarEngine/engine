#include "SpriteAnimationManager.h"
#include "../Input/XMLFileParser.h"
#include "../Input/XMLContainer.h"

namespace star
{
	SpriteAnimationManager * SpriteAnimationManager::m_pManager = nullptr;
	
	SpriteAnimationManager::~SpriteAnimationManager()
	{

	}

	void SpriteAnimationManager::AddSpritesheet(const tstring & file, DirectoryMode mode)
	{
		XMLFileParser parser(file);
		XMLContainer container;
		parser.Read(container, mode);
		
		tstring name = container.GetAttributes()[_T("name")];
		auto it = m_Spritesheets.find(name);
		bool isValid = it == m_Spritesheets.end();
		//ASSERT(isValid, _T("This spritesheet already exists!"));
		if(isValid)
		{
			Spritesheet spritesheet(container);
			m_Spritesheets.insert(std::pair<tstring, Spritesheet>(name, spritesheet));
		}
	}
	
	void SpriteAnimationManager::AddSpritesheet(const tstring & file, const tstring & binary_file,
		DirectoryMode mode)
	{
		XMLFileParser parser(file);
		XMLContainer container;
		parser.Read(container, binary_file, mode);
		
		tstring name = container.GetAttributes()[_T("name")];
		auto it = m_Spritesheets.find(name);
		bool isValid = it == m_Spritesheets.end();
		//ASSERT(isValid, _T("This spritesheet already exists!"));
		if(isValid)
		{
			Spritesheet spritesheet(container);
			m_Spritesheets.insert(std::pair<tstring, Spritesheet>(name, spritesheet));
		}
	}

	const Spritesheet & 
		SpriteAnimationManager::GetSpritesheet(const tstring & name) const
	{
		auto it = m_Spritesheets.find(name);
		bool isValid = it != m_Spritesheets.end();
		ASSERT(isValid, _T("Couldn't find this spritesheet..."));
		return m_Spritesheets.at(name);
	}

	SpriteAnimationManager * SpriteAnimationManager::GetInstance()
	{
		if(m_pManager == nullptr)
		{
			m_pManager = new SpriteAnimationManager();
		}
		return m_pManager;
	}
	
	void SpriteAnimationManager::Clear()
	{
		m_Spritesheets.clear();
	}

	SpriteAnimationManager::SpriteAnimationManager()
		: m_Spritesheets()
	{

	}
}
