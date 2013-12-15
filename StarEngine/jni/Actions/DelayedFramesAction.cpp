#include "DelayedFramesAction.h"

namespace star
{
	DelayedFramesAction::DelayedFramesAction(uint32 nrOfFrames)
		: Action()
		, m_NumberOfFrames(nrOfFrames)
		, m_CurrentNrOfFrames(0)
		, m_Callback(nullptr)
	{
	}

	DelayedFramesAction::DelayedFramesAction(const tstring& name, uint32 nrOfFrames)
		: Action(name)
		, m_NumberOfFrames(nrOfFrames)
		, m_CurrentNrOfFrames(0)
		, m_Callback(nullptr)
	{
	}

	DelayedFramesAction::~DelayedFramesAction()
	{

	}

	void DelayedFramesAction::Initialize()
	{

	}

	void DelayedFramesAction::Update(const Context & context)
	{
		if(m_CurrentNrOfFrames == m_NumberOfFrames)
		{
			if(m_Callback)
			{
				m_Callback();
			}
			Destroy();
		}
		++m_CurrentNrOfFrames;
	}

	void DelayedFramesAction::SetCallback(const std::function<void()> & callback)
	{
		m_Callback = callback;
	}
}
