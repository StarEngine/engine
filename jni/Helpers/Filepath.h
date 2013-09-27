#pragma once

#include "..\defines.h"

namespace star
{
	class Filepath
	{
	public:
		Filepath(const tstring & full_path);
		Filepath(const tstring & path, const tstring & file);
		Filepath(const Filepath & yRef);
		~Filepath();

		const Filepath & operator=(const Filepath & yRef);
		bool operator==(const Filepath & yRef);

		const tstring & GetPath() const;
		const tstring & GetFile() const;
		tstring GetName() const;
		tstring GetExtension() const;
		tstring GetFullPath() const;
	private:
		tstring m_Path,
				m_File;
	};
}
