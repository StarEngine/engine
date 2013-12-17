#pragma once

#include "..\defines.h"

namespace star
{
	/// <summary>
	/// A class that is mostly used internally in the engine.
	/// It allows you to get the full static path, of several locations.
	/// It allows you to get the extension and filename of the filepath.
	/// </summary>
	class FilePath final
	{
	public:
		/// <summary>
		/// Default constructor for the filepath,
		/// assigning an EMPTY_STRING value to all datamembers.
		/// </summary>
		FilePath();
		/// <summary>
		/// Constructor overload requiring a string of the full filepath,
		/// starting from the root directory.
		/// </summary>
		explicit FilePath(const tstring & full_path);
		/// <summary>
		/// Overload of the constructor requiring the path and filename,
		/// which will combined be the full path starting from he root directory.
		/// </summary>
		/// <param name="path">the directory part of the filepath</param>
		/// <param name="file">the filename including the extension</param>
		FilePath(const tstring & path, const tstring & file);
		/// <summary>
		/// An overload of the constructor requiring the reference
		/// of an FilePath object where the datamembers will be copped from.
		/// </summary>
		/// <param name="yRef">a reference of a FilePath object</param>
		FilePath(const FilePath & yRef);
		/// <summary>
		/// Cleans up the path and file tstring datamembers.
		/// </summary>
		~FilePath();

		/// <summary>
		/// Copy the path and file tstring datamembers.
		/// </summary>
		/// <param name="yRef">a reference of a FilePath object</param>
		/// <returns>a reference to the object where
		/// assignment operator get invoked off.</returns>
		FilePath & operator=(const FilePath & yRef);
		/// <summary>
		/// Comparing the path and file tstrings combining it into a boolean result.
		/// </summary>
		/// <param name="yRef">a reference of a FilePath object</param>
		/// <returns>true if the yRef object and the current invoked object are equal</returns>
		bool operator==(const FilePath & yRef);

		/// <summary>
		/// Get the path variable of the filepath.
		/// </summary>
		/// <returns>a const reference to the path datamember.</returns>
		const tstring & GetPath() const;
		/// <summary>
		/// Get the file variable of the filepath.
		/// </summary>
		/// <returns>a const reference to the file datamember.</returns>
		const tstring & GetFile() const;
		/// <summary>
		/// Get the name of the file without the extension part.
		/// </summary>
		/// <returns>the name of the file hidden in the filepath</returns>
		tstring GetName() const;
		/// <summary>
		/// Get the extension of the file hidden in the filepath
		/// </summary>
		/// <returns>the extension of the file</returns>
		tstring GetExtension() const;
		/// <summary>
		/// Get the complete local path which is equal
		/// to a combination of the path and file datamembers.
		/// </summary>
		/// <returns>the complete local path</returns>
		tstring GetLocalPath() const;
		/// <summary>
		/// Get the complete dynamic path with the root being used,
		/// as defined as in the assets enumeration value of DirectoryMode.
		/// </summary>
		/// <returns>the complete dynamic path, combining the 
		/// assets directory and the full local path.</returns>
		/// <seealso cref="DirectoryMode"></seealso>
		tstring GetAssetsPath() const;
		/// <summary>
		/// Get the complete dynamic path with the root being used,
		/// as defined as in the internal enumeration value of DirectoryMode.
		/// </summary>
		/// <returns>the complete dynamic path, combining the 
		/// internal directory and the full local path.</returns>
		/// <seealso cref="DirectoryMode"></seealso>
		tstring GetInternalPath() const;
		/// <summary>
		/// Get the complete dynamic path with the root being used,
		/// as defined as in the external enumeration value of DirectoryMode.
		/// </summary>
		/// <returns>the complete dynamic path, combining the 
		/// external directory and the full local path.</returns>
		/// <seealso cref="DirectoryMode"></seealso>
		tstring GetExternalPath() const;
		/// <summary>
		/// Get the correct complete dynamic path with the root being used,
		/// defined based on the mode value.
		/// </summary>
		/// <returns>the complete dynamic path, combining the 
		/// directory defined by the mode value and the full local path.</returns>
		/// <seealso cref="DirectoryMode"></seealso>
		static void GetCorrectPath(const tstring & path,
			tstring & correct_path, DirectoryMode mode);

#ifdef DESKTOP
		/// <summary>
		/// Sets the static datamember that represents the assets root directory.
		/// </summary>
		/// <param name="root">the path of the assets directory</param>
		static void SetAssetsRoot(const tstring & root);
		/// <summary>
		/// Sets the static datamember that represents the internal root directory.
		/// </summary>
		/// <param name="root">the path of the internal directory</param>
		static void SetInternalRoot(const tstring & root);
		/// <summary>
		/// Sets the static datamember that represents the external root directory.
		/// </summary>
		/// <param name="root">the path of the external directory</param>
		static void SetExternalRoot(const tstring & root);
#endif

	private:
		tstring m_Path,
				m_File;
#ifdef DESKTOP
		static tstring m_AssetsRoot, m_InternalRoot, m_ExternalRoot;
#endif
#ifdef _WIN32
		/// <summary>
		/// A deprecated function to get the static capital-sensitive path
		/// of the current file.
		/// </summary>
		/// <param name="path">the path to be checked</param>
		/// <returns>the correct capital-sensitive static path</returns>
		tstring GetActualPathName(const tstring& path) const;
#endif
	};
}
