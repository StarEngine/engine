#pragma once

#include "..\defines.h"
#include "..\Helpers\FilePath.h"

namespace star
{
	class XMLContainer;

	class XMLFileSerializer final
	{
	public:
		XMLFileSerializer(const tstring & path,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE);
		~XMLFileSerializer();

		void Write(XMLContainer & container);
		void Write(
			XMLContainer & container,
			const tstring & binaryPath
			);

	private:
		FilePath m_File;

		tstring WriteFile(XMLContainer & container);

		void WriteAtributes(tstringstream & strstr, XMLContainer & element);
		void WriteChild(tstringstream & strstr, XMLContainer & element, uint32 & tabs);

		static tstring GetTabString(uint32 & tabs);

		XMLFileSerializer(const XMLFileSerializer & yRef);
		XMLFileSerializer(XMLFileSerializer && yRef);
		XMLFileSerializer & operator=(const XMLFileSerializer & yRef);
		XMLFileSerializer & operator=(XMLFileSerializer&& yRef);
	};
}
