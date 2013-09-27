#pragma once

#include "..\defines.h"
#include "..\Helpers\Filepath.h"
#include "PugiXML\src\pugixml.hpp"
#include "PugiXML\src\pugiconfig.hpp"
#include "XMLContainer.h"
#include "../Helpers/Helpers.h"

namespace star
{
	class XMLFileSerializer
	{
	public:
		XMLFileSerializer(const tstring & full_path)
			: m_File(full_path)
		{

		}

		XMLFileSerializer(const tstring & path, const tstring & file)
			: m_File(path, file)
		{

		}

		~XMLFileSerializer() {}

		void Write(XMLContainer & container)
		{
			pugi::xml_document XMLDocument;
			pugi::xml_parse_result result = XMLDocument.load_file(m_File.GetFullPath().c_str());
			ASSERT (result == pugi::status_ok, star::CharToTChar(result.description()));
			if (result == pugi::status_ok)
			{
				tstringstream strstrResult;
				strstrResult << _T("<?xml version=\"1.0\"?>") << std::endl << std::endl;
				uint32 tabs(0);
				WriteChild(strstrResult, container, tabs);
			}
		}

	private:
		Filepath m_File;
		#define TAB _T("    ")

		void WriteAtributes(tstringstream & strstr, XMLContainer & element)
		{
			auto attributes = element.GetAttributes();
			for(auto attribute : attributes)
			{
				strstr << _T(" ") << attribute.first << _T("=\"") << attribute.second << _T("\"");
			}
		}

		void WriteChild(tstringstream & strstr, XMLContainer & element, uint32 & tabs)
		{
			strstr << GetTabString(tabs) << _T("<") << element.GetName();
			WriteAtributes(strstr, element);
			strstr << _T(">") << std::endl;
			if(element.size() > 0)
			{
				++tabs;
				for(auto child : element)
				{
					WriteChild(strstr, child.second, tabs);
				}
				--tabs;
				strstr << _T("</") << element.GetName() << _T(">") << std::endl;
			}
			else if(element.GetValue() != EMPTY_STRING)
			{
				strstr << element.GetValue();
				strstr << _T("</") << element.GetName() << _T(">") << std::endl;
			}
		}

		static tstring GetTabString(uint32 & tabs)
		{
			tstring tab_string(EMPTY_STRING);
			for(uint32 i = 0 ; i < tabs ; ++i)
			{
				tab_string += TAB;
			}
			return tab_string;
		}

		XMLFileSerializer(const XMLFileSerializer & yRef);
		const XMLFileSerializer & operator=(const XMLFileSerializer & yRef);
	};
}
