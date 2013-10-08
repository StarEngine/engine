#pragma once

#include "../defines.h"
#include "../Helpers/Dictionary.h"
#include <memory>

namespace star
{
	class XMLContainer :
			public Dictionary<tstring, std::shared_ptr<XMLContainer> >
	{
	public:
		XMLContainer();
		XMLContainer(const XMLContainer & yRef);
		~XMLContainer();

		XMLContainer & operator=(const XMLContainer & yRef);

		Dictionary<tstring, tstring> & GetAttributes();
		const tstring & GetValue() const;
		const tstring & GetName() const;

		void SetValue(const tstring & value);
		void SetName(const tstring & name);
		
		void clear();
		void swap(XMLContainer & yRef);

	protected:
		tstring m_Value, m_Name;
		Dictionary<tstring, tstring> m_Attributes;
	};
}
