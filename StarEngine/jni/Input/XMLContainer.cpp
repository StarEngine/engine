#include "XMLContainer.h"

namespace star
{
	XMLContainer::XMLContainer()
		: Dictionary<tstring, std::shared_ptr<XMLContainer>>()
	{

	}

	XMLContainer::XMLContainer(const XMLContainer & yRef)
		: Dictionary<tstring, std::shared_ptr<XMLContainer>>(yRef)
		, m_Value(yRef.m_Value)
		, m_Name(yRef.m_Name)
		, m_Attributes(yRef.m_Attributes)
	{

	}

	XMLContainer::~XMLContainer()
	{
		m_Attributes.clear();
	}

	XMLContainer & XMLContainer::operator=(const XMLContainer & yRef)
	{
		m_MultiMap = yRef.m_MultiMap;
		m_Value = yRef.m_Value;
		m_Name = yRef.m_Name;
		m_Attributes = yRef.m_Attributes;
		return *this;
	}

	Dictionary<tstring, tstring> & XMLContainer::GetAttributes()
	{
		return m_Attributes;
	}

	const tstring & XMLContainer::GetValue() const
	{
		return m_Value;
	}

	const tstring & XMLContainer::GetName() const
	{
		return m_Name;
	}

	void XMLContainer::SetValue(const tstring & value)
	{
		m_Value = value;
	}

	void XMLContainer::SetName(const tstring & name)
	{
		m_Name = name;
	}

	void XMLContainer::clear()
	{
		Dictionary<tstring, std::shared_ptr<XMLContainer>>::clear();
		m_Value = _T("");
		m_Attributes.clear();
	}

	void XMLContainer::swap(XMLContainer & yRef)
	{
		Dictionary<tstring, std::shared_ptr<XMLContainer>>::swap(yRef);
		m_Value = yRef.m_Value;
		m_Attributes.swap(yRef.m_Attributes);
	}
}
