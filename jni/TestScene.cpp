#include "TestScene.h"
#include "Helpers/Helpers.h"
#include "SceneManaging/CollisionManager.h"
#include "SceneManaging\PathFindManager.h"
#include "Input\InputManager.h"
#include "GraphicsManager.h"
#include "SceneManaging/SceneManager.h"
#include "Helpers/Filepath.h"

#ifdef _WIN32
#include "libs/OpenGL/GLEW/include/GL/glew.h"
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#define INPUT_MANAGER (InputManager::GetSingleton())
#define LOGGER (Logger::GetSingleton())

namespace star
{
	TestScene::TestScene(const tstring & Name):
		BaseScene(Name),
		m_TotalFrames(0),
		m_FPS(0),
		m_Step(0),
		m_PassedMiliseconds(0),
		m_pObjectOne(nullptr),
		m_pObjectTwo(nullptr),
		m_pObjectThree(nullptr),
		m_pObjectFour(nullptr),
		m_pObjectFive(nullptr),
		m_pObjectSix(nullptr),
		m_pRectCompOne(nullptr),
		m_pRectCompTwo(nullptr),
		m_pPathFindComp(nullptr),
		m_pPathFindCompTwo(nullptr),
		m_pPathFindCompThree(nullptr), 
		m_pPathFindCompFour(nullptr),
		m_pPathFindCompFive(nullptr),
		m_pPathFindCompSix(nullptr)
	{
		
	}

	status TestScene::Initialize( const Context& context)
	{
		m_pObjectOne = new Object();
		m_pRectCompOne = new RectangleColliderComponent(10,10);
		m_pPathFindComp = new PathFindNodeComponent();
		m_pObjectOne->AddComponent(m_pRectCompOne);
		m_pObjectOne->AddComponent(m_pPathFindComp);

		m_pObjectTwo = new Object();
		m_pRectCompTwo = new CircleColliderComponent(10);
		m_pPathFindCompTwo = new PathFindNodeComponent();
		m_pObjectTwo->AddComponent(m_pRectCompTwo);
		m_pObjectTwo->AddComponent(m_pPathFindCompTwo);
		m_pObjectTwo->GetComponent<TransformComponent>()->Translate(1,0,0);
		
		m_pObjectThree = new Object();
		m_pPathFindCompThree = new PathFindNodeComponent();
		m_pObjectThree->AddComponent(m_pPathFindCompThree);
		m_pObjectThree->GetComponent<TransformComponent>()->Translate(1,1,0);

		m_pObjectFour = new Object();
		m_pPathFindCompFour = new PathFindNodeComponent();
		m_pObjectFour->AddComponent(m_pPathFindCompFour);
		m_pObjectFour->GetComponent<TransformComponent>()->Translate(2,1,0);

		m_pObjectFive = new Object();
		m_pPathFindCompFive = new PathFindNodeComponent();
		m_pObjectFive->AddComponent(m_pPathFindCompFive);
		m_pObjectFive->GetComponent<TransformComponent>()->Translate(3,1,0);

		m_pObjectSix = new Object();
		m_pPathFindCompSix = new PathFindNodeComponent();
		m_pObjectSix->AddComponent(m_pPathFindCompSix);
		m_pObjectSix->GetComponent<TransformComponent>()->Translate(3,2,0);

		CollisionManager::GetInstance()->AddObject(m_pObjectOne);
		CollisionManager::GetInstance()->AddObject(m_pObjectTwo);

		CollisionManager::GetInstance()->CheckCollision(_T("Default"));

		if(TextureManager::GetInstance()->LoadTexture(_T("TestDaPng.png"),_T("TestPNG")))
		{
			LOGGER->Log(star::LogLevel::Info,_T("PNG : TestDaPng loaded succesfull"));
		}
		if(TextureManager::GetInstance()->LoadTexture(_T("Awesome.png"),_T("Awesome")))
		{
			LOGGER->Log(star::LogLevel::Info,_T("PNG : Awesome loaded succesfull"));
		}

		LOGGER->Log(star::LogLevel::Info,_T("Started making shader"));

#ifdef _WIN32
		Filepath texshaderVertex(_T("WinShaders/"),_T("Texture_Shader.vert"));
		Filepath texshaderFrag(_T("WinShaders/"),_T("Texture_Shader.frag"));
#else
		Filepath texshaderVertex(_T("AndroidShaders/"),_T("BaseTexShader.vert"));
		Filepath texshaderFrag(_T("AndroidShaders/"),_T("BaseTexShader.frag"));

#endif
		if(!mTextureShader.Init(texshaderVertex.GetFullPath(),texshaderFrag.GetFullPath()))
		{
			LOGGER->Log(star::LogLevel::Info,_T("Making Shader Failed"));
		}
		LOGGER->Log(star::LogLevel::Info,_T("Stopped making shader"));
		//=================================================================
		// [EXAMPLE] Here you see that I have a file path.
		//			 I used the easiest constructor,
		//			 but it has also other constructors.
		//			 For more information: check the header file.
		//			 This constructor has 2 parameters
		//			 	1) Directory of the file
		//					Notes:
		//					 + use EMPTY_STRING or _T("") if the file is
		//					   in the assets root dir.
		//					 + always start the path defintion starting
		//					   from the assets root dir.
		//Filepath example_path(_T("directory/"), _T("file.ext"));
		// this is the function you use to get the complete path
		// inclusive the file name and extension
		//	Notes:
		//		+ for windows he automaticly prepends the
		//		  predefined assets dir path to the returned full path.
		//		  by default this is './assets/'. (dir android uses)
		//	      this can be changed in the Win32Manifest.xml file.
		//LOGGER->Log(star::LogLevel::Info,example_path.GetFullPath());
		// File path has also functions, which you in most cases probably
		// don't really need.
		//=================================================================

		return STATUS_OK;
	}

