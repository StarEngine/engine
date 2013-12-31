#pragma once

#include "../defines.h"
#include "../Input/XMLContainer.h"

namespace star
{
	class BaseScene;
	
	class GameData final
	{
	public:
		GameData(
			const tstring & file,
			BaseScene * pScene = nullptr,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE
			);
		GameData(
			const tstring & file,
			const tstring & binaryFile,
			BaseScene * pScene = nullptr,
			DirectoryMode mode = DEFAULT_DIRECTORY_MODE
			);
		GameData(const GameData & yRef);
		GameData(GameData && yRef);

		~GameData();

		GameData & operator=(const GameData & yRef);
		GameData & operator=(GameData && yRef);

		void Load();
		void Save();

		template <typename T>
		T GetData(
			const tstring & name,
			const tstring & group = DEFAULT_DATA_GROUP
			);
		
		template <typename T>
		void SetData(
			const tstring & name,
			const T & value,
			const tstring & group = DEFAULT_DATA_GROUP
			);

		void SetAutoSaveEnabled(bool enable, float32 seconds = 60.0f);

	private:
		static const tstring DEFAULT_DATA_GROUP;
		static const tstring UNIQUE_ID_PREFIX;
		static uint64 UNIQUE_ID_COUNTER;

		XMLContainer m_Data;
		tstring m_File, m_BinaryFile, m_UniqueID;
		DirectoryMode m_DirectoryMode;
		bool m_AutoSaveEnabled;
		float32 m_AutoSaveSeconds;
		BaseScene *m_pScene;
	};
}

#include "GameData.inl"
