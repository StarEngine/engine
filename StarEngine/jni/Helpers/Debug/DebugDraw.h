#pragma once

#include "../../defines.h"
#include "../../Graphics/Color.h"
#include "../../Graphics/Shader.h"
#ifdef DESKTOP
#include <gl\GL.h>
#else
#include <GLES2/gl2.h>
#endif

namespace star  
{  
	class AARect;
	class Rect;

	class DebugDraw final
	{  
	public:  
		 
		static DebugDraw* GetInstance();
		~DebugDraw();  

		void Initialize();

		void DrawPolygon(const vec2* vertices, int32 vertexCount, const Color& color);  
		void DrawSolidPolygon(const vec2* vertices, int32 vertexCount, const Color& color);  
		void DrawCircle(const vec2& center, float32 radius, const Color& color);  
		void DrawSolidCircle(const vec2& center, float32 radius, const Color& color); 
		void DrawSegment(const vec2& pos1, const vec2& pos2, const Color& aColor);  
		//[TODO] DrawTransform: Draw the transformed Axises of the object/matrix
		// void DrawTransform(const mat4& aXf);  
		void DrawPoint(const vec2& pos, float32 size, const Color& color);  
		void DrawLine(const vec2& pos1, const vec2& pos2, const Color& color);
		void DrawString(int32 xPos, int32 yPos, const tstring& text);  
		void DrawRect(const AARect& rect, const Color& color);  
		void DrawRect(const Rect& rect, const Color& color); 
		void DrawSolidRect(const AARect& rect, const Color& color);  
		void DrawSolidRect(const Rect& rect, const Color& color); 

		void SetDrawOpacityTriangles(float32 opacity);
		void SetDrawOpacityLines(float32 opacity);
		void SetDrawOpacityPoints(float32 opacity);
		void SetCircleSegements(uint32 segments);
  
	private:  
		static const uint32 MAX_VERTICES = 64;

		enum
		{
			Triangles = 0x01,
			Lines     = 0x02,
			Points    = 0x04
		}; 

		DebugDraw();  
		static DebugDraw* m_InstancePtr;
		
		void CreatePolygonVertices(const vec2* vertices, uint32 vertexCount);  
		void CreateCircleVertices(const vec2& center, float32 radius);  
		void DrawPrimitives(uint32 primitiveTypes, uint32 count, const Color& color);  

		vec2 m_Vertices[MAX_VERTICES];  
		float32 m_PointSize;  

		uint32 m_CircleSegments;
		float32 m_DrawOpTriangles;
		float32 m_DrawOpLines;
		float32 m_DrawOpPoints;

		Shader* m_Shader;
		GLuint m_ColorLocation;  
		GLuint m_MVPLocation;
		GLuint m_PositionLocation;  	

		DebugDraw(const DebugDraw &);
		DebugDraw(DebugDraw &&);
		DebugDraw & operator=(const DebugDraw &);
		DebugDraw & operator=(DebugDraw&&);
	};  
  
} 