	status TestScene::Update(const Context& context)
	{
		auto pos = INPUT_MANAGER->GetCurrentFingerPosCP();
		//tstringstream posBuffer;
		//posBuffer << _T("Current Mouse Pos: ( ") << pos.x << _T(" , ") << pos.y << _T(" )");
		//LOGGER->Log(LogLevel::Warning, posBuffer.str());

		++m_TotalFrames;
		m_PassedMiliseconds += float(context.mTimeManager->GetMicroSeconds());
		if(m_PassedMiliseconds >= 1000000)
		{
			m_FPS = m_TotalFrames;
			m_TotalFrames = 0;
			m_PassedMiliseconds -= 1000000;

			tstringstream str;
			str << "FPS: " << m_FPS;
			//LOGGER->Log(LogLevel::Info, str.str());

			m_pObjectOne->GetComponent<TransformComponent>()->Translate(PathFindManager::GetInstance()->GetStep(m_Step));
			vec3 pos = m_pObjectOne->GetComponent<TransformComponent>()->GetWorldPosition();
			//tstringstream tstr;
			//tstr << _T("PlayerPos : (") << pos.x << _T(", ") << pos.y << _T(")");
			//LOGGER->Log(LogLevel::Info, tstr.str());
			++m_Step;
		}
		PathFindManager::GetInstance()->FindPath(m_pObjectOne->GetComponent<TransformComponent>()->GetWorldPosition(), vec3(3,2,0));

		if(pos.y>(GraphicsManager::GetInstance()->GetScreenHeight()/2) && pos.y< star::GraphicsManager::GetInstance()->GetScreenHeight())
		{
			SceneManager::GetInstance()->SetActiveScene(_T("TestScene2"));
		}


		return STATUS_OK;
	}

	status TestScene::Draw()
	{
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Clear the background of our window to red

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)

		mTextureShader.Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(_T("Awesome")));
		GLint s_textureId = glGetUniformLocation(mTextureShader.id(), "textureSampler");
		glUniform1i(s_textureId, 0);

		static const GLfloat squareVertices[] = {
				-0.5f, -0.5f,
				-0.5f, 0.5f,
				0.5f,  -0.5f,
				0.5f,  0.5f,
		    };

		static const GLfloat textureVertices[] = {
		        1.0f, 1.0f,
		        1.0f, 0.0f,
		        0.0f,  1.0f,
		        0.0f,  0.0f,
		};

		glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT,0,0, squareVertices);
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, textureVertices);
		glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);
		glDrawArrays(GL_TRIANGLE_STRIP,0,4);
		glDisableVertexAttribArray(ATTRIB_VERTEX);
		glDisableVertexAttribArray(ATTRIB_TEXTUREPOSITON);
		mTextureShader.Unbind();

		return STATUS_OK;
	}



}
