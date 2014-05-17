#include "SpriteSheet.h"
#include "../Input/XMLContainer.h"
#include "../Helpers/Helpers.h"

namespace star
{
	SpriteSheet::SpriteSheet()
		: Dictionary<tstring, SpriteAnimation>()
		, m_Name(EMPTY_STRING)
		, m_DefaultAnimation(EMPTY_STRING)
		, m_FramesHorizontal(0)
		, m_FramesVertical(0)
	{

	}

	SpriteSheet::SpriteSheet(XMLContainer & spritesheet)
		: Dictionary<tstring, SpriteAnimation>()
		, m_Name(EMPTY_STRING)
		, m_DefaultAnimation(EMPTY_STRING)
		, m_FramesHorizontal(0)
		, m_FramesVertical(0)
	{
		auto attributes = spritesheet.GetAttributes();
		m_Name = attributes[_T("name")];
		m_DefaultAnimation = attributes[_T("default")];
		m_FramesHorizontal = string_cast<int32>(attributes[_T("width")]);
		m_FramesVertical = string_cast<int32>(attributes[_T("height")]);
		int32 amount = m_FramesHorizontal * m_FramesVertical;
		float32 speed = string_cast<float32>(attributes[_T("speed")]);

		auto it = spritesheet.lower_bound(_T("animation"));
		auto end_animation = spritesheet.upper_bound(_T("animation"));

		do
		{
			auto animation = it->second;
			auto animation_attributes = animation->GetAttributes();
			tstring aName = animation_attributes[_T("name")];
			float32 aSpeed = string_cast<float32>(animation_attributes[_T("speed")]);
			int32 aRepeat = string_cast<int32>(animation_attributes[_T("repeat")]);
			tstring frames = animation->GetValue();

			vec2 uv;
			uv.x = 1.0f / (float32)m_FramesHorizontal;
			uv.y = 1.0f / (float32)m_FramesVertical;

			SpriteAnimation spriteAnimation(aName, uv, aSpeed * speed, aRepeat,
				frames, m_FramesHorizontal, m_FramesVertical, amount);

			//[COMMENT] A memory leak starts below
			insert(std::pair<tstring, SpriteAnimation>(aName, spriteAnimation));

			++it;
		} while( it != end_animation );
	}

	SpriteSheet::SpriteSheet(const SpriteSheet & yRef)
		: Dictionary<tstring, SpriteAnimation>(yRef)
		, m_Name(yRef.m_Name)
		, m_DefaultAnimation(yRef.m_DefaultAnimation)
		, m_FramesHorizontal(yRef.m_FramesHorizontal)
		, m_FramesVertical(yRef.m_FramesVertical)
	{

	}

	SpriteSheet::SpriteSheet(SpriteSheet && yRef)
		: Dictionary<tstring, SpriteAnimation>(yRef)
		, m_Name(yRef.m_Name)
		, m_DefaultAnimation(yRef.m_DefaultAnimation)
		, m_FramesHorizontal(yRef.m_FramesHorizontal)
		, m_FramesVertical(yRef.m_FramesVertical)
	{

	}

	SpriteSheet::SpriteSheet(iterator begin, iterator end)
		: Dictionary<tstring, SpriteAnimation>(begin, end)
		, m_Name(EMPTY_STRING)
		, m_DefaultAnimation(EMPTY_STRING)
		, m_FramesHorizontal(0)
		, m_FramesVertical(0)
	{

	}

	SpriteSheet::~SpriteSheet()
	{

	}
	
	SpriteSheet & SpriteSheet::operator=(const SpriteSheet& yRef)
	{
		Dictionary<tstring, SpriteAnimation>::operator=(yRef);
		m_Name = yRef.m_Name;
		m_DefaultAnimation = yRef.m_DefaultAnimation;
		m_FramesHorizontal = yRef.m_FramesHorizontal;
		m_FramesVertical = yRef.m_FramesVertical;

		return *this;
	}
	
	SpriteSheet & SpriteSheet::operator=(SpriteSheet&& yRef)
	{
		Dictionary<tstring, SpriteAnimation>::operator=(yRef);
		m_Name = yRef.m_Name;
		m_DefaultAnimation = yRef.m_DefaultAnimation;
		m_FramesHorizontal = yRef.m_FramesHorizontal;
		m_FramesVertical = yRef.m_FramesVertical;

		return *this;
	}
	
	void SpriteSheet::SetName(const tstring & name)
	{
		m_Name = name;
	}

	const tstring & SpriteSheet::GetName() const
	{
		return m_Name;
	}

	const tstring & SpriteSheet::GetDefaultAnimation() const
	{
		return m_DefaultAnimation;
	}

	int32 SpriteSheet::GetFramesHorizontal() const
	{
		return m_FramesHorizontal;
	}

	int32 SpriteSheet::GetFramesVertical() const
	{
		return m_FramesVertical;
	}
}
