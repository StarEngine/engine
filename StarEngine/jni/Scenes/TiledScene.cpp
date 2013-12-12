#include "TiledScene.h"
#include "../Input/XMLContainer.h"
#include "../Input/XMLFileParser.h"
#include "../Helpers/Helpers.h"
#include "../Objects/Object.h"
#include "../Objects/FreeCamera.h"

#include "../Components/Graphics/SpriteComponent.h"

namespace star
{
	TiledScene::TiledScene(
		const tstring & name,
		float32 scale )
		: BaseScene(name)
		, m_Width(0)
		, m_Height(0)
		, m_TileWidth(0)
		, m_TileHeight(0)
		, m_TileSets()
		, m_TiledObjects()
		, m_Scale(scale)
	{

	}

	TiledScene::~TiledScene()
	{
	}

	void TiledScene::RemoveObject(Object * object)
	{
		auto it = std::find(m_TiledObjects.begin(), m_TiledObjects.end(), object);
		if(it != m_TiledObjects.end())
		{
			m_TiledObjects.erase(it);
		}

		BaseScene::RemoveObject(object);
	}

	void TiledScene::DefineSpecialObject(
		const tstring & object_id,
		std::function<Object*(const TileObject&)> func)
	{
		m_DefinedObject[object_id] = func;
	}

	void TiledScene::GetCorrectTileset(uint32 gid, TileSet & set) const
	{
		for(auto it = m_TileSets.begin() ;
			it != m_TileSets.end() ;)
		{
			if(gid >= it->FirstGid)
			{
				auto pIt = it++;
				if(it == m_TileSets.end() ||
					gid < it->FirstGid)
				{
					set = *pIt;
					return;
				}
			}
			else
			{
				++it;
			}
		}
	}
	
	star::SpriteComponent * TiledScene::CreateSpriteFromGid(uint32 gid, const TileSet & set)
	{
		gid -= set.FirstGid;

		int32 tx(set.Width / set.TileWidth),
			ty(set.Height / set.TileHeight);

		auto texture = new SpriteComponent(
			set.Texture, 
			GetSpritesheetName(set), tx, ty);
		texture->SetCurrentSegment(gid % tx, gid / tx);

		return texture;
	}
	
	tstring TiledScene::GetSpritesheetName(const TileSet & set) const
	{
		tstring name = GetName();
		name += _T("_ts_");
		name += set.Name;
		return name;
	}
	
	TiledScene::TileObject::TileObject()
		: type(EMPTY_STRING)
		, name(EMPTY_STRING)
		, x(0)
		, y(0)
		, width(0)
		, height(0)
	{
	}

	void TiledScene::CreateObjects()
	{
		if(m_pDefaultCamera == nullptr)
		{
			auto defaultCamera = new FreeCamera();
			defaultCamera->SetStatic(false);
			defaultCamera->SetZoomEnabled(true);
			defaultCamera->SetMoveSpeed(2.0f);
			AddObject(defaultCamera);
			m_pDefaultCamera = defaultCamera;
		}
	}

	void TiledScene::AfterInitializedObjects()
	{
	}

	void TiledScene::OnActivate()
	{

	}

	void TiledScene::OnDeactivate()
	{

	}

	void TiledScene::Update(const Context& context)
	{

	}

	void TiledScene::Draw()
	{

	}

	void TiledScene::CreateLevel(const tstring & file,
		DirectoryMode mode)
	{
		XMLContainer container;
		XMLFileParser parser(file);

		Logger::GetInstance()->Log(parser.Read(container, mode),
			_T("An error occured while trying to read the level."),
			STARENGINE_LOG_TAG);

		BaseCreateLevel(container);
	}

	void TiledScene::CreateLevel(const tstring & file, const tstring & binary_file,
		DirectoryMode mode)
	{
		XMLContainer container;
		XMLFileParser parser(file);

		Logger::GetInstance()->Log(parser.Read(container, binary_file, mode),
			_T("An error occured while trying to read the level."),
			STARENGINE_LOG_TAG);

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
			set.Name = tileSetAttributes[_T("name")];

			set.Width = string_cast<uint32>(imageAttributes[_T("width")]);
			set.Height = string_cast<uint32>(imageAttributes[_T("height")]);

			m_TileSets.push_back(set);

			++TST;
		} while(TST != TSET);

		CreateTiledObjects(container);

