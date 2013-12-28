#include "DebugDraw.h"
#include "../../Graphics/GraphicsManager.h"
#include "../../Graphics/ScaleSystem.h"
#include "../../Logger.h"
#include "../AARect.h"
#include "../Rect.h"
#include "../Helpers.h"
#include "../Math.h"

namespace star
{
	DebugDraw * DebugDraw::m_InstancePtr = nullptr;

	DebugDraw::DebugDraw()
		: m_PointSize(1.0f)
		, m_Shader(nullptr)
		, m_ColorLocation(0)
		, m_MVPLocation(0)
		, m_PositionLocation(0)
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

	void DebugDraw::SetDrawOpacityTriangles(float32 opacity)
	{
		m_DrawOpTriangles = opacity;
	}

	void DebugDraw::SetDrawOpacityLines(float32 opacity)
	{
		m_DrawOpLines = opacity;
	}

	void DebugDraw::SetDrawOpacityPoints(float32 opacity)
	{
		m_DrawOpPoints = opacity;
	}

	void DebugDraw::Initialize()
	{
		static const GLchar* vertexShader = "\
			uniform mat4 MVP;\
			attribute vec2 position;\
			void main()\
			{\
			  vec4 NewPosition = vec4(position, 0.0, 1.0);\
			  NewPosition *= MVP;\
			  gl_Position = NewPosition;\
			}\
			";

		static const GLchar* fragmentShader = "\
			precision mediump float;\
			uniform vec4 color;\
			void main()\
			{\
			  gl_FragColor = color;\
			}\
			";

		// create program
		m_Shader = new Shader(vertexShader, fragmentShader);

		m_ColorLocation = m_Shader->GetUniformLocation("color");
		m_MVPLocation = m_Shader->GetUniformLocation("MVP");
		m_PositionLocation = m_Shader->GetAttribLocation("position");
	}

	void DebugDraw::DrawPolygon(
		const vec2* vertices, 
		int32 vertexCount,
		const Color& color)
	{
		CreatePolygonVertices(vertices, vertexCount);
		AddToVertexQueue(Lines, vertexCount, color);
	}

	void DebugDraw::DrawSolidPolygon(
		const vec2* vertices, 
		int32 vertexCount, 
		const Color& color)
	{
		CreatePolygonVertices(vertices, vertexCount);
		AddToVertexQueue(Triangles + Lines, vertexCount, color);
	}

	void DebugDraw::DrawCircle(
		const vec2& center, 
		float32 radius, 
		const Color& color, 
		uint32 segments)
	{
		CreateCircleVertices(center, radius, segments);
		AddToVertexQueue(Lines, segments, color);
	}

	void DebugDraw::DrawSolidCircle(
		const vec2& center, 
		float32 radius,
		const Color& color, 
		uint32 segments)
	{
		CreateCircleVertices(center, radius, segments);
		AddToVertexQueue(Triangles + Lines, segments, color);
	}

	void DebugDraw::DrawSegment(
		const vec2& pos1, 
		const vec2& pos2, 
		const Color& color)
	{
		m_Vertices[0] = pos1;
		m_Vertices[1] = pos2;
		AddToVertexQueue(Lines, 2, color);
	}

	void DebugDraw::DrawPoint(
		const vec2& pos, 
		float32 size, 
		const Color& color)
	{
		m_PointSize = size;

		m_Vertices[0] = pos;
		AddToVertexQueue(Points, 1, color);
	}

	void DebugDraw::DrawLine(
		const vec2& pos1, 
		const vec2& pos2, 
		const Color& color)
	{
		m_Vertices[0] = pos1;
		m_Vertices[1] = pos2;
		AddToVertexQueue(Lines,2,color);
	}

	void DebugDraw::DrawString(
		int32 aX,
		int32 aY, 
		const tstring& text)
	{
		//[TODO] Implement this through the font manager, 
		//draw text on screen on given pos.
		LOG(LogLevel::Warning, 
			_T("DebugDraw::DrawString is not yet implemented!"),
			STARENGINE_LOG_TAG);
	}

	void DebugDraw::DrawRect(
		const AARect& rect, 
		const Color& color)
	{
		m_Vertices[0].x = float32(rect.GetLeft());
		m_Vertices[0].y = float32(rect.GetBottom());
		m_Vertices[1].x = float32(rect.GetRight());
		m_Vertices[1].y = float32(rect.GetBottom());
		m_Vertices[2].x = float32(rect.GetRight());
		m_Vertices[2].y = float32(rect.GetTop());
		m_Vertices[3].x = float32(rect.GetLeft());
		m_Vertices[3].y = float32(rect.GetTop());
		AddToVertexQueue(Lines, 4, color);
	}

	void DebugDraw::DrawRect(
		const Rect& rect, 
		const Color& color)
	{
		m_Vertices[0] = rect.GetLeftBottom();
		m_Vertices[1] = rect.GetRightBottom();
		m_Vertices[2] = rect.GetRightTop();
		m_Vertices[3] = rect.GetLeftTop();
		AddToVertexQueue(Lines, 4, color);
	}

