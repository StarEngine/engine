#pragma once

#include "..\defines.h"
#include "..\Helpers\Filepath.h"

namespace star
{
	class XMLContainer;

	class XMLFileSerializer
	{
	public:
		XMLFileSerializer(const tstring & full_path);
		XMLFileSerializer(const tstring & path, const tstring & file);
		~XMLFileSerializer();

		void Write(XMLContainer & container);

	private:
		Filepath m_File;
		#define TAB _T("    ")

		void WriteAtributes(tstringstream & strstr, XMLContainer & element);
		void WriteChild(tstringstream & strstr, XMLContainer & element, uint32 & tabs);

		static tstring GetTabString(uint32 & tabs);

		XMLFileSerializer(const XMLFileSerializer & yRef);
		XMLFileSerializer(XMLFileSerializer && yRef);
		const XMLFileSerializer & operator=(const XMLFileSerializer & yRef);
	};
}
