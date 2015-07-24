#include "OpenGLRenderer.h"


OpenGLRenderer::OpenGLRenderer()
{
	
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		throw;
	}
	
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("data/shaders/SimpleVertexShader.vert", "data/shaders/SimpleFragmentShader.frag");


	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	matrixID = glGetUniformLocation(programID, "MVP");

	// Get a handle for our "myTextureSampler" uniform
	textureID = glGetUniformLocation(programID, "myTextureSampler");

	printf("matrixID: %d\n", matrixID);
	printf("textureID: %d\n", textureID);
}


OpenGLRenderer::~OpenGLRenderer()
{
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vertexArrayID);
}
