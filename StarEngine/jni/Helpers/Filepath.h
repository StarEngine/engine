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
		/// <param name="full_path">a reference of a FilePath object</param>
		/// <param name="mode">the mode to be used, defining the root directory</param>
		explicit FilePath(const tstring & full_path,
			DirectoryMode mode = DirectoryMode::assets);
		/// <summary>
		/// An overload of the constructor requiring the reference
		/// of an FilePath object where the datamembers will be copped from.
		/// </summary>
		/// <param name="yRef">a reference of a FilePath object</param>
		FilePath(const FilePath & yRef);
		/// <summary>
		/// An overload of the constructor requiring 
		/// a FilePath object where the datamembers will be moved from.
		/// </summary>
		/// <param name="yRef">the FilePath object to be moved</param>
		FilePath(FilePath && yRef);
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
		/// Move the path and file tstring datamembers.
		/// </summary>
		/// <param name="yRef"> a FilePath object to be moved</param>
		/// <returns>a reference to the object where
		/// assignment operator get invoked off.</returns>
		FilePath & operator=(FilePath && yRef);
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
		/// Get the root of the path, using the correct DirectoryMode.
		/// </summary>
		/// <returns>the root of the path</returns>
		/// <seealso cref="DirectoryMode"></seealso>
		tstring GetRoot() const;
		/// <summary>
		/// Get the complete local path which is equal
		/// to a combination of the path and file datamembers.
		/// </summary>
		/// <returns>the complete local path</returns>
		tstring GetLocalPath() const;
		/// <summary>
		/// Get the correct complete dynamic path with the root being used,
		/// defined based on the mode value.
		/// <param name="correct_path">the complete dynamic path, combining the 
		/// directory defined by the mode value and the full local path.</param>
		/// </summary>
		/// <seealso cref="DirectoryMode"></seealso>
		void GetFullPath(tstring & correct_path) const;
		/// <summary>
		/// Get the correct complete dynamic path with the root being used,
		/// defined based on the mode value.
		/// </summary>
		/// <returns>the complete dynamic path, combining the 
		/// directory defined by the mode value and the full local path.</returns>
		/// <seealso cref="DirectoryMode"></seealso>
		tstring GetFullPath() const;
		/// <summary>
		/// Gets the directory mode.
		/// </summary>
		/// <returns>The directory mode defined in the constructor</returns>
		DirectoryMode GetDirectoryMode() const;

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
		DirectoryMode m_DirectoryMode;


		/// <summary>
		/// Checks if the path is capital correct.
		/// This check is important for unix based operating system, 
		/// as their file system is capital sensitive.
		/// </summary>
		/// <param name="path">The path.</param>
		void CheckIfPathIsCapitalCorrect(const tstring & path);
		/// <summary>
		/// A function to get the static capital-sensitive path
		/// of the current file.
		/// </summary>
		/// <param name="pathIn">the path to be checked</param>
		/// <param name="pathOut">the correct capital-sensitive static path</param>
		/// <returns>True if the file existed, false if the file didnt exist.</returns>
		static bool GetActualPathName(const tstring & pathIn, tstring & pathOut);
		/// <summary>
		/// For windows: Converts all / seperators to \\ seperators.
		/// For android and linux: Converts all \\ seperators to / seperators.
		/// </summary>
		/// <param name="path">The path to convert.</param>
		static void ConvertPathToCorrectPlatformStyle(tstring & path);
	};
}
