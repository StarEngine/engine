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

	static const uint8 FILE_ERROR = 0;
	static const uint8 FILE_READ = 1;
	static const uint8 FILE_WRITE = 2;

	class XMLFileParser
	{
	public:
		XMLFileParser(const tstring & path,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE);
		~XMLFileParser();

		bool Read(XMLContainer & container);
		bool Read(XMLContainer & container, const tstring & binary_path);

		uint8 ReadOrCreate(
			XMLContainer & container,
			const tstring & rootName
			);
		uint8 ReadOrCreate(
			XMLContainer & container,
			const tstring & rootName,
			const tstring & binary_path
			);

	private:

		FilePath m_File;

		void AddAttributes(XMLContainer & element, const pugi::xml_node & node);
		void AddChild(XMLContainer & parent, const pugi::xml_node & node);

		XMLFileParser(const XMLFileParser & yRef);
		XMLFileParser(XMLFileParser && yRef);
		XMLFileParser & operator=(const XMLFileParser & yRef);
		XMLFileParser & operator=(XMLFileParser&& yRef);
	};
}
