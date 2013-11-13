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

	class DebugDraw
	{  
	public:  
		 
		static DebugDraw* GetInstance();
		~DebugDraw();  

		void Initialize();

		void DrawPolygon(const vec2* vertices, int32 vertexCount, const Color& color);  
		void DrawSolidPolygon(const vec2* vertices, int32 vertexCount, const Color& color);  
		void DrawCircle(const vec2& center, float radius, const Color& color);  
		void DrawSolidCircle(const vec2& center, float radius, const vec2& axis, const Color& color);  
		void DrawSegment(const vec2& pos1, const vec2& pos2, const Color& aColor);  
		//[TODO] DrawTransform: Draw the transformed Axises of the object/matrix
		// void DrawTransform(const mat4x4& aXf);  
		void DrawPoint(const vec2& pos, float size, const Color& color);  
		void DrawLine(const vec2& pos1, const vec2& pos2, const Color& color);
		void DrawString(int xPos, int yPos, const tstring& text);  
		void DrawRect(const AARect& rect, const Color& color);  
		void DrawRect(const Rect& rect, const Color& color); 
		void DrawSolidRect(const AARect& rect, const Color& color);  
		void DrawSolidRect(const Rect& rect, const Color& color); 

		void SetDrawOpacityTriangles(float opacity);
		void SetDrawOpacityLines(float opacity);
		void SetDrawOpacityPoints(float opacity);
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
		void CreateCircleVertices(const vec2& center, float radius);  
		void DrawPrimitives(uint32 primitiveTypes, uint32 count, const Color& color);  

		vec2 m_Vertices[MAX_VERTICES];  
		float m_PointSize;  

		uint32 m_CircleSegments;
		float m_DrawOpTriangles;
		float m_DrawOpLines;
		float m_DrawOpPoints;

		Shader* m_Shader;
		GLuint m_ColorLocation;  
		GLuint m_MVPLocation;
		GLuint m_PositionLocation;  		
	};  
  
} 

