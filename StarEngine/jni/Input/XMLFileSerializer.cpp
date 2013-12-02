#include "XMLFileSerializer.h"
#include "..\Helpers\Helpers.h"
#include "XMLContainer.h"

namespace star
{
	XMLFileSerializer::XMLFileSerializer(const tstring & path)
		: m_File(path)
	{

	}

	XMLFileSerializer::~XMLFileSerializer() {}

	void XMLFileSerializer::Write(
		XMLContainer & container,
		DirectoryMode mode
		)
	{
		tstring buffer = WriteFile(container);
		WriteTextFile(m_File, buffer, mode);
	}

	void XMLFileSerializer::Write(
			XMLContainer & container,
			const tstring & binaryPath,
			DirectoryMode mode
			)
	{
		container.Serialize(binaryPath, mode);
	}

	tstring XMLFileSerializer::WriteFile(XMLContainer & container)
	{
		tstringstream strstrResult;
		strstrResult << _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>") << std::endl;
		uint32 tabs(0);
		WriteChild(strstrResult, container, tabs);

		return strstrResult.str();
	}

	void XMLFileSerializer::WriteAtributes(tstringstream & strstr, XMLContainer & element)
	{
		auto attributes = element.GetAttributes();
		for(auto attribute : attributes)
		{
			strstr << _T(" ") << attribute.first << _T("=\"") << attribute.second << _T("\"");
		}
	}

	void XMLFileSerializer::WriteChild(tstringstream & strstr, XMLContainer & element, uint32 & tabs)
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
			if(element.GetValue() != EMPTY_STRING)
			{
				++tabs;
				strstr << GetTabString(tabs) << element.GetValue() << std::endl;
				--tabs;
				strstr << GetTabString(tabs);
				strstr << _T("</") << element.GetName();
				strstr << _T(">") << std::endl;
			}
			else if(element.size() > 0)
			{
				++tabs;
				for(auto child : element)
				{
					XMLContainer child_value;
					child_value = *(child.second);
					WriteChild(strstr, child_value, tabs);
				}
				--tabs;
				strstr << GetTabString(tabs) << _T("</") << element.GetName() << _T(">") << std::endl;
			}
		}
	}

	tstring XMLFileSerializer::GetTabString(uint32 & tabs)
	{
		tstring tab_string(EMPTY_STRING);
		for(uint32 i = 0 ; i < tabs ; ++i)
		{
			tab_string += TAB;
		}
		return tab_string;
	}
}
