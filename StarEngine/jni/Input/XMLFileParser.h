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
		XMLFileParser(const tstring & path);
		~XMLFileParser();

		bool Read(XMLContainer & container, DirectoryMode mode = DEFAULT_DIRECTORY_MODE);
		bool Read(XMLContainer & container, const tstring & binary_path,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE);

		uint8 ReadOrCreate(
			XMLContainer & container,
			const tstring & rootName,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE
			);
		uint8 ReadOrCreate(
			XMLContainer & container,
			const tstring & rootName,
			const tstring & binary_path,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE
			);

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
