#pragma once

#include "..\Helpers\FilePath.h"
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
		XMLFileParser(const tstring & path);
		~XMLFileParser();

		bool Read(XMLContainer & container, DirectoryMode mode = DEFAULT_DIRECTORY_MODE);
		bool Read(XMLContainer & container, const tstring & binary_path,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE);

		bool ReadOrCreate(XMLContainer & container, DirectoryMode mode = DEFAULT_DIRECTORY_MODE);
		bool ReadOrCreate(XMLContainer & container, const tstring & binary_path,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE);

	private:
		FilePath m_File;

		void AddAttributes(XMLContainer & element, const pugi::xml_node & node);
		void AddChild(XMLContainer & parent, const pugi::xml_node & node);

		XMLFileParser(const XMLFileParser & yRef);
		XMLFileParser(XMLFileParser && yRef);
		const XMLFileParser & operator=(const XMLFileParser & yRef);
		const XMLFileParser & operator=(XMLFileParser&& yRef);
	};
}
