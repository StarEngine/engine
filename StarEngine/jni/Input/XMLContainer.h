#pragma once

#include "../defines.h"
#include "../Helpers/Dictionary.h"
#include "../Helpers/SerializedData.h"
#include <memory>

namespace star
{
	class XMLContainer final :
			public Dictionary<tstring, std::shared_ptr<XMLContainer>>
	{
	public:
		XMLContainer();
		XMLContainer(const XMLContainer & yRef);
		XMLContainer(XMLContainer && yRef);
		~XMLContainer();

		XMLContainer & operator=(const XMLContainer & yRef);
		XMLContainer & operator=(XMLContainer && yRef);

		Dictionary<tstring, tstring> & GetAttributes();
		const tstring & GetValue() const;
		const tstring & GetName() const;

		void SetValue(const tstring & value);
		void SetName(const tstring & name);
		
		void clear();
		void swap(XMLContainer & yRef);

		void Serialize(const tstring & file, DirectoryMode mode = DEFAULT_DIRECTORY_MODE);
		void Deserialize(const tstring & file, DirectoryMode mode = DEFAULT_DIRECTORY_MODE);

	protected:
		tstring m_Value, m_Name;
		Dictionary<tstring, tstring> m_Attributes;
		
		uint32 SerializeString(const tstring & value, schar ** data, schar end = NULL);
		void SerializeChildren(SerializedData & data,
			const dictionary & map);
		void SerializeXMLContainer(SerializedData & data,
			XMLContainer * container);
		void SerializeAttributes(SerializedData & data,
			const Dictionary<tstring, tstring> & container);

		void DeserializeString(SerializedData & data, uint32 & counter, tstring & str);
		void DeserializeAttributes(SerializedData & data, uint32 & counter,
			Dictionary<tstring, tstring> & container);
		void DeserializeChildren(SerializedData & data, uint32 & counter,
			dictionary & map);
		void DeserializeXMLContainer(SerializedData & data, uint32 & counter,
			XMLContainer * container);

		static const schar 
			SER_END_OF_NAME_OR_VALUE = 4,
			SER_START_OF_ATTRIBUTES = 2,
			SER_END_OF_ATTRIBUTES = 3,
			SER_START_OF_CHILDREN = 1,
			SER_END_OF_CHILDREN = 5,
			SER_START_OF_CHILD = 6,
			SER_END_OF_CHILD = 7;
	};
}
