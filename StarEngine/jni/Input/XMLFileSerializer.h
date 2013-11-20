#pragma once

#include "..\defines.h"
#include "..\Helpers\Filepath.h"

namespace star
{
	class XMLContainer;

	class XMLFileSerializer final
	{
	public:
		XMLFileSerializer(const tstring & path);
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
		const XMLFileSerializer & operator=(XMLFileSerializer&& yRef);
	};
}
