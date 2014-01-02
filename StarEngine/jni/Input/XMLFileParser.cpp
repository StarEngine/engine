#include "XMLFileParser.h"
#include "PugiXML\src\pugixml.hpp"
#include "PugiXML\src\pugiconfig.hpp"
#include "XMLContainer.h"
#include "XMLFileSerializer.h"
#include "..\Helpers\Helpers.h"
#include "..\Logger.h"

#ifdef ANDROID
#include "../Helpers/HelpersAndroid.h"
#endif

namespace star
{
	XMLFileParser::XMLFileParser(const tstring & path, DirectoryMode mode)
		: m_File(path, mode)
	{

	}

	XMLFileParser::~XMLFileParser()
	{

	}

	bool XMLFileParser::Read(XMLContainer & container)
	{
		pugi::xml_document XMLDocument;
		pugi::xml_parse_result result;
		
		SerializedData data;
		data.data = ReadBinaryFile(m_File.GetLocalPath(), data.size, m_File.GetDirectoryMode());
		result = XMLDocument.load_buffer_inplace_own(data.data, data.size);

		ASSERT_LOG(result,
			_T("XMLFileParser::Read: ") 
				+ string_cast<tstring>(result.description()), STARENGINE_LOG_TAG);
		if (result)
		{
			auto root = XMLDocument.first_child();
			if(root != NULL)
			{
				container.SetName(star::string_cast<tstring>(root.name()));
				AddAttributes(container, root);

				auto child = root.first_child();
				if(child != NULL)
				{
					do 
					{
						AddChild(container, child);
						child = child.next_sibling();
					} while (child != NULL);
				}
			}
		}
		return result;
	}
	
	bool XMLFileParser::Read(XMLContainer & container, const tstring & binary_path)
	{
#ifdef _DEBUG
		bool result = Read(container);
		if(result)
		{
			container.Serialize(binary_path, m_File.GetDirectoryMode());
		}
		return result;
#else
		container.Deserialize(binary_path, m_File.GetDirectoryMode());
		return true;
#endif
	}

	uint8 XMLFileParser::ReadOrCreate(
		XMLContainer & container,
		const tstring & rootName
		)
	{
		pugi::xml_document XMLDocument;
		pugi::xml_parse_result result;
		
		SerializedData data;
		if(ReadBinaryFileSafe(m_File.GetLocalPath(), data.data, data.size, m_File.GetDirectoryMode(), false))
		{
			result = XMLDocument.load_buffer_inplace_own(data.data, data.size);
			if (result)
			{
				auto root = XMLDocument.first_child();
				if(root != NULL)
				{
					container.SetName(star::string_cast<tstring>(root.name()));
					AddAttributes(container, root);

					auto child = root.first_child();
					if(child != NULL)
					{
						do 
						{
							AddChild(container, child);
							child = child.next_sibling();
						} while (child != NULL);
					}
				}
				LOG(LogLevel::Info,
					_T("XMLFileParser::ReadOrCreate: read file '")
					+ m_File.GetLocalPath() + _T("'."), STARENGINE_LOG_TAG);
				return FILE_READ; 
			}
			LOG(LogLevel::Warning,
				_T("XMLFileParser::ReadOrCreate: ") +
				star::string_cast<tstring>(result.description()), STARENGINE_LOG_TAG);

			return FILE_ERROR;
		}

		// Write the file instead
		XMLFileSerializer serializer(m_File.GetLocalPath());
		container.SetName(rootName);
		serializer.Write(container);
		
		LOG(LogLevel::Info,
			_T("XMLFileParser::ReadOrCreate: created file '")
			+ m_File.GetLocalPath() + _T("'."), STARENGINE_LOG_TAG);

		return FILE_WRITE;
	}
	
	uint8 XMLFileParser::ReadOrCreate(
		XMLContainer & container,
		const tstring & rootName,
		const tstring & binary_path
		)
	{
#ifdef _DEBUG
		uint8 result = ReadOrCreate(container, rootName);
		if(result)
		{
			container.Serialize(binary_path, m_File.GetDirectoryMode());
		}
		return result;
#else
		if(!container.DeserializeSafe(
				binary_path,
				m_File.GetDirectoryMode()
				)
			)
		{
			container.SetName(rootName);
			container.Serialize(binary_path, m_File.GetDirectoryMode());
		
			LOG(LogLevel::Info,
				_T("XMLFileParser::ReadOrCreate: created file '")
				+ m_File.GetLocalPath() + _T("'."), STARENGINE_LOG_TAG);

			return FILE_WRITE;
		}

		LOG(LogLevel::Info,
			_T("XMLFileParser::ReadOrCreate: read file '")
			+ m_File.GetLocalPath() + _T("'."), STARENGINE_LOG_TAG);

		return FILE_READ;
#endif
	}

	void XMLFileParser::AddAttributes(XMLContainer & element, const pugi::xml_node & node)
	{
		auto attributes = node.attributes();
		for(auto attribute : attributes)
		{
			element.GetAttributes().insert( 
				std::make_pair<tstring, tstring>( 
					star::string_cast<tstring>(attribute.name()),
					star::string_cast<tstring>(attribute.value())));
		}
	}

	void XMLFileParser::AddChild(XMLContainer & parent, const pugi::xml_node & node)
	{
		std::shared_ptr<XMLContainer> child(new XMLContainer());
		AddAttributes(*(child.get()), node);
		child->SetName(star::string_cast<tstring>(node.name()));
		child->SetValue(star::string_cast<tstring>(node.child_value()));
		auto sibling = node.first_child();
		if(sibling != NULL)
		{
			do 
			{
				AddChild(*(child.get()), sibling);
				sibling = sibling.next_sibling();
			} while (sibling != NULL);
		}
		if(child->GetName() != EMPTY_STRING)
		{
			parent.insert(std::make_pair(star::string_cast<tstring>(node.name()), child));
		}
	}
}