		CreateGroupedObjects(container);
	}

	void TiledScene::ClearLevel()
	{
		for(auto obj : m_TiledObjects)
		{
			RemoveObject(obj);
		}
		m_TiledObjects.clear();
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
			Logger::GetInstance()->Log(lpIT != lpEnd,
				_T("This layer has no properties. Make sure to define all necacary properties!"),
				STARENGINE_LOG_TAG);
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

			float32 sX(m_Scale * m_TileWidth);
			float32 sY(m_Scale * m_TileHeight);

			uint32 i = 0;
			while(TIT != tilesEnd)
			{
				uint32 tID = string_cast<int32>(TIT->second->GetAttributes().at(_T("gid")));
				if(tID != 0)
				{
					TileSet tileSet;

					GetCorrectTileset(tID, tileSet);

					Object * obj = new Object();
					auto transform = obj->GetTransform();
					float32 x((i % m_Width) * sX);
					float32 y((m_Height - (i / m_Width) - 1) * sY);
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

					auto texture = CreateSpriteFromGid(tID, tileSet);
					obj->AddComponent(texture);
					AddObject(obj);
					m_TiledObjects.push_back(obj);
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

		while ( GIT != groupEnd )
		{
			auto OIT = GIT->second->lower_bound(_T("object"));
			auto objectsEnd = GIT->second->upper_bound(_T("object"));

			auto objectProperties = GIT->second->at(_T("properties"));
			auto opIT = objectProperties->lower_bound(_T("property"));
			auto opEnd = objectProperties->upper_bound(_T("property"));
			Logger::GetInstance()->Log(opIT != opEnd,
				_T("[TILED] This Object Group has no properties. Make sure to define all necacary properties!"),
				STARENGINE_LOG_TAG);
			do
			{
				auto attributes = opIT->second->GetAttributes();
				auto name = attributes.at(_T("name"));
				if(name == _T("height"))
				{
					height = string_cast<int32>(attributes.at(_T("value")));
				}
				++opIT;
			} while(opIT != opEnd);

			while(OIT != objectsEnd)
			{
				auto objAttributes = OIT->second->GetAttributes();
				Object * obj;
				TileObject tObj;

				const auto rGID = objAttributes.lower_bound(_T("gid"));
				if(rGID != objAttributes.end())
				{
					tObj.id = string_cast<int32>(rGID->second);
				}

				const auto rX = objAttributes.lower_bound(_T("x"));
				if(rX != objAttributes.end())
				{
					tObj.x = int32(string_cast<int32>(rX->second) * m_Scale);
				}

				const auto rY = objAttributes.lower_bound(_T("y"));
				if(rY != objAttributes.end())
				{
					tObj.y = int32(string_cast<int32>(rY->second) * m_Scale);
					tObj.y = int32((m_Height * m_TileHeight * m_Scale) - tObj.y);
				}

				const auto rWidth = objAttributes.lower_bound(_T("width"));
				if(rWidth != objAttributes.end())
				{
					tObj.width = int32(string_cast<uint32>(rWidth->second) * m_Scale);
				}
				else
				{
					tObj.width = int32(m_TileWidth * m_Scale);
				}

				const auto rHeight = objAttributes.lower_bound(_T("height"));
				if(rHeight != objAttributes.end())
				{
					tObj.height = int32(string_cast<uint32>(rHeight->second) * m_Scale);
				}
				else
				{
					tObj.width = int32(m_TileHeight * m_Scale);
				}

				tObj.y -= tObj.height;

				const auto rName = objAttributes.lower_bound(_T("name"));
				if(rName != objAttributes.end())
				{
					tObj.name = rName->second;
				}

				const auto rType = objAttributes.lower_bound(_T("type"));
				bool foundType = rType != objAttributes.end();
				Logger::GetInstance()->Log(foundType,
					_T("[TILED] Couldn't find the type of the object. Please define this!"),
					STARENGINE_LOG_TAG);
				if(foundType)
				{
					tObj.type = rType->second;
				}

				if(m_DefinedObject.find(tObj.type) != m_DefinedObject.end())
				{
					obj = m_DefinedObject[tObj.type](tObj);

					auto transform = obj->GetTransform();
				#ifdef STAR2D
					// [TODO] Use height from layer name instead of this hack
					transform->Translate(
						float32(tObj.x),
						float32(tObj.y),
						height);
					transform->Scale(m_Scale, m_Scale);
	#else
					transform->Translate(
						tObj.x,
						tObj.y,
						height);
					transform->Scale(m_Scale, m_Scale, m_Scale);
	#endif
					AddObject(obj);
					m_TiledObjects.push_back(obj);
				}
				else
				{
					Logger::GetInstance()->Log(LogLevel::Error, 
						_T("[TILED] Object with type '") + tObj.type + _T("' wasn't defined!"),
						STARENGINE_LOG_TAG);
				}
				++OIT;
			}
			++height;
			++GIT;
		}
	}
}
