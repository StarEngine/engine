#include "GameData.h"
#include "Helpers.h"
#include "../Input/XMLFileParser.h"
#include "../Input/XMLFileSerializer.h"
#include "../Scenes/BaseScene.h"
#include "../Scenes/SceneManager.h"

namespace star
{
	const tstring GameData::DEFAULT_DATA_GROUP = _T("general");
	const tstring GameData::UNIQUE_ID_PREFIX = _T("GameData_SW_");
	uint64 GameData::UNIQUE_ID_COUNTER = 0;

	GameData::GameData(
		const tstring & file,
		BaseScene * pScene,
		DirectoryMode mode
		)
		: m_Data()
		, m_File(file)
		, m_BinaryFile(EMPTY_STRING)
		, m_UniqueID(
			UNIQUE_ID_PREFIX +
			string_cast<tstring>(UNIQUE_ID_COUNTER++)
			)
		, m_DirectoryMode(mode)
		, m_AutoSaveEnabled(false)
		, m_AutoSaveSeconds(0)
		, m_pScene(pScene)
	{
		Load();
	}

	GameData::GameData(
		const tstring & file,
		const tstring & binaryFile,
		BaseScene * pScene,
		DirectoryMode mode
		)
		: m_Data()
		, m_File(file)
		, m_BinaryFile(binaryFile)
		, m_UniqueID(
			UNIQUE_ID_PREFIX +
			string_cast<tstring>(UNIQUE_ID_COUNTER++)
			)
		, m_DirectoryMode(mode)
		, m_AutoSaveEnabled(false)
		, m_AutoSaveSeconds(0)
		, m_pScene(pScene)
	{
		Load();
	}

	GameData::GameData(const GameData & yRef)
		: m_Data(yRef.m_Data)
		, m_File(yRef.m_File)
		, m_BinaryFile(yRef.m_BinaryFile)
		, m_UniqueID(
			UNIQUE_ID_PREFIX +
			string_cast<tstring>(UNIQUE_ID_COUNTER++)
			)
		, m_DirectoryMode(yRef.m_DirectoryMode)
		, m_AutoSaveEnabled(yRef.m_AutoSaveEnabled)
		, m_AutoSaveSeconds(yRef.m_AutoSaveSeconds)
		, m_pScene(yRef.m_pScene)
	{
		if(m_AutoSaveEnabled)
		{
			SetAutoSaveEnabled(true, m_AutoSaveSeconds);
		}
	}

	GameData::GameData(GameData && yRef)
		: m_Data(yRef.m_Data)
		, m_File(yRef.m_File)
		, m_BinaryFile(yRef.m_BinaryFile)
		, m_UniqueID(
			UNIQUE_ID_PREFIX +
			string_cast<tstring>(UNIQUE_ID_COUNTER++)
			)
		, m_DirectoryMode(yRef.m_DirectoryMode)
		, m_AutoSaveEnabled(yRef.m_AutoSaveEnabled)
		, m_AutoSaveSeconds(yRef.m_AutoSaveSeconds)
		, m_pScene(yRef.m_pScene)
	{
		if(m_AutoSaveEnabled)
		{
			SetAutoSaveEnabled(true, m_AutoSaveSeconds);
		}
	}

	GameData::~GameData()
	{

	}

	GameData & GameData::operator=(const GameData & yRef)
	{
		m_Data = yRef.m_Data;
		m_File = yRef.m_File;
		m_BinaryFile = yRef.m_BinaryFile;
		m_UniqueID =
			UNIQUE_ID_PREFIX +
			string_cast<tstring>(UNIQUE_ID_COUNTER++);
		m_DirectoryMode = yRef.m_DirectoryMode;
		m_AutoSaveEnabled = yRef.m_AutoSaveEnabled;
		m_AutoSaveSeconds = yRef.m_AutoSaveSeconds;
		m_pScene = yRef.m_pScene;
		if(m_AutoSaveEnabled)
		{
			SetAutoSaveEnabled(true, m_AutoSaveSeconds);
		}

		return *this;
	}

	GameData & GameData::operator=(GameData && yRef)
	{
		m_Data = yRef.m_Data;
		m_File = yRef.m_File;
		m_BinaryFile = yRef.m_BinaryFile;
		m_UniqueID =
			UNIQUE_ID_PREFIX +
			string_cast<tstring>(UNIQUE_ID_COUNTER++);
		m_DirectoryMode = yRef.m_DirectoryMode;
		m_AutoSaveEnabled = yRef.m_AutoSaveEnabled;
		m_AutoSaveSeconds = yRef.m_AutoSaveSeconds;
		m_pScene = yRef.m_pScene;
		if(m_AutoSaveEnabled)
		{
			SetAutoSaveEnabled(true, m_AutoSaveSeconds);
		}
		
		return *this;
	}

	void GameData::Load()
	{
		XMLFileParser parser(m_File);
		if(m_BinaryFile != EMPTY_STRING)
		{
			parser.Read(m_Data, m_BinaryFile, m_DirectoryMode);
		}
		else
		{
			parser.Read(m_Data, m_DirectoryMode);
		}
	}

	void GameData::Save()
	{
		XMLFileSerializer serializer(m_File);
		if(m_BinaryFile != EMPTY_STRING)
		{
			serializer.Write(m_Data, m_BinaryFile, m_DirectoryMode);
		}
		else
		{
			serializer.Write(m_Data, m_DirectoryMode);
		}
	}

	void GameData::SetAutoSaveEnabled(bool enable, float32 seconds)
	{
		std::shared_ptr<Stopwatch> watch(nullptr);
		if(m_pScene)
		{
			watch = m_pScene->GetStopwatch();
		}
		else
		{
			watch = SceneManager::GetInstance()->GetStopwatch();
		}
		if(enable)
		{
			if(m_AutoSaveEnabled)
			{
				watch->SetTargetTimeTimer(
					m_UniqueID,
					seconds
					);
			}
			else
			{
				watch->CreateTimer(
					m_UniqueID,
					seconds,
					false,
					true,
					[&] () 
					{
						Save();
					},
					false
					);
			}
		}
		else if(m_AutoSaveEnabled)
		{
			watch->RemoveTimer(m_UniqueID);
		}
		m_AutoSaveEnabled = enable;
		m_AutoSaveSeconds = seconds;
	}
}
