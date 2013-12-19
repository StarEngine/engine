#include "XMLContainer.h"
#include "../Helpers/Helpers.h"
#include "../Logger.h"

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

	XMLContainer::XMLContainer(XMLContainer && yRef)
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

	XMLContainer & XMLContainer::operator=(XMLContainer && yRef)
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

	void XMLContainer::AddChild(const tstring & name)
	{
		auto container = std::make_shared<XMLContainer>();
		container->SetName(name);
		m_MultiMap.insert(
			std::pair<tstring, std::shared_ptr<XMLContainer>>(
				name, container
				)
			);
	}

	void XMLContainer::AddChild(const tstring & name, const tstring & value)
	{
		auto container = std::make_shared<XMLContainer>();
		container->SetName(name);
		container->SetValue(value);
		m_MultiMap.insert(
			std::pair<tstring, std::shared_ptr<XMLContainer>>(
				name, container
				)
			);
	}

	void XMLContainer::Serialize(const tstring & file, DirectoryMode mode)
	{
		SerializedData data;
		SerializeXMLContainer(data, this);
		WriteBinaryFile(file, data.data, data.size, mode);
		delete [] data.data;
	}

	void XMLContainer::Deserialize(const tstring & file, DirectoryMode mode)
	{
		clear();

		SerializedData buffer;
		buffer.data = ReadBinaryFile(file, buffer.size, mode);
		uint32 counter(1); // first byte == SER_START_OF_CHILD
		DeserializeXMLContainer(buffer, counter, this);

		delete [] buffer.data;
	}

	bool XMLContainer::DeserializeSafe(const tstring & file, DirectoryMode mode)
	{
		clear();

		SerializedData buffer;
		bool result = ReadBinaryFileSafe(file, buffer.data, buffer.size, mode);

		if(result)
		{
			uint32 counter(1); // first byte == SER_START_OF_CHILD
			DeserializeXMLContainer(buffer, counter, this);
			delete [] buffer.data;
		}
		else
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("XMLContainer::DeserializeSafe: Couldn't read file '")
				+ file + _T("'."), STARENGINE_LOG_TAG);
		}

		return result;
	}

	uint32 XMLContainer::SerializeString(
		const tstring & value, schar ** data, schar end)
	{
	#ifdef _WIN32
		#ifndef _UNICODE
		sstring_16 wValue =
				string_cast<sstring_16>(value);
		#endif
	#else
		sstring_16 wValue =
				string_cast<sstring_16>(value);
	#endif
		auto size = value.length() * sizeof(swchar);
		uint8 extra(0);
		if(end != NULL) ++extra;
		*data = new schar[size + extra];
	#ifdef _WIN32
		#ifdef _UNICODE
		memcpy(*data, value.c_str(), size);
		#else
		memcpy(*data, wValue.c_str(), size);
		#endif
	#else
		memcpy(*data, wValue.c_str(), size);
	#endif
		if(end != NULL)
		{
			(*data)[size] = end;
		}
		return size + extra;
	}
		
	void XMLContainer::SerializeChildren(SerializedData & data,
		const dictionary & map)
	{
		data.size = 2;
		auto mapSize = map.size();
		if(mapSize > 0)
		{
			SerializedData * buffers = new SerializedData[mapSize];
			auto it = map.cbegin();
			auto end = map.cend();
			uint32 counter(0);

			while(it != end)
			{
				SerializeXMLContainer(buffers[counter], it->second.get());
				data.size += buffers[counter].size;
				++it;
				++counter;
			}

			data.data = new schar[data.size];
			counter = 1; // 0th character is SER_START_OF_CHILDREN

			for(uint32 i = 0 ; i < mapSize ; ++i)
			{
				auto & buffer = buffers[i];
				for(uint32 u = 0 ; u < buffer.size ; ++u)
				{
					data.data[counter] = buffer.data[u];
					++counter;
				}
				delete [] buffer.data;
			}

			delete [] buffers;
		}
		else
		{
			data.data = new schar[data.size];
		}
		data.data[0] = SER_START_OF_CHILDREN;
		data.data[data.size - 1] = SER_END_OF_CHILDREN;
	}

	
	void XMLContainer::SerializeXMLContainer(SerializedData & data,
		XMLContainer * container)
	{
		uint8 n(4);
		SerializedData	*buffers;

		buffers = new SerializedData[n];

		buffers[0].size = SerializeString(container->m_Name,
			&buffers[0].data, SER_END_OF_NAME_OR_VALUE);

		buffers[1].size = SerializeString(container->m_Value,
			&buffers[1].data , SER_END_OF_NAME_OR_VALUE);

		SerializeAttributes(data, container->m_Attributes);
		buffers[2].size = data.size;
		buffers[2].data = data.data;

		SerializeChildren(data, container->m_MultiMap);
		buffers[3].size= data.size;
		buffers[3].data = data.data;

		data.size = buffers[0].size +
			buffers[1].size + buffers[2].size
			+ buffers[3].size + 2;

		data.data = new schar[data.size];
		uint32 c(1); // 0th character is SER_START_OF_CHILD
		data.data[0] = SER_START_OF_CHILD;
		data.data[data.size-1] = SER_END_OF_CHILD;

		for(uint32 i = 0 ; i < n ; ++i)
		{
			for(uint32 u = 0 ; u < buffers[i].size ; ++u)
			{
				data.data[c] = buffers[i].data[u];
				++c;
			}
			delete [] buffers[i].data;
		}

		delete [] buffers;
	}

	void XMLContainer::SerializeAttributes(SerializedData & data,
		const Dictionary<tstring, tstring> & container)
	{
		data.size = 2;
		auto it = container.cbegin();
		auto end = container.cend();
		
		SerializedData ** buffers;
		auto cSize = container.size();
		buffers = new SerializedData*[cSize];

		uint32 i(0);
		while(it != end)
		{
			buffers[i] = new SerializedData[2];

			buffers[i][0].size = SerializeString(it->first,
				&buffers[i][0].data, SER_END_OF_NAME_OR_VALUE);
			buffers[i][1].size = SerializeString(it->second,
				&buffers[i][1].data, SER_END_OF_NAME_OR_VALUE);

			data.size += buffers[i][0].size + buffers[i][1].size;

			++it;
			++i;
		}

		data.data = new schar[data.size];
		uint32 c(1);

		data.data[0] = SER_START_OF_ATTRIBUTES;
		data.data[data.size-1] = SER_END_OF_ATTRIBUTES;

		for(i = 0 ; i < cSize ; ++i)
		{
			for(uint32 u = 0 ; u < 2 ; ++u)
			{
				for(uint32 t = 0 ; t < buffers[i][u].size ; ++t)
				{
					data.data[c] = buffers[i][u].data[t];
					++c;
				}
				delete [] buffers[i][u].data;
			}
			delete [] buffers[i];
		}
		delete [] buffers;
	}
	
	void XMLContainer::DeserializeString(
		SerializedData & data, uint32 & counter, tstring & str)
	{
		sstring buffer;
		schar c;
		uint32 size(0);

		do
		{
			c = data.data[counter];
			buffer += c;
			++size;
			++counter;
		} while(c != SER_END_OF_NAME_OR_VALUE);
		
		--size;

#ifdef _WIN32
	#ifdef _UNICODE 
		str.clear();
		str.resize(size / sizeof(tchar));
		memcpy(&str[0], &buffer[0], size);
	#else
		swstring stringBuffer;
		stringBuffer.resize(size / sizeof(swchar));
		memcpy(&stringBuffer[0], &buffer[0], size);
		str = string_cast<sstring>(stringBuffer);
	#endif
#else
		sstring_16 stringBuffer;
		stringBuffer.resize(size / sizeof(schar_16));
		memcpy(&stringBuffer[0], &buffer[0], size);
		str = string_cast<tstring>(stringBuffer);
#endif
	}

	void XMLContainer::DeserializeAttributes(SerializedData & data, uint32 & counter,
		Dictionary<tstring, tstring> & container)
	{
		while(data.data[counter] != SER_START_OF_ATTRIBUTES)
		{
			++counter;
		}
		++counter;
		bool isValue(false);
		tstring name,value;
		while(data.data[counter] != SER_END_OF_ATTRIBUTES)
		{
			if(!isValue)
			{
				DeserializeString(data, counter, name);
				isValue = true;
			}
			else
			{
				DeserializeString(data, counter, value);
				container.insert(std::pair<tstring, tstring>(name, value));
				isValue = false;
			}
		}
	}

	void XMLContainer::DeserializeChildren(SerializedData & data, uint32 & counter,
		dictionary & map)
	{
		while(data.data[counter] != SER_START_OF_CHILDREN)
		{
			++counter;
		}
		++counter;
		bool isValue(false);
		tstring name,value;
		while(data.data[counter] != SER_END_OF_CHILDREN)
		{
			while(data.data[counter] != SER_START_OF_CHILD)
			{
				if(data.data[counter] == SER_END_OF_CHILDREN)
				{
					++counter;
					return;
				}
				++counter;
			}
			++counter;
			XMLContainer * container = new XMLContainer();
			DeserializeXMLContainer(data, counter, container);
			map.insert(dkv_pair(container->GetName(), std::shared_ptr<XMLContainer>(container)));
			while(data.data[counter] != SER_END_OF_CHILD)
			{
				++counter;
			}
			++counter;
		}
	}

	void XMLContainer::DeserializeXMLContainer(SerializedData & data, uint32 & counter,
		XMLContainer * container)
	{
		DeserializeString(data, counter, container->m_Name);
		DeserializeString(data, counter, container->m_Value);
		DeserializeAttributes(data, counter, container->m_Attributes);
		DeserializeChildren(data, counter, container->m_MultiMap);
	}
}
