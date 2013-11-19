#pragma once

#include <memory>
#include "../defines.h"

namespace star
{
	class ScaleSystem final
	{
	public:
		~ScaleSystem();

		static ScaleSystem * GetInstance();
		void SetWorkingResolution(int32 xPixels, int32 yPixels);
		void SetWorkingResolution(const vec2& pixels);
		const vec2& GetWorkingResolution() const;
		const vec2& GetActualResolution() const;
		float32 GetScale() const;
		void CalculateScale();

	private:
		ScaleSystem();

		vec2 m_WorkingRes;
		float32 m_Scale;
		bool m_bIninitialized;

		static ScaleSystem * m_ScaleSystemPtr;
	};
}
