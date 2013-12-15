#pragma once
#include "Action.h"
#include <functional>

namespace star
{
	class DelayedFramesAction : public Action
	{
	public:
		DelayedFramesAction(uint32 nrOfFrames = 1);
		DelayedFramesAction(const tstring& name, uint32 nrOfFrames = 1);
		virtual ~DelayedFramesAction();

		void SetCallback(const std::function<void()> & callback);

	protected:
		virtual void Initialize();
		virtual void Update(const Context & context);

		std::function<void()> m_Callback;

	private:
		uint32 m_NumberOfFrames;
		uint32 m_CurrentNrOfFrames;
	};
}


