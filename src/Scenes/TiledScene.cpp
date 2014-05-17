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
		const std::function<Object*(const TileObject&)> & func)
	{
		if(m_DefinedObject.find(object_id) != m_DefinedObject.end())
		{
			LOG(LogLevel::Warning,
				_T("TiledScene::DefineSpecialObject: Overriding definition for object '")
				+ object_id + _T("'."));
		}
		m_DefinedObject[object_id] = func;
	}

	void TiledScene::ExtendTile(uint32 tileID,
		const std::function<void(Object*)> & func)
	{
		if(m_ExtensionTiles.find(tileID) != m_ExtensionTiles.end())
		{
			LOG(LogLevel::Warning,
				_T("TiledScene::ExtendTile: Overriding extension for tile '")
				+ string_cast<tstring>(tileID) + _T("'."));
		}
		m_ExtensionTiles[tileID] = func;
	}

	void TiledScene::ExtendTiles(uint32 * tileIDArray, uint32 size,
		const std::function<void(Object*)> & func)
	{
		for(uint32 i = 0 ; i < size ; ++i)
		{
			ExtendTile(tileIDArray[i], func);
		}
	}

	void TiledScene::GetCorrectTileset(uint32 gid, TileSet & set) const
	{
		for(auto it = m_TileSets.begin() ;
			it != m_TileSets.end() ;)
		{
			if(gid >= it->firstGid)
			{
				auto pIt = it++;
				if(it == m_TileSets.end() ||
					gid < it->firstGid)
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
		gid -= set.firstGid;

		int32 tx(set.width / set.tileWidth),
			ty(set.height / set.tileHeight);

		auto texture = new SpriteComponent(
			set.texture, 
			GetSpritesheetName(set), tx, ty);
		texture->SetCurrentSegment(gid % tx, gid / tx);

		return texture;
	}
	
	tstring TiledScene::GetSpritesheetName(const TileSet & set) const
	{
		tstring name = GetName();
		name += _T("_ts_");
		name += set.name;
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
		XMLFileParser parser(file, mode);

		ASSERT_LOG(parser.Read(container),
			_T("An error occured while trying to read the level."),
			STARENGINE_LOG_TAG);

		BaseCreateLevel(container);
	}

	void TiledScene::CreateLevel(const tstring & file, const tstring & binary_file,
		DirectoryMode mode)
	{
		XMLContainer container;
		XMLFileParser parser(file, mode);

		ASSERT_LOG(parser.Read(container, binary_file),
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

			set.firstGid = string_cast<uint32>(tileSetAttributes[_T("firstgid")]);
			set.tileWidth = string_cast<uint32>(tileSetAttributes[_T("tilewidth")]);
			set.tileHeight = string_cast<uint32>(tileSetAttributes[_T("tileheight")]);

			set.texture = imageAttributes[_T("source")];
			set.name = tileSetAttributes[_T("name")];

			set.width = string_cast<uint32>(imageAttributes[_T("width")]);
			set.height = string_cast<uint32>(imageAttributes[_T("height")]);

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
		auto objectIterator = container.lower_bound(_T("layer"));
		auto objectsEnd = container.upper_bound(_T("layer"));

		tstring tsName = GetName() + _T("_tileset_default");

		int32 height(0);
		while (objectIterator != objectsEnd)
		{
			auto tilesIterator = objectIterator->second->at(_T("data"))->lower_bound(_T("tile"));
			auto tilesEnd = objectIterator->second->at(_T("data"))->upper_bound(_T("tile"));

			auto layerProperties = objectIterator->second->at(_T("properties"));
			auto layerProperteriesIterator = layerProperties->lower_bound(_T("property"));
			auto layerPropertiesEnd = layerProperties->upper_bound(_T("property"));
			ASSERT_LOG(layerProperteriesIterator != layerPropertiesEnd,
				_T("This layer has no properties. Make sure to define all necessairy properties!"),
				STARENGINE_LOG_TAG);
			do
			{
				auto attributes = layerProperteriesIterator->second->GetAttributes();
				auto name = attributes.at(_T("name"));
				if(name == _T("height"))
				{
					height = string_cast<int32>(attributes.at(_T("value")));
				}
				++layerProperteriesIterator;
			} while(layerProperteriesIterator != layerPropertiesEnd);

			float32 sX(m_Scale * m_TileWidth);
			float32 sY(m_Scale * m_TileHeight);

			uint32 i = 0;
			while(tilesIterator != tilesEnd)
			{
				uint32 tID = string_cast<int32>(tilesIterator->second->GetAttributes().at(_T("gid")));
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
						height
						);
					transform->Scale(m_Scale, m_Scale);
				#else
					transform->Translate(
						x,
						y,
						height * m_Scale
						);
					transform->Scale(m_Scale, m_Scale, m_Scale);
				#endif

					auto texture = CreateSpriteFromGid(tID, tileSet);
					obj->AddComponent(texture);

					if(m_ExtensionTiles.find(tID) != m_ExtensionTiles.end())
					{
						m_ExtensionTiles[tID](obj);
					}
					obj->SetName(_T("tile_") + string_cast<tstring>(height) +
						_T("_") + string_cast<tstring>(i));
					AddObject(obj);
					m_TiledObjects.push_back(obj);
				}
				++i;
				++tilesIterator;
			}
			++objectIterator;
		}
	}

	void TiledScene::CreateGroupedObjects(XMLContainer & container)
	{
		auto groupIterator = container.lower_bound(_T("objectgroup"));
		auto groupEnd = container.upper_bound(_T("objectgroup"));

		uint32 height(0);

		while ( groupIterator != groupEnd )
		{
			auto objectIterator = groupIterator->second->lower_bound(_T("object"));
			auto objectsEnd = groupIterator->second->upper_bound(_T("object"));

			auto objectProperties = groupIterator->second->at(_T("properties"));
			auto objectPropertiesIterator = objectProperties->lower_bound(_T("property"));
			auto objectPropertiesEnd = objectProperties->upper_bound(_T("property"));
			ASSERT_LOG(objectPropertiesIterator != objectPropertiesEnd,
				_T("TiledScene::CreateGroupedObjects: This Object Group has no properties. \
Make sure to define all necacary properties!"),
				STARENGINE_LOG_TAG);
			do
			{
				auto attributes = objectPropertiesIterator->second->GetAttributes();
				auto name = attributes.at(_T("name"));
				if(name == _T("height"))
				{
					height = string_cast<int32>(attributes.at(_T("value")));
				}
				++objectPropertiesIterator;
			} while(objectPropertiesIterator != objectPropertiesEnd);

			while(objectIterator != objectsEnd)
			{
				auto objAttributes = objectIterator->second->GetAttributes();
				Object * obj;
				TileObject tObj;

				const auto objectGlobalIDIterator = objAttributes.lower_bound(_T("gid"));
				if(objectGlobalIDIterator != objAttributes.end())
				{
					tObj.id = string_cast<int32>(objectGlobalIDIterator->second);
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
				ASSERT_LOG(foundType,
					_T("TiledScene::CreateGroupedObjects: Couldn't find the type of the object. Please define this!"),
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
					LOG(LogLevel::Error, 
						_T("TiledScene::CreateGroupedObjects: \
Object with type '") + tObj.type + _T("' wasn't defined!"),
						STARENGINE_LOG_TAG);
				}
				++objectIterator;
			}
			++height;
			++groupIterator;
		}
	}
}
