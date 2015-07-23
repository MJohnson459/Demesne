#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.hpp>

class OpenGLRenderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	// OpenGL variables

	/// Loaded GLSL program
	GLuint programID;

	/// VAO id
	GLuint vertexArrayID;

	/// PVM matrix id
	GLuint matrixID;
};

