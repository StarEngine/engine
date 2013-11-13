#pragma once

#include "BaseScene.h"
#include <map>
#include <functional>
#include "../Objects/FreeCamera.h"

namespace star
{
	class XMLContainer;

	class TiledScene : public BaseScene
	{
	public:
		TiledScene(const tstring & name, float scale = 1.0f);
		virtual ~TiledScene();

	protected:
		virtual void CreateObjects();
		virtual void AfterInitializedObjects(const star::Context& context);

		void CreateLevel(const tstring & file,
			DirectoryMode mode = DirectoryMode::assets);
		void CreateLevel(const tstring & file, const tstring & binary_file,
			DirectoryMode mode = DirectoryMode::assets);
		void BaseCreateLevel(XMLContainer & container);

		void DefineSpecialObject(uint32 object_id, const std::function<Object*()> & func);

		star::FreeCamera *m_pActiveCamera;

		uint32 m_Width, m_Height, m_TileWidth, m_TileHeight;
		float m_Scale;

		struct TileSet
		{
			uint32 FirstGid, TileWidth, TileHeight, Width, Height;
			tstring Texture;
		};

		std::vector<TileSet> m_TileSets;
		std::map<uint32, std::function<Object*()>> m_DefinedObject;

	private:
		void CreateTiledObjects(XMLContainer & container);
		void CreateGroupedObjects(XMLContainer & container);

		TiledScene(const TiledScene& t);
		TiledScene(TiledScene&& t);
		TiledScene& operator=(const TiledScene& t);
		TiledScene& operator=(TiledScene&& t);
	};
}
