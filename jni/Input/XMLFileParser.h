#pragma once

#include "..\Helpers\Filepath.h"
#include "..\defines.h"

namespace pugi
{
	class xml_node;
}

namespace star
{
	class XMLContainer;

	class XMLFileParser
	{
	public:
		XMLFileParser(const tstring & full_path);
		XMLFileParser(const tstring & path, const tstring & file);
		~XMLFileParser();

		bool Read(XMLContainer & container);

	private:
		Filepath m_File;

		void AddAttributes(XMLContainer & element, const pugi::xml_node & node);
		void AddChild(XMLContainer & parent, const pugi::xml_node & node);

		XMLFileParser(const XMLFileParser & yRef);
		XMLFileParser(XMLFileParser && yRef);
		const XMLFileParser & operator=(const XMLFileParser & yRef);
	};
}
