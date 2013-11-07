#include "ScaleSystem.h"
#include "GraphicsManager.h"
#include "../Logger.h"

namespace star
{
	std::shared_ptr<ScaleSystem> ScaleSystem::m_ScaleSystemPtr = nullptr;

	ScaleSystem::ScaleSystem()
		:m_Scale(0)
		,m_AspectRatio(0)
		,m_bIninitialized(false)
	{
	}


	ScaleSystem::~ScaleSystem(void)
	{
	}

	std::shared_ptr<ScaleSystem> ScaleSystem::GetInstance()
	{
		if(m_ScaleSystemPtr == nullptr)
		{
			m_ScaleSystemPtr = std::shared_ptr<ScaleSystem>(new ScaleSystem());
		}			
		return m_ScaleSystemPtr;	
	}

	void ScaleSystem::SetWorkingResolution(int xPixels, int yPixels)
	{
		SetWorkingResolution(vec2(xPixels, yPixels));
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
		m_AspectRatio = pixels.x / pixels.y;
		CalculateScale();
	}

	float ScaleSystem::GetScale()
	{
		return m_Scale;
	}

	float ScaleSystem::GetAspectRatio()
	{
		return m_AspectRatio;
	}

	void ScaleSystem::CalculateScale()
	{
		if(m_bIninitialized)
		{
			ASSERT(m_WorkingRes != vec2(), 
				_T("Working resolution is 0! Please set correct working Resolution in the Game.cpp file!"));
			m_Scale = GraphicsManager::GetInstance()->GetViewportResolution().x / m_WorkingRes.x;
		}
	}
}

