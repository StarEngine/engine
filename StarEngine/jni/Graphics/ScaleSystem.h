#pragma once

#include <memory>
#include "../defines.h"
#include "../Helpers/Singleton.h"

namespace star
{
	/// <summary>
	/// Provides a resolution independant system.
	/// Set your target resolution to the value you specify
	/// and code everything as if your window would be that resolution.
	/// </summary>
	class ScaleSystem final : public Singleton<ScaleSystem>
	{
	public:
		friend Singleton<ScaleSystem>;

		/// <summary>
		/// Sets the working resolution of the game.
		/// </summary>
		/// <param name="xPixels">The amount of pixels horizontally.</param>
		/// <param name="yPixels">The amount of pixels vertically.</param>
		void SetWorkingResolution(int32 xPixels, int32 yPixels);
		/// <summary>
		/// Sets the working resolution of the game.
		/// </summary>
		/// <param name="pixels">The amount of pixels.</param>
		void SetWorkingResolution(const vec2& pixels);
		/// <summary>
		/// Gets the working resolution of the game.
		/// </summary>
		/// <returns>The working resolution</returns>
		const vec2& GetWorkingResolution() const;
		/// <summary>
		/// Gets the actual resolution of the game.
		/// </summary>
		/// <returns>The actual resolution</returns>
		const vec2& GetActualResolution() const;
		/// <summary>
		/// Gets the scale of the window, expressed as the window resolution / the target resolution.
		/// </summary>
		/// <returns>The scale of the window.</returns>
		float32 GetScale() const;
		/// <summary>
		/// Calculates the scale of the window, expressed as the window resolution / the target resolution.
		/// </summary>
		void CalculateScale();

	private:
		/// <summary>
		/// Creates a new instance of the <see cref="ScaleSystem"/>
		/// Private because of Singleton design pattern.
		/// </summary>
		ScaleSystem();
		
		/// <summary>
		/// Finalizes an instance of the <see cref="ScaleSystem"/> class.
		/// </summary>
		~ScaleSystem();

		vec2 m_WorkingRes;
		float32 m_Scale;
		bool m_bIninitialized;
	};
}
