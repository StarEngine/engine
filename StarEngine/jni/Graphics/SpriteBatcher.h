#pragma once
#include "../defines.h"
#include "SpriteBatchItem.h"
#include "VertexPosColTex.h"
#include <vector>
namespace star
{
	enum SpriteSortMode;

	class SpriteBatcher final
	{
	public:
		SpriteBatcher();
		~SpriteBatcher();

		SpriteBatchItem* CreateBatchItem();
		void DrawBatch(SpriteSortMode spriteSortMode);

	private:
		void CheckBuffers(uint32 nrOfBatchItems);

		static const uint32 BASE_BATCH_SIZE = 256;
		static const uint32 BASE_VERTEX_ARR_SIZE = 256;
		//6 verts per quad
		static const uint16 MAX_BATCH_SIZE = sizeof(uint16) / 6;

		std::vector<SpriteBatchItem*> m_BatchItemVec;
		std::vector<SpriteBatchItem*> m_FreeBatchItemVec;

		std::vector<int16> m_IndexBuffer;
		std::vector<VertexPosColTex> m_VertexBuffer;
	};
}


