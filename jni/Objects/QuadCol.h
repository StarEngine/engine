#pragma once

#include "../defines.h"

#ifdef _WIN32
#else

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include "../Shaders/Shader.h"
#endif
namespace star
{
	class QuadCol
	{
	public:
		QuadCol();
		~QuadCol();

		void Rotate(glm::mat4& matrix, float angle, vec3& axis);
		void Scale(glm::mat4& matrix, vec3& scale);
		void Translate (glm::mat4& matrix, vec3& translation);

		void Draw();

	private:
		void createSquare();

		Shader* mShader;

		glm::mat4 modelMatrix;
		glm::mat4 rotMatrix;
		glm::mat4 scaleMatrix;
		glm::mat4 translateMatrix;

		GLfloat squareVertices[8];
	};
}
