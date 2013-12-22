#include "ScaleSystem.h"
#include "GraphicsManager.h"
#include "../Logger.h"

namespace star
{
	ScaleSystem * ScaleSystem::m_ScaleSystemPtr = nullptr;

	ScaleSystem::ScaleSystem()
		:m_WorkingRes(0,0)
		,m_Scale(0)
		,m_bIninitialized(false)
	{
	}


	ScaleSystem::~ScaleSystem(void)
	{
	}

	ScaleSystem * ScaleSystem::GetInstance()
	{
		if(m_ScaleSystemPtr == nullptr)
		{
			m_ScaleSystemPtr = new ScaleSystem();
		}			
		return m_ScaleSystemPtr;	
	}

	void ScaleSystem::SetWorkingResolution(int32 xPixels, int32 yPixels)
	{
		vec2 workingRes(xPixels, yPixels);
		SetWorkingResolution(workingRes);
	}
	
	const vec2& ScaleSystem::GetWorkingResolution() const
	{
		return m_WorkingRes;
	}

	const vec2 & ScaleSystem::GetActualResolution() const
	{
		return GraphicsManager::GetInstance()->GetWindowResolution();
	}

	void ScaleSystem::SetWorkingResolution(const vec2& pixels)
	{
		m_bIninitialized = true;
		m_WorkingRes = pixels;
		CalculateScale();
	}

	float32 ScaleSystem::GetScale() const
	{
		return m_Scale;
	}

	void ScaleSystem::CalculateScale()
	{
		if(m_bIninitialized)
		{
			Logger::GetInstance()->Log(m_WorkingRes != vec2(), 
				_T("ScaleSystem::CalculateScale(): \
Working resolution is 0! Please set correct working Resolution in the Game.cpp file!"));
			m_Scale = GraphicsManager::GetInstance()->GetViewportResolution().x / m_WorkingRes.x;
		}
	}
}

