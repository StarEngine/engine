#pragma once

#include "..\Helpers\Filepath.h"
#include "PugiXML/src/pugixml.hpp"
#include "PugiXML/src/pugiconfig.hpp"
#include "XMLContainer.h"
#include "../Helpers/Helpers.h"

namespace star
{
	class XMLFileParser
	{
	public:
		XMLFileParser(const tstring & full_path)
			: m_File(full_path)
		{

		}

		XMLFileParser(const tstring & path, const tstring & file)
			: m_File(path, file)
		{

		}

		~XMLFileParser()
		{

		}

		void Read(XMLContainer & container)
		{
			pugi::xml_document XMLDocument;
			pugi::xml_parse_result result = XMLDocument.load_file(m_File.GetFullPath().c_str());
			ASSERT (result == pugi::status_ok, star::CharToTChar(result.description()));
			if (result == pugi::status_ok)
			{
				auto root = XMLDocument.first_child();
				if(root != NULL)
				{
					container.SetName(star::CharToTChar(root.name()));
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
		}

	private:
		Filepath m_File;

		void AddAttributes(XMLContainer & element, const pugi::xml_node & node)
		{
			auto element_attributes = element.GetAttributes();
			for(auto attribute : node.attributes())
			{
				element_attributes.insert( std::make_pair<tstring, tstring>( star::CharToTChar(attribute.name()),
					star::CharToTChar(attribute.value())));
			}
		}

		void AddChild(XMLContainer & parent, const pugi::xml_node & node)
		{
			XMLContainer child;
			AddAttributes(child, node);
			child.SetValue(star::CharToTChar(node.value()));
			auto sibling = node.first_child();
			if(sibling != NULL)
			{
				do 
				{
					AddChild(child, sibling);
					sibling = sibling.next_sibling();
				} while (sibling != NULL);
			}
			parent.insert(std::make_pair(star::CharToTChar(node.name()), child));
		}

		XMLFileParser(const XMLFileParser & yRef);
		const XMLFileParser & operator=(const XMLFileParser & yRef);
	};
}
