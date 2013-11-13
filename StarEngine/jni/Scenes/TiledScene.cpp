#include "TiledScene.h"
#include "../Input/XMLContainer.h"
#include "../Input/XMLFileParser.h"
#include "../Helpers/Helpers.h"
#include "../Objects/Object.h"

#include "../Components/Graphics/SpriteComponent.h"

namespace star
{
	TiledScene::TiledScene(
		const tstring & name,
		float scale )
		: BaseScene(name)
		, m_pActiveCamera(nullptr)
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
	}

	void TiledScene::DefineSpecialObject(
		uint32 object_id, const std::function<Object*()> & func)
	{
		m_DefinedObject[object_id] = func;
	}

	void TiledScene::CreateObjects()
	{
		if(m_pActiveCamera == nullptr)
		{
			m_pActiveCamera = new FreeCamera();
			AddObject(m_pActiveCamera);
		}
	}

	void TiledScene::AfterInitializedObjects(const star::Context& context)
	{
	
	}

	void TiledScene::CreateLevel(const tstring & file,
		DirectoryMode mode)
	{
		XMLContainer container;
		XMLFileParser parser(file);

		ASSERT(parser.Read(container, mode), _T("An error occured while trying to read the level."));

		BaseCreateLevel(container);
	}

	void TiledScene::CreateLevel(const tstring & file, const tstring & binary_file,
		DirectoryMode mode)
	{
		XMLContainer container;
		XMLFileParser parser(file);

		ASSERT(parser.Read(container, binary_file, mode), _T("An error occured while trying to read the level."));

		BaseCreateLevel(container);
	}
	
	void TiledScene::BaseCreateLevel(XMLContainer & container)
	{
		auto mapAttributes = container.GetAttributes();
		m_Width = string_cast<uint32>(mapAttributes[_T("width")]);
		m_Height = string_cast<uint32>(mapAttributes[_T("height")]);
		m_TileWidth = string_cast<uint32>(mapAttributes[_T("tilewidth")]);
		m_TileHeight = string_cast<uint32>(mapAttributes[_T("tileheight")]);
		
		auto TST = container.lower_bound(_T("tileset"));
		auto TSET = container.upper_bound(_T("tileset"));

		do
		{
			auto tileSetContainer = TST->second;
			auto tileSetAttributes = tileSetContainer->GetAttributes();
			auto imageAttributes = tileSetContainer->at(_T("image"))->GetAttributes();

			TileSet set;

			set.FirstGid = string_cast<uint32>(tileSetAttributes[_T("firstgid")]);
			set.TileWidth = string_cast<uint32>(tileSetAttributes[_T("tilewidth")]);
			set.TileHeight = string_cast<uint32>(tileSetAttributes[_T("tileheight")]);

			set.Texture = imageAttributes[_T("source")];
			set.Width = string_cast<uint32>(imageAttributes[_T("width")]);
			set.Height = string_cast<uint32>(imageAttributes[_T("height")]);

			m_TileSets.push_back(set);

			++TST;
		} while(TST != TSET);

		CreateTiledObjects(container);

		CreateGroupedObjects(container);
	}

	void TiledScene::CreateTiledObjects(XMLContainer & container)
	{
		auto OIT = container.lower_bound(_T("layer"));
		auto objectsEnd = container.upper_bound(_T("layer"));

		tstring tsName = GetName() + _T("_tileset_default");

		int32 height(0);
		while ( OIT != objectsEnd )
		{
			auto TIT = OIT->second->at(_T("data"))->lower_bound(_T("tile"));
			auto tilesEnd = OIT->second->at(_T("data"))->upper_bound(_T("tile"));

			auto layerProperties = OIT->second->at(_T("properties"));
			auto lpIT = layerProperties->lower_bound(_T("property"));
			auto lpEnd = layerProperties->upper_bound(_T("property"));
			ASSERT(lpIT != lpEnd, _T("This layer has no properties. Make sure to define all necacary properties!"));
			do
			{
				auto attributes = lpIT->second->GetAttributes();
				auto name = attributes.at(_T("name"));
				if(name == _T("height"))
				{
					height = string_cast<int32>(attributes.at(_T("value")));
				}
				++lpIT;
			} while(lpIT != lpEnd);

			float sX(m_Scale * m_TileWidth);
			float sY(m_Scale * m_TileHeight);

			uint32 i = 0;
			while(TIT != tilesEnd)
			{
				uint32 tID = string_cast<int>(TIT->second->GetAttributes().at(_T("gid")));
				if(tID != 0)
				{
					int tempID(tID);
					TileSet tileSet;
					for(auto it = m_TileSets.begin() ;
						it != m_TileSets.end() ;)
					{
						if(tID >= it->FirstGid)
						{
							auto pIt = it++;
							if(it == m_TileSets.end() ||
								tID < it->FirstGid)
							{
								tileSet = *pIt;
							}
						}
						else
						{
							++it;
						}
					}

					tID -= tileSet.FirstGid;

					Object * obj = new Object();
					auto transform = obj->GetTransform();
					float x((i % m_Width) * sX);
					float y((m_Height - (i / m_Width) - 1) * sY);
				#ifdef STAR2D
					// [TODO] Use height from layer name instead of this hack
					transform->Translate(
						x,
						y,
						height);
					transform->Scale(m_Scale, m_Scale);
				#else
					transform->Translate(
						x,
						y,
						height * m_Scale );
					transform->Scale(m_Scale, m_Scale, m_Scale);
				#endif
					int tx(tileSet.Width  / tileSet.TileWidth),
						ty(tileSet.Height  / tileSet.TileHeight);

					auto texture = new SpriteComponent(
						tileSet.Texture, 
						tsName, false, false, tx, ty);
					texture->SetCurrentSegment(tID % tx, tID / tx);

					obj->AddComponent(texture);
					AddObject(obj);
				}
				++i;
				++TIT;
			}
			++OIT;
		}
	}

	void TiledScene::CreateGroupedObjects(XMLContainer & container)
	{
		auto GIT = container.lower_bound(_T("objectgroup"));
		auto groupEnd = container.upper_bound(_T("objectgroup"));

		uint32 height(0);
		float sX(m_Scale * m_TileWidth);
		float sY(m_Scale * m_TileHeight);

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
					
					float x((i % m_Width) * sX);
					float y((m_Height - (i / m_Width) - 1) * sY);

					auto transform = obj->GetTransform();
				#ifdef STAR2D
					// [TODO] Use height from layer name instead of this hack
					transform->Translate(
						x,
						y,
						height);
					transform->Scale(m_Scale, m_Scale);
	#else
					transform->Translate(
						x,
						y,
						height * m_Scale );
					transform->Scale(m_Scale, m_Scale, m_Scale);
	#endif
				}
				else
				{
					Logger::GetInstance()->Log(LogLevel::Error, 
						_T("Object with ID '") + objAttributes[_T("gid")] + _T("' wasn't defined!"));
				}
				++i;
				++OIT;
			}
			++height;
			++GIT;
		}
	}
}
