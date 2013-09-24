#pragma once

#include "defines.h"
#include "libs/OpenGL/GLEW/include/GL/glew.h"
#include "libs/OpenGL/GLUT/include/GL/glut.h"

namespace star
{
	class GraphicsManager
	{
	public:
		~GraphicsManager(){}

		static GraphicsManager* GetInstance();

		void Initialize();
		void StartDraw();
		void StopDraw();

	private:

		static GraphicsManager* mGraphicsManager;

		GraphicsManager();

		int32 mScreenWidth;
		int32 mScreenHeight;

		//disabling default copy constructor
		GraphicsManager(const GraphicsManager& yRef);
		GraphicsManager& operator=(const GraphicsManager& yRef);
	};


}