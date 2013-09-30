#pragma once

#include "..\Helpers\Filepath.h"
#include "PugiXML/src/pugixml.hpp"
#include "PugiXML/src/pugiconfig.hpp"
#include "XMLContainer.h"
#include "..\Helpers\Helpers.h"

#ifndef _WIN32
#include <memory>
#endif

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

		bool Read(XMLContainer & container)
		{
			pugi::xml_document XMLDocument;
			pugi::xml_parse_result result;
#ifdef _WIN32
			result = XMLDocument.load_file(m_File.GetFullPath().c_str());
#else
			AAssetManager manager(star::EventLoop::mApplicationPtr->activity->assetManager);
			AAsset* asset = AAssetManager_open(
					manager,
					star::string_cast<string>(m_File.GetFullPath()).c_str(),
					AASSET_MODE_UNKNOWN
					);
			ASSERT(asset != NULL, _T("Couldn't find this file!"));
			long size = AAsset_getLength(asset);
			char* buffer = new char[sizeof(char) * size];
			AAsset_read(asset, buffer, size);
			AAsset_close(asset);
			result = XMLDocument.load_buffer_inplace_own(buffer, size);
#endif
			ASSERT (result,
				star::string_cast<tstring>(result.description()).c_str());
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

	private:
		Filepath m_File;

		void AddAttributes(XMLContainer & element, const pugi::xml_node & node)
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

		void AddChild(XMLContainer & parent, const pugi::xml_node & node)
		{
			XMLContainer child;
			AddAttributes(child, node);
			child.SetName(star::string_cast<tstring>(node.name()));
			child.SetValue(star::string_cast<tstring>(node.child_value()));
			auto sibling = node.first_child();
			if(sibling != NULL)
			{
				do 
				{
					AddChild(child, sibling);
					sibling = sibling.next_sibling();
				} while (sibling != NULL);
			}
			parent.insert(std::make_pair(star::string_cast<tstring>(node.name()), child));
		}

		XMLFileParser(const XMLFileParser & yRef);
		XMLFileParser(XMLFileParser && yRef);
		const XMLFileParser & operator=(const XMLFileParser & yRef);
	};
}
