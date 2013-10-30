#include "SpriteComponent.h"
#include "../../Logger.h"
#include "../../Assets/TextureManager.h"
#include "../../Graphics/GraphicsManager.h"
#include "../TransformComponent.h"
#include "../../Objects/FreeCamera.h"
#include "../CameraComponent.h"
#include "../../Objects/Object.h"
#include "../../Graphics/SpriteBatch.h"

namespace star
{
	SpriteComponent::SpriteComponent(const tstring& filepath,const tstring& spriteName, bool bIsHUDElement)
		: BaseComponent()
		, m_Width(0)
		, m_Heigth(0)
		, m_Shader()
		, m_FilePath(filepath)
		, m_SpriteName(spriteName)
		, m_bIsHudElement(bIsHUDElement)
	{
	}

	void SpriteComponent::InitializeComponent()
	{
		#ifdef DESKTOP
				Filepath texshaderVertex(_T("WinShaders/"), _T("Texture_Shader.vert"));
				Filepath texshaderFrag(_T("WinShaders/"), _T("Texture_Shader.frag"));
		#else
				Filepath texshaderVertex(_T("AndroidShaders/"), _T("BaseTexShader.vert"));
				Filepath texshaderFrag(_T("AndroidShaders/"), _T("BaseTexShader.frag"));
		#endif

				if(!m_Shader.Init(texshaderVertex.GetFullPath(),texshaderFrag.GetFullPath()))
				{
					Logger::GetInstance()->Log(star::LogLevel::Info, _T("Making Shader Failed"));
				}
		
		TextureManager::GetInstance()->LoadTexture(m_FilePath.GetFullPath(),m_SpriteName);
		m_Width = TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).x;
		m_Heigth =  TextureManager::GetInstance()->GetTextureDimensions(m_SpriteName).y;

		CreateVertices();
		CreateIndices();
	}

	SpriteComponent::~SpriteComponent()
	{
		// [COMMENT] can you explain me why you wouldn't want
		// to destroy the texture once this spritecomponent
		// is deleted. (you can do that via skype)
		// [COMMENT] @ Simon: We should discuss if RemoveTexture should be called here. 
		// Really depends of the structure of the TextureManager

		//TextureManager::GetInstance()->DeleteTexture(m_SpriteName);
	}

	void SpriteComponent::CreateVertices()
	{
		m_Vertices[0] = (GLfloat)m_Width;
        m_Vertices[1] = (GLfloat)m_Heigth;
        m_Vertices[2] = 0;
        m_Vertices[3] = (GLfloat)m_Width;
        m_Vertices[4] = 0;
        m_Vertices[5] = 0;
        m_Vertices[6] = 0;
        m_Vertices[7] = (GLfloat)m_Heigth;
        m_Vertices[8] = 0;
        m_Vertices[9] = 0;
        m_Vertices[10] = 0;
        m_Vertices[11] = 0;
	}

	void SpriteComponent::CreateIndices()
	{
		m_UvCoords[0] = 1.0f;
		m_UvCoords[1] = 1.0f;
		m_UvCoords[2] = 1.0f;
		m_UvCoords[3] = 0.0f;
		m_UvCoords[4] = 0.0f;
		m_UvCoords[5] = 1.0f;
		m_UvCoords[6] = 0.0f;
		m_UvCoords[7] = 0.0f;
	}

	void SpriteComponent::Draw()
	{
		SpriteBatch::GetInstance()->AddSpriteToQueue(this, m_bIsHudElement);
	}

	mat4x4 SpriteComponent::InverseMatrix(const mat4x4& matrix)
	{
		float x1, y1, z1, w1,
			  x2, y2, z2, w2,
			  x3, y3, z3, w3,
			  x4, y4, z4, w4;

		x1 = matrix[0][0];
		x2 = matrix[1][0];
		x3 = matrix[2][0];
		x4 = matrix[3][0];

		y1 = matrix[0][1];
		y2 = matrix[1][1];
		y3 = matrix[2][1];
		y4 = matrix[3][1];

		z1 = matrix[0][2];
		z2 = matrix[1][2];
		z3 = matrix[2][2];
		z4 = matrix[3][2];

		w1 = matrix[0][3];
		w2 = matrix[1][3];
		w3 = matrix[2][3];
		w4 = matrix[3][3];

		mat4x4 inverseMatrix
		(
		x1, y1, z1, x4,
		x2, y2, z2, y4,
		x3, y3, z3, z4,
		w1, w2, w3, w4
		);
		
		return inverseMatrix;
	}

	const tstring& SpriteComponent::GetFilePath() const
	{
		return m_FilePath.GetPath();
	}

	const tstring& SpriteComponent::GetName() const
	{
		return m_SpriteName;
	}

	int32 SpriteComponent::GetWidth() const
	{
		return m_Width;
	}

	int32 SpriteComponent::GetHeight() const
	{
		return m_Heigth;
	}

	std::vector<GLfloat> SpriteComponent::GetVertices() const
	{
		std::vector<GLfloat> vertices;
		vertices.clear();
		
		for(int i = 0; i < 12; ++i)
		{
			vertices.push_back(m_Vertices[i]);
		}
		return vertices;
	}

	std::vector<GLfloat> SpriteComponent::GetUVCoords() const
	{
		std::vector<GLfloat> uvCoords;
		uvCoords.clear();
		
		for(int i = 0; i < 8; ++i)
		{
			uvCoords.push_back(m_UvCoords[i]);
		}
		return uvCoords;
	}
}
