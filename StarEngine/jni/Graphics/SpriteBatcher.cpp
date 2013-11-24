#include "SpriteBatcher.h"
#include "SpriteSortMode.h"

namespace star
{
	SpriteBatcher::SpriteBatcher()
		: m_BatchItemVec()
		, m_FreeBatchItemVec()
		, m_IndexBuffer()
		, m_VertexBuffer()
	{
		CheckBuffers(BASE_BATCH_SIZE);
	}


	SpriteBatcher::~SpriteBatcher()
	{
		for(auto item : m_BatchItemVec)
		{
			delete item;
		}
		m_BatchItemVec.clear();

		for(auto item : m_FreeBatchItemVec)
		{
			delete item;
		}
		m_FreeBatchItemVec.clear();
		m_IndexBuffer.clear();
		m_VertexBuffer.clear();
	}

	void SpriteBatcher::CheckBuffers(uint32 nrOfBatchItems)
	{
		uint32 neededCapacity = 6 * nrOfBatchItems;
		if(neededCapacity <= m_IndexBuffer.size())
		{
			return;
		}
		uint32 start = m_IndexBuffer.size();
		for(uint32 i = start; i < nrOfBatchItems; ++i)
		{
			/*
			*  TL    TR
			*   0----1 
			*   |   /| 
			*   |  / |
			*   | /  |
			*   |/   |
			*   2----3
			*  BL    BR
			*/

			//Triangle 1
			m_IndexBuffer.push_back(i * 4);
			m_IndexBuffer.push_back(i * 4 + 1);
			m_IndexBuffer.push_back(i * 4 + 2);

			//Triangle 2
			m_IndexBuffer.push_back(i * 4 + 1);
			m_IndexBuffer.push_back(i * 4 + 3);
			m_IndexBuffer.push_back(i * 4 + 2);
		}

		m_VertexBuffer.resize(4 * nrOfBatchItems);
	}

	SpriteBatchItem* SpriteBatcher::CreateBatchItem()
	{
		SpriteBatchItem* item;
		if(!m_FreeBatchItemVec.empty())
		{
			item = m_FreeBatchItemVec.back();
			//Remove the pointer from the FreeBatchVec
			m_FreeBatchItemVec.pop_back();
		}
		else
		{
			item = new SpriteBatchItem();
		}
		m_BatchItemVec.push_back(item);
		return item;
	}

	void SpriteBatcher::DrawBatch(SpriteSortMode spriteSortMode)
	{
		if(m_BatchItemVec.empty())
		{
			return;
		}

		//[TODO] Implement the sort modes!
		switch(spriteSortMode)
		{
		case SpriteSortMode::Texture:
			break;
		case SpriteSortMode::BackToFront:
			break;
		case SpriteSortMode::FrontToBack:
			break;
		}

		//[TODO] complete this methode.
	}
}

