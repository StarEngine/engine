#pragma once

#include "..\defines.h"
#include "..\Helpers\Filepath.h"
#include "..\Helpers\Helpers.h"
#include "PugiXML\src\pugixml.hpp"
#include "PugiXML\src\pugiconfig.hpp"
#include "XMLContainer.h"

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
			tstringstream strstrResult;
			strstrResult << _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>") << std::endl;
			uint32 tabs(0);
			WriteChild(strstrResult, container, tabs);
			
			tofstream resultFile;
			resultFile.open(m_File.GetFullPath());
			resultFile << strstrResult.str();
			resultFile.close();
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
			if(element.size() == 0 && element.GetValue() == EMPTY_STRING)
			{
				strstr << _T("/>") << std::endl;
			}
			else
			{
				strstr << _T(">") << std::endl;
				if(element.size() > 0)
				{
					++tabs;
					for(auto child : element)
					{
						WriteChild(strstr, child.second, tabs);
					}
					--tabs;
					strstr << GetTabString(tabs) << _T("</") << element.GetName() << _T(">") << std::endl;
				}
				else if(element.GetValue() != EMPTY_STRING)
				{
					strstr << element.GetValue();
					strstr << _T("</") << element.GetName() << _T(">") << std::endl;
				}
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
		XMLFileSerializer(XMLFileSerializer && yRef);
		const XMLFileSerializer & operator=(const XMLFileSerializer & yRef);
	};
}
