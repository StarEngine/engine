#pragma once

#include "../defines.h"
#include "../Helpers/Dictionary.h"

namespace star
{
	class XMLContainer : public Dictionary<tstring, XMLContainer>
	{
	public:
		XMLContainer()
			: Dictionary<tstring, XMLContainer>()
		{

		}
		
		XMLContainer(const XMLContainer & yRef)
			: Dictionary<tstring, XMLContainer>(yRef)
			, m_Value(yRef.m_Value)
			, m_Name(yRef.m_Name)
			, m_Attributes(yRef.m_Attributes)
		{

		}

		~XMLContainer()
		{
			m_Attributes.clear();
		}

		XMLContainer & operator=(const XMLContainer & yRef)
		{
			m_MultiMap = yRef.m_MultiMap;
			m_Value = yRef.m_Value;
			m_Name = yRef.m_Name;
			m_Attributes = yRef.m_Attributes;
			return *this;
		}

		Dictionary<tstring, tstring> & GetAttributes()
		{
			return m_Attributes;
		}

		const tstring & GetValue() const
		{
			return m_Value;
		}

		const tstring & GetName() const
		{
			return m_Name;
		}

		void SetValue(const tstring & value)
		{
			m_Value = value;
		}

		void SetName(const tstring & name)
		{
			m_Name = name;
		}

		void clear()
		{
			Dictionary<tstring, XMLContainer>::clear();
			m_Value = _T("");
			m_Attributes.clear();
		}

		void swap(XMLContainer & yRef)
		{
			Dictionary<tstring, XMLContainer>::swap(yRef);
			m_Value = yRef.m_Value;
			m_Attributes.swap(yRef.m_Attributes);
		}

	protected:
		tstring m_Value, m_Name;
		Dictionary<tstring, tstring> m_Attributes;
	};
}
