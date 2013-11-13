#include "DebugDraw.h"
#include "../../Graphics/GraphicsManager.h"
#include "../../Logger.h"
#include "../AARect.h"
#include "../Rect.h"
#include "../Helpers.h"
#include "../../Graphics/ScaleSystem.h"

namespace star
{
	DebugDraw * DebugDraw::m_InstancePtr = nullptr;

	DebugDraw::DebugDraw()
		: m_PointSize(1.0f)
		, m_Shader(nullptr)
		, m_ColorLocation(0)
		, m_MVPLocation(0)
		, m_PositionLocation(0)
		, m_CircleSegments(16)
		, m_DrawOpTriangles(0.5f)
		, m_DrawOpLines(1.0f)
		, m_DrawOpPoints(1.0f)
	{
		
	}

	DebugDraw* DebugDraw::GetInstance()
	{
		if(m_InstancePtr == nullptr)
		{
			m_InstancePtr = new DebugDraw();
		}
		return m_InstancePtr;
	}

	DebugDraw::~DebugDraw()
	{
		delete m_Shader;
	}

	void DebugDraw::SetDrawOpacityTriangles(float opacity)
	{
		m_DrawOpTriangles = opacity;
	}

	void DebugDraw::SetDrawOpacityLines(float opacity)
	{
		m_DrawOpLines = opacity;
	}

	void DebugDraw::SetDrawOpacityPoints(float opacity)
	{
		m_DrawOpPoints = opacity;
	}

	void DebugDraw::SetCircleSegements(uint32 segments)
	{
		m_CircleSegments = segments;
	}

	void DebugDraw::Initialize()
	{
		static const GLchar* vertexShader = "\
			uniform mat4 MVP;\
			attribute vec2 position;\
			void main() {\
			  vec4 NewPosition = vec4(position, 0.0, 1.0);\
			  NewPosition *= MVP;\
			  gl_Position = NewPosition;\
			}\
			";

		static const GLchar* fragmentShader = "\
			precision mediump float; \
			uniform vec4 color;\
			void main() { \
			  gl_FragColor = color; \
			} \
			";

		// create program
		m_Shader = new Shader();
		m_Shader->Init(vertexShader, fragmentShader);

		m_ColorLocation = m_Shader->GetUniformLocation("color");
		m_MVPLocation = m_Shader->GetUniformLocation("MVP");
		m_PositionLocation = m_Shader->GetAttribLocation("position");
	}

	void DebugDraw::DrawPolygon(const vec2* vertices, int32 vertexCount, const Color& color)
	{
		CreatePolygonVertices(vertices, vertexCount);
		DrawPrimitives(Lines, vertexCount, color);
	}

	void DebugDraw::DrawSolidPolygon(const vec2* vertices, int32 vertexCount, const Color& color)
	{
		CreatePolygonVertices(vertices, vertexCount);
		DrawPrimitives(Triangles + Lines, vertexCount, color);
	}

	void DebugDraw::DrawCircle(const vec2& center, float radius, const Color& color)
	{
		CreateCircleVertices(center, radius);
		DrawPrimitives(Lines, m_CircleSegments, color);
	}

	void DebugDraw::DrawSolidCircle(const vec2& center, float radius, const vec2& axis,
			const Color& color)
	{
		CreateCircleVertices(center, radius);
		DrawPrimitives(Triangles + Lines, m_CircleSegments, color);
		// Draw the axis line
		DrawSegment(center, center + radius * axis, color);
	}

