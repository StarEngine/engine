#pragma once

#include "BaseScene.h"
#include "../Helpers/Filepath.h"
#include <map>
#include <functional>

namespace star
{
	class XMLContainer;

	class TiledScene : public BaseScene
	{
	public:
		TiledScene(const tstring & name, const Filepath & file, float scale = 1.0f);
		virtual ~TiledScene();

		void DefineSpecialObject(uint32 object_id, const std::function<Object*()> & func);

	protected:
		virtual status Initialize(const Context& context);

		Filepath m_File;
		uint32 m_Width, m_Height, m_TileWidth, m_TileHeight;
		float m_Scale;

		struct TileSet
		{
			uint32 FirstGid, TileWidth, TileHeight, Width, Height;
			Filepath Texture;
		};

		std::map<tstring, TileSet> m_TileSets;
		std::map<uint32, std::function<Object*()>> m_DefinedObject;

	private:
		void CreateTiledObjects(XMLContainer & container);
		void CreateGroupedObjects(XMLContainer & container);

		TiledScene(const TiledScene& t);
		TiledScene(TiledScene&& t);
		TiledScene& operator=(const TiledScene& t);
	};
}
