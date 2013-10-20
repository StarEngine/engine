#include "FontManager.h"
#include "../Logger.h"
#include "../Context.h"
#include "../Graphics/GraphicsManager.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/BaseScene.h"
#include "../Components/CameraComponent.h"
#include "../Objects/FreeCamera.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif

namespace star 
{
	std::shared_ptr<FontManager> FontManager::mFontManager = nullptr;


	std::shared_ptr<FontManager> FontManager::GetInstance()
	{
		if(mFontManager == nullptr)
		{
			mFontManager = std::shared_ptr<FontManager>(new FontManager());
		}
		return (mFontManager);
	}

	FontManager::FontManager():
		mLibrary(0)
	{
		auto error = FT_Init_FreeType(&mLibrary);
		if(error)
		{
			star::Logger::GetInstance()->Log(star::LogLevel::Error, _T("Font Manager : Could not initialize FreeType library"));
		}

#ifdef _WIN32
		Filepath texshaderVertex(_T("WinShaders/"), _T("Font_Shader.vert"));
		Filepath texshaderFrag(_T("WinShaders/"), _T("Font_Shader.frag"));
#else
		Filepath texshaderVertex(_T("AndroidShaders/"), _T("Font_Shader.vert"));
		Filepath texshaderFrag(_T("AndroidShaders/"), _T("Font_Shader.frag"));

#endif
		if(!m_Shader.Init(texshaderVertex.GetFullPath(),texshaderFrag.GetFullPath()))
		{
			Logger::GetInstance()->Log(star::LogLevel::Info, _T("Font Manager : Making Shader Failed"));
		}

		star::Logger::GetInstance()->Log(star::LogLevel::Info, _T("Font Manager : Initialized FreeType library"));
	}

	void FontManager::EraseFonts()
	{
		auto iter = mFontList.begin();
		for(iter; iter != mFontList.end(); ++iter)
		{
			iter->second.DeleteFont();
		}
		mFontList.clear();
		mPathList.clear();
		
		FT_Done_FreeType(mLibrary);
	}

	bool FontManager::LoadFont(const tstring& path, const tstring& name, int32 size)
	{
		if(mFontManager == nullptr)
		{
			return (false);
		}

		
		/*if(std::find(mPathList.begin(), mPathList.end(), path)!=mPathList.end())
		{
			return (false);
		}*/

		if(mFontList.find(name) != mFontList.end())
		{
			return (false);
		}

		star::Filepath filepath(_T("Fonts/"),path);

		Font tempfont;
		if(tempfont.Init(filepath.GetFullPath(),size,mLibrary))
		{
			mFontList[name] = tempfont;

		}
		else
		{
			return (false);
		}
		
		//mPathList.push_back(path);

		return (true);
	}

	bool FontManager::DeleteFont(const tstring& name)
	{
		auto it = mFontList.find(name);
		if(it != mFontList.end())
		{
			mFontList.erase(it);
			return (true);
		}
		return (false);
	}

	bool FontManager::DrawText( const tstring& text, const tstring& fontname, ivec2 position, vec4 color)
	{
		if(text==EMPTY_STRING)return false;
		
		auto it = mFontList.find(fontname);
		if(it == mFontList.end())return false;

		auto curfont = it->second;

		float h = curfont.GetSize()/0.63f;

		std::string conv_text = star::string_cast<std::string>(text);
		const char *start_line=conv_text.c_str();
		
		//[INFO] Needed for later text rendering (line breaks)
		/*std::vector<std::string> lines;
		for(const char *c=ctext; *c ; c++ ) 
		{
			if(*c=='\n') 
			{
				std::string line;
				for(const char *n=start_line;n<c;n++) line.append(1,*n);
				lines.push_back(line);
				start_line=c+1;
			}
			else if(start_line) 
			{
				std::string line;
				for(const char *n=start_line;n<c;n++) line.append(1,*n);
				lines.push_back(line);
			}
		
		}*/


		GLuint* textures = curfont.GetTextures();
		std::vector<fontUvCoords> tempuvs = curfont.getUvCoords();
		std::vector<fontVertices> tempverts = curfont.getVetrices();
		std::vector<ivec2> tempsizes = curfont.GetLetterDimensions();
		m_Shader.Bind();
		for(int i=0;start_line[i]!=0;i++) 
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,textures[ start_line[i] ]);
			GLint s_textureId = glGetUniformLocation(m_Shader.GetId(), "textureSampler");
			glUniform1i(s_textureId, 0);

			GLint s_colorId = glGetUniformLocation(m_Shader.GetId(), "colorMultiplier");
			glUniform4f(s_colorId,color.r,color.g,color.b,color.a);
			//Set attributes and buffers
			glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT,0,0,tempverts[start_line[i]].ver);
			glEnableVertexAttribArray(ATTRIB_VERTEX);
			glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, tempuvs[start_line[i]].uv);
			glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);

			uint32 width = GraphicsManager::GetInstance()->GetWindowWidth();
			uint32 height = GraphicsManager::GetInstance()->GetWindowHeight();
			auto projectionObject = star::SceneManager::GetInstance()->GetActiveScene()->GetActiveCamera();
			mat4x4 projection = projectionObject->GetComponent<CameraComponent>()->GetProjection();

			glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"Projection"),1,GL_FALSE,glm::value_ptr(projection));
			mat4x4 world;
			if(start_line[i] != 0)
			{
				int offset = curfont.GetMaxLetterHeight()-tempsizes[start_line[i] ].y;
				world = glm::translate(glm::vec3(position.x,position.y+curfont.GetMaxLetterHeight()-offset,0));
				position.x+=tempsizes[start_line[i] ].x;
			}
			else
			{
				world = glm::translate(glm::vec3(position.x,position.y,0));
			}
			mat4x4 worldInverse = InverseMatrix(world);
			glUniformMatrix4fv(glGetUniformLocation(m_Shader.GetId(),"Translation"),1,GL_FALSE,glm::value_ptr(worldInverse));

			glDrawArrays(GL_TRIANGLE_STRIP,0,4);

			//Unbind attributes and buffers
			glDisableVertexAttribArray(ATTRIB_VERTEX);
			glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);
		}
		m_Shader.Unbind();

		return true;   
	}

	mat4x4 FontManager::InverseMatrix(const mat4x4& matrix)
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
}