	void DebugDraw::DrawSegment(const vec2& pos1, const vec2& pos2, const Color& color)
	{
		m_Vertices[0].x = pos1.x * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[0].x = pos1.y * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1].y = pos2.x * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1].y = pos2.y * ScaleSystem::GetInstance()->GetScale();
		DrawPrimitives(Lines, 2, color);
	}

	void DebugDraw::DrawPoint(const vec2& pos, float size, const Color& color)
	{
		m_PointSize = size;

		m_Vertices[0].x = pos.x * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[0].y = pos.y * ScaleSystem::GetInstance()->GetScale();
		DrawPrimitives(Points, 1, color);
	}

	void DebugDraw::DrawScaledPoint(const vec2& pos, float size, const Color& color)
	{
		m_PointSize = size;

		m_Vertices[0].x = pos.x;
		m_Vertices[0].y = pos.y;
		DrawPrimitives(Points, 1, color);
	}

	void DebugDraw::DrawLine(const vec2& pos1, const vec2& pos2, const Color& color)
	{
		m_Vertices[0].x = pos1.x * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[0].y = pos1.y * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1].x = pos2.x * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1].y = pos2.y * ScaleSystem::GetInstance()->GetScale();
		DrawPrimitives(Lines,2,color);
	}

	void DebugDraw::DrawScaledLine(const vec2& pos1, const vec2& pos2, const Color& color)
	{
		m_Vertices[0].x = pos1.x;
		m_Vertices[0].y = pos1.y;
		m_Vertices[1].x = pos2.x;
		m_Vertices[1].y = pos2.y;
		DrawPrimitives(Lines,2,color);
	}

	void DebugDraw::DrawString(int aX, int aY, const tstring& text)
	{
		//[TODO] Implement this through the font manager, draw text on screen on given pos.
		Logger::GetInstance()->Log(LogLevel::Warning, _T("This is not yet implemented!"));
	}
	
	void DebugDraw::DrawRect(const AARect& rect, const Color& color)
	{
		m_Vertices[0].x = float(rect.GetLeft()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[0].y = float(rect.GetBottom()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1].x = float(rect.GetRight()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1].y = float(rect.GetBottom()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[2].x = float(rect.GetRight()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[2].y = float(rect.GetTop()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[3].x = float(rect.GetLeft()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[3].y = float(rect.GetTop()) * ScaleSystem::GetInstance()->GetScale();
		DrawPrimitives(Lines, 4, color);
	}

	void DebugDraw::DrawRect(const Rect& rect, const Color& color)
	{
		m_Vertices[0] = rect.GetLeftBottom() * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1] = rect.GetRightBottom() * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[2] = rect.GetRightTop() * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[3] = rect.GetLeftTop() * ScaleSystem::GetInstance()->GetScale();
		DrawPrimitives(Lines, 4, color);
	}

	void DebugDraw::DrawSolidRect(const AARect& rect, const Color& color)
	{
		m_Vertices[0].x = float(rect.GetLeft()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[0].y = float(rect.GetBottom()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1].x = float(rect.GetRight()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1].y = float(rect.GetBottom()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[2].x = float(rect.GetRight()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[2].y = float(rect.GetTop()) * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[3].x = float(rect.GetLeft()) * ScaleSystem::GetInstance()->GetScale(); 
		m_Vertices[3].y = float(rect.GetTop()) * ScaleSystem::GetInstance()->GetScale();
		DrawPrimitives(Triangles + Lines, 4, color);
	}

	void DebugDraw::DrawSolidRect(const Rect& rect, const Color& color)
	{
		m_Vertices[0] = rect.GetLeftBottom() * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[1] = rect.GetRightBottom() * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[2] = rect.GetRightTop() * ScaleSystem::GetInstance()->GetScale();
		m_Vertices[3] = rect.GetLeftTop() * ScaleSystem::GetInstance()->GetScale();
		DrawPrimitives(Triangles + Lines, 4, color);
	}
	
	void DebugDraw::DrawScaledRect(const AARect& rect, const Color& color)
	{
		m_Vertices[0].x = float(rect.GetLeft());
		m_Vertices[0].y = float(rect.GetBottom());
		m_Vertices[1].x = float(rect.GetRight());
		m_Vertices[1].y = float(rect.GetBottom());
		m_Vertices[2].x = float(rect.GetRight());
		m_Vertices[2].y = float(rect.GetTop());
		m_Vertices[3].x = float(rect.GetLeft());
		m_Vertices[3].y = float(rect.GetTop());
		DrawPrimitives(Lines, 4, color);
	}

	void DebugDraw::DrawScaledRect(const Rect& rect, const Color& color)
	{
		m_Vertices[0] = rect.GetLeftBottom();
		m_Vertices[1] = rect.GetRightBottom();
		m_Vertices[2] = rect.GetRightTop();
		m_Vertices[3] = rect.GetLeftTop();
		DrawPrimitives(Lines, 4, color);
	}

	void DebugDraw::DrawScaledSolidRect(const AARect& rect, const Color& color)
	{
		m_Vertices[0].x = float(rect.GetLeft());
		m_Vertices[0].y = float(rect.GetBottom());
		m_Vertices[1].x = float(rect.GetRight());
		m_Vertices[1].y = float(rect.GetBottom());
		m_Vertices[2].x = float(rect.GetRight());
		m_Vertices[2].y = float(rect.GetTop());
		m_Vertices[3].x = float(rect.GetLeft()); 
		m_Vertices[3].y = float(rect.GetTop());
		DrawPrimitives(Triangles + Lines, 4, color);
	}

	void DebugDraw::DrawScaledSolidRect(const Rect& rect, const Color& color)
	{
		m_Vertices[0] = rect.GetLeftBottom();
		m_Vertices[1] = rect.GetRightBottom();
		m_Vertices[2] = rect.GetRightTop();
		m_Vertices[3] = rect.GetLeftTop();
		DrawPrimitives(Triangles + Lines, 4, color);
	}

	void DebugDraw::CreatePolygonVertices(const vec2* vertices, uint32 vertexCount)
	{
		ASSERT(vertexCount <= MAX_VERTICES, _T("more vertices than allocated space"));

		for (uint32 i = 0; i < vertexCount; i++)
		{
			m_Vertices[i].x = vertices[i].x * ScaleSystem::GetInstance()->GetScale();
			m_Vertices[i].y = vertices[i].y * ScaleSystem::GetInstance()->GetScale();
		}
	}

	void DebugDraw::CreateCircleVertices(const vec2& center, float radius)
	{
		ASSERT(m_CircleSegments < MAX_VERTICES, tstring(_T("You can only draw ") 
			+ string_cast<tstring>(MAX_VERTICES) + _T(" vertices per primitive")).c_str());
		const float increment = float(2.0 * PI / m_CircleSegments);
		float theta = 0.0f;

		for (uint32 i = 0; i < m_CircleSegments; ++i)
		{
			vec2 v = center + radius * vec2(glm::cos(theta), glm::sin(theta));
			m_Vertices[i].x = v.x * ScaleSystem::GetInstance()->GetScale();
			m_Vertices[i].y = v.y * ScaleSystem::GetInstance()->GetScale();
			theta += increment;
		}
	}

	void DebugDraw::DrawPrimitives(uint32 primitiveTypes, uint32 count, const Color& color)
	{
#ifdef DESKTOP
		glUseProgram(m_Shader->GetID());

		glUniformMatrix4fv(m_MVPLocation,
				1, GL_FALSE, glm::value_ptr(GraphicsManager::GetInstance()->GetViewProjectionMatrix()));

		glEnableVertexAttribArray(m_PositionLocation);
		glVertexAttribPointer(m_PositionLocation, 2, GL_FLOAT, GL_FALSE, 0, (GLfloat*) m_Vertices);

		if (primitiveTypes & Triangles)
		{
			glUniform4f(m_ColorLocation, color.r, color.g, color.b, m_DrawOpTriangles);
			glDrawArrays(GL_TRIANGLE_FAN, 0, count);
		}

		if (primitiveTypes & Lines)
		{
			glUniform4f(m_ColorLocation, color.r, color.g, color.b, m_DrawOpLines);
			glDrawArrays(GL_LINE_LOOP, 0, count);
		}

		if (primitiveTypes & Points)
		{
			glUniform4f(m_ColorLocation, color.r, color.g, color.b, m_DrawOpPoints);
			//[TODO] only works for windows..
#ifdef DESKTOP
			glPointSize(m_PointSize);
#endif
			glDrawArrays(GL_POINTS, 0, count);
		}

		glDisableVertexAttribArray(m_PositionLocation);
		glUseProgram(0);
#endif
	}

}
