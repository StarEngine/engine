#include "../defines.h"
#include "../Input/XMLContainer.h"
#include "Helpers.h"

namespace star
{
	template <typename T>
	T GameData::GetData(
		const tstring & name,
		const tstring & group
		)
	{
		return string_cast<T, tstring>(
			m_Data.at(group)->at(name)->GetValue()
			);
	}
		
	template <typename T>
	void GameData::SetData(
		const tstring & name,
		const T & value,
		const tstring & group
		)
	{
		m_Data.at(group)->at(name)->SetValue(
			string_cast<tstring, T>(value)
			);
	}
}
