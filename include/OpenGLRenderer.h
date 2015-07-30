#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.hpp>
#include <cstdio>
#include <map>
#include <gli/gli.hpp>

#define DEBUG

#ifdef DEBUG
#define DEBUG_OPENGL(str) do { \
	GLenum err; \
	while ((err = glGetError()) != GL_NO_ERROR) {\
		printf("%s\n", str); \
		printf("OpenGL error: %s\n", gluErrorString(err));\
	}\
} while( false )
#else
#define DEBUG_OPENGL(str) do { } while ( false )
#endif

class OpenGLRenderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	/// Load texture from file
	GLuint CreateTexture(char const* Filename);

	GLuint LoadTexture(std::string path);

	GLint textureCount;

	// OpenGL variables

	/// Loaded GLSL program
	GLuint programID;

	/// VAO id
	GLuint vertexArrayID;

	/// PVM matrix id
	GLuint matrixID;

	GLuint samplerID;

	std::map<std::string, GLuint> textureMap;


	// Terrain Textures
	GLuint terrainTextureId;
	const GLsizei terrainTileWidth = 128;
	const GLsizei terrainTileHeight = 128;
	const GLsizei maxTerrainTiles = 64;

	
};