	void DebugDraw::DrawSolidRect(
		const AARect& rect, 
		const Color& color)
	{
		m_Vertices[0].x = float32(rect.GetLeft());
		m_Vertices[0].y = float32(rect.GetBottom());
		m_Vertices[1].x = float32(rect.GetRight());
		m_Vertices[1].y = float32(rect.GetBottom());
		m_Vertices[2].x = float32(rect.GetRight());
		m_Vertices[2].y = float32(rect.GetTop());
		m_Vertices[3].x = float32(rect.GetLeft()); 
		m_Vertices[3].y = float32(rect.GetTop());
		AddToVertexQueue(Triangles + Lines, 4, color);
	}

	void DebugDraw::DrawSolidRect(
		const Rect& rect, 
		const Color& color)
	{
		m_Vertices[0] = rect.GetLeftBottom();
		m_Vertices[1] = rect.GetRightBottom();
		m_Vertices[2] = rect.GetRightTop();
		m_Vertices[3] = rect.GetLeftTop();
		AddToVertexQueue(Triangles + Lines, 4, color);
	}

	void DebugDraw::CreatePolygonVertices(
		const vec2* vertices, 
		uint32 vertexCount)
	{
		ASSERT_LOG(vertexCount <= MAX_VERTICES, 
			_T("more vertices than allocated space"),
			STARENGINE_LOG_TAG);

		for (uint32 i = 0; i < vertexCount; ++i)
		{
			m_Vertices[i] = vertices[i];
		}
	}

	void DebugDraw::CreateCircleVertices
		(const vec2& center, 
		float32 radius,
		uint8 segments)
	{
		// [TODO] Fix this bug in eclipse: 
		// (undefined reference to 'star::DebugDraw::MAX_VERTICES')
		//ASSERT_LOG(m_CircleSegments < MAX_VERTICES, 
		//	tstring(_T("You can only draw ") 
		//	+ string_cast<tstring>(MAX_VERTICES) 
		//	+ _T(" vertices per primitive")).c_str(), STARENGINE_LOG_TAG);
		const float32 increment = float32(2.0 * PI / segments);
		float32 theta = 0.0f;

		for (uint32 i = 0; i < segments; ++i)
		{
			vec2 vec = center + radius * vec2(cos(theta), sin(theta));

			m_Vertices[i] = vec;
			theta += increment;
		}
	}

	void DebugDraw::AddToVertexQueue(
		uint32 primitiveTypes,
		uint32 count,
		const Color& color
		)
	{
		PrimitiveInfo tempInfo = PrimitiveInfo();
		for(uint32 i = 0; i < MAX_VERTICES; ++i)
		{
			tempInfo.vertices[i] = m_Vertices[i];
		}
		tempInfo.primitiveType = primitiveTypes;
		tempInfo.count = count;
		tempInfo.color = color;
		tempInfo.opacityLines = m_DrawOpLines;
		tempInfo.opacityTriangles = m_DrawOpTriangles;
		tempInfo.opacityPoints = m_DrawOpPoints;

		m_VertexBuffer.push_back(tempInfo);
	}

	void DebugDraw::Begin()
	{
		m_Shader->Bind();
		
		float32 scaleValue(ScaleSystem::GetInstance()->GetScale());
		mat4 scaleMat(Scale(scaleValue, scaleValue, 1.0f));

		glUniformMatrix4fv(
			m_MVPLocation,
			1, GL_FALSE,
			ToPointerValue(
				scaleMat *
				GraphicsManager::GetInstance()->GetViewInverseProjectionMatrix()
				)
			);
	}

	void DebugDraw::Flush()
	{
#ifdef DESKTOP
		Begin();

		for(const auto & elem : m_VertexBuffer)
		{
			glEnableVertexAttribArray(m_PositionLocation);
			glVertexAttribPointer(m_PositionLocation, 2, GL_FLOAT, 
				GL_FALSE, 0, elem.vertices);

			if ((elem.primitiveType & Triangles) != 0)
			{
				glUniform4f(m_ColorLocation, elem.color.r, elem.color.g, elem.color.b, m_DrawOpTriangles);
				glDrawArrays(GL_TRIANGLE_FAN, 0, elem.count);
			}

			if ((elem.primitiveType & Lines) != 0)
			{
				glUniform4f(m_ColorLocation, elem.color.r, elem.color.g, elem.color.b, m_DrawOpLines);
				glDrawArrays(GL_LINE_LOOP, 0, elem.count);
			}

			if ((elem.primitiveType & Points) != 0)
			{
				glUniform4f(m_ColorLocation, elem.color.r, elem.color.g, elem.color.b, m_DrawOpPoints);
				//[TODO] only works for windows..
				glPointSize(m_PointSize);
				glDrawArrays(GL_POINTS, 0, elem.count);
			}
			glDisableVertexAttribArray(m_PositionLocation);
		}

		End();
#endif
	}

	void DebugDraw::End()
	{
		m_Shader->Unbind();
		m_VertexBuffer.clear();
	}

}
