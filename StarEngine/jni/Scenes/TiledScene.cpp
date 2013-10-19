#include "TiledScene.h"
#include "../Input/XMLContainer.h"
#include "../Input/XMLFileParser.h"
#include "../Helpers/Helpers.h"
#include "../Objects/Object.h"

namespace star
{
	TiledScene::TiledScene(
		const tstring & name,
		const tstring & file,
		float scale )
		: BaseScene(name)
		, m_File(file)
		, m_Width(0)
		, m_Height(0)
		, m_TileWidth(0)
		, m_TileHeight(0)
		, m_TileSets()
		, m_Scale(scale)
	{

	}

	TiledScene::~TiledScene()
	{
		m_TileSets.clear();
	}

	void TiledScene::DefineSpecialObject(
		uint32 object_id, const std::function<Object*()> & func)
	{
		m_DefinedObject[object_id] = func;
	}

	status TiledScene::CreateObjects()
	{
		XMLContainer container;
		XMLFileParser parser(m_File);

		ASSERT(parser.Read(container), _T("An error occured when trying to read the level..."));

		auto mapAttributes = container.GetAttributes();
		m_Width = string_cast<uint32>(mapAttributes[_T("with")]);
		m_Height = string_cast<uint32>(mapAttributes[_T("height")]);
		m_TileWidth = string_cast<uint32>(mapAttributes[_T("tilewidth")]);
		m_TileHeight = string_cast<uint32>(mapAttributes[_T("tileheight")]);
		
		auto TSIT = container.lower_bound(_T("tileset"));
		auto tileSetend = container.upper_bound(_T("tiletset"));
		while ( TSIT != tileSetend )
		{
			auto tileSetContainer = TSIT->second;
			auto tileSetAttributes = tileSetContainer->GetAttributes();
			auto imageAttributes = tileSetContainer->at(_T("image"))->GetAttributes();

			TileSet tileSet;

			tileSet.FirstGid = string_cast<uint32>(tileSetAttributes[_T("firstgid")]);
			tileSet.TileWidth = string_cast<uint32>(tileSetAttributes[_T("tilewidth")]);
			tileSet.TileHeight = string_cast<uint32>(tileSetAttributes[_T("tileheight")]);

			tileSet.Texture = imageAttributes[_T("source")];
			tileSet.Width = string_cast<uint32>(imageAttributes[_T("width")]);
			tileSet.Height = string_cast<uint32>(imageAttributes[_T("height")]);

			m_TileSets[tileSetAttributes[_T("name")]] = tileSet;

			++TSIT;
		}

		CreateTiledObjects(container);

		CreateGroupedObjects(container);

		return STATUS_OK;
	}

	status TiledScene::AfterInitializedObjects(const star::Context& context)
	{
		return STATUS_OK;
	}

	void TiledScene::CreateTiledObjects(XMLContainer & container)
	{
		auto OIT = container.lower_bound(_T("layer"));
		auto objectsEnd = container.upper_bound(_T("layer"));

		uint32 height(0);
		while ( OIT != objectsEnd )
		{
			auto TIT = OIT->second->at(_T("data"))->lower_bound(_T("tile"));
			auto tilesEnd = OIT->second->at(_T("data"))->upper_bound(_T("tile"));

			uint32 i = 0;
			while(TIT != tilesEnd)
			{
				Object * obj = new Object();
				auto transform = obj->GetTransform();
#ifdef STAR2D
				// [TODO] Use height from layer name instead of this hack
				transform->Translate(
					( i % m_Width ) * m_Scale,
					( i / m_Width ) * m_Scale,
					height);
				transform->Scale(m_Scale, m_Scale);
				// [TODO] define texture?
#else
				transform->Translate(
					( i % m_Width ) * m_Scale,
					( i / m_Width ) * m_Scale,
					height * m_Scale );
				transform->Scale(m_Scale, m_Scale, m_Scale);
				// [TODO] define texture?
#endif
				++i;
				++TIT;
			}
			++height;
			++OIT;
		}
	}

	void TiledScene::CreateGroupedObjects(XMLContainer & container)
	{
		auto GIT = container.lower_bound(_T("objectgroup"));
		auto groupEnd = container.upper_bound(_T("objectgroup"));

		uint32 height(0);
		while ( GIT != groupEnd )
		{
			auto OIT = GIT->second->lower_bound(_T("object"));
			auto objectsEnd = GIT->second->lower_bound(_T("object"));

			uint32 i = 0;
			while(OIT != objectsEnd)
			{
				auto objAttributes = OIT->second->GetAttributes();
				Object * obj;
				uint32 objID = string_cast<uint32>(objAttributes[_T("gid")]);
				if(m_DefinedObject.find(objID) != m_DefinedObject.end())
				{
					obj = m_DefinedObject[objID]();
				}
				else
				{
					Logger::GetInstance()->Log(LogLevel::Error, 
						_T("Object with ID '") + objAttributes[_T("gid")] + _T("' wasn't defined!"));
					obj = new Object();
				}
				auto transform = obj->GetTransform();
#ifdef STAR2D
				// [TODO] Use height from layer name instead of this hack
				transform->Translate(
					( i % m_Width ) * m_Scale,
					( i / m_Width ) * m_Scale,
					height);
				transform->Scale(m_Scale, m_Scale);
#else
				transform->Translate(
					( i % m_Width ) * m_Scale,
					( i / m_Width ) * m_Scale,
					height * m_Scale );
				transform->Scale(m_Scale, m_Scale, m_Scale);
#endif
				++i;
				++OIT;
			}
			++height;
			++GIT;
		}
	}
}
