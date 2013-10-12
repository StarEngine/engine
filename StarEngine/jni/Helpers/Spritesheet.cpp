#include "Spritesheet.h"
#include "../Input/XMLContainer.h"
#include "../Helpers/Helpers.h"

namespace star
{
	Spritesheet::Spritesheet()
		: Dictionary<tstring, SpriteAnimation>()
		, m_Name(EMPTY_STRING)
	{

	}

	Spritesheet::Spritesheet(XMLContainer & spritesheet)
		: Dictionary<tstring, SpriteAnimation>()
		, m_Name(EMPTY_STRING)
	{
		auto attributes = spritesheet.GetAttributes();
		m_Name = attributes[_T("name")];
		int width = string_cast<int>(attributes[_T("width")]);
		int height = string_cast<int>(attributes[_T("height")]);
		int amount = width * height;
		float speed = string_cast<float>(attributes[_T("speed")]);

		auto it = spritesheet.lower_bound(_T("animation"));
		auto end_animation = spritesheet.upper_bound(_T("animation"));

		do
		{
			auto animation = it->second;
			auto animation_attributes = animation->GetAttributes();
			tstring aName = animation_attributes[_T("name")];
			float aSpeed = string_cast<float>(animation_attributes[_T("speed")]);
			int aRepeat = string_cast<int>(animation_attributes[_T("repeat")]);
			tstring frames = animation->GetValue();

			vec2 uv;
			uv.x = 1.0f / (float)width;
			uv.y = 1.0f / (float)height;

			SpriteAnimation spriteAnimation(aName, uv, aSpeed * speed, aRepeat,
				frames, width, amount);

			insert(std::pair<tstring, SpriteAnimation>(aName, spriteAnimation));

			++it;
		} while( it != end_animation );
	}

	Spritesheet::Spritesheet(const Spritesheet & yRef)
		: Dictionary<tstring, SpriteAnimation>(yRef)
		, m_Name(EMPTY_STRING)
	{

	}

	Spritesheet::Spritesheet(Spritesheet && yRef)
		: Dictionary<tstring, SpriteAnimation>(yRef)
		, m_Name(EMPTY_STRING)
	{

	}

	Spritesheet::Spritesheet(iterator begin, iterator end)
		: Dictionary<tstring, SpriteAnimation>(begin, end)
		, m_Name(EMPTY_STRING)
	{

	}

	Spritesheet::~Spritesheet()
	{

	}
	
	Spritesheet & Spritesheet::operator=(const Spritesheet& yRef)
	{
		Dictionary<tstring, SpriteAnimation>::operator=(yRef);
		m_Name = yRef.m_Name;

		return *this;
	}
	
	void Spritesheet::SetName(const tstring & name)
	{
		m_Name = name;
	}

	const tstring & Spritesheet::GetName() const
	{
		return m_Name;
	}
}
