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
	samplerID = glGetUniformLocation(programID, "textureSampler");

	printf("matrixID: %d\n", matrixID);
	printf("textureID: %d\n", samplerID);
}


OpenGLRenderer::~OpenGLRenderer()
{
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vertexArrayID);
}


GLuint OpenGLRenderer::CreateTexture(char const* Filename)
{
	// Check if we have already loaded the file
	auto id = textureMap.find(Filename);
	if (id != textureMap.end())
	{
		return id->second;
	}

	gli::texture2D Texture(gli::load_dds(Filename));
	assert(!Texture.empty());
	gli::gl GL;
	gli::gl::format const Format = GL.translate(Texture.format());
	GLint const MaxLevels = static_cast<GLint>(Texture.levels() - 1);

	GLuint TextureName = 0;
	glGenTextures(1, &TextureName);
	glBindTexture(GL_TEXTURE_2D, TextureName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	printf("texture size: %d\n", static_cast<GLsizei>(Texture[0].size()));
	printf("texture Format.Internal: %d\n", Format.Internal);
	printf("texture size.x: %d\n", static_cast<GLsizei>(Texture[0].dimensions().x));
	printf("texture size.y: %d\n", static_cast<GLsizei>(Texture[0].dimensions().y));
	printf("texture id: %d\n", TextureName);

	glCompressedTexImage2D(GL_TEXTURE_2D, 0, Format.Internal,
		static_cast<GLsizei>(Texture[0].dimensions().x),
		static_cast<GLsizei>(Texture[0].dimensions().y),
		0,
		static_cast<GLsizei>(Texture[0].size()),
		Texture[0].data());

	return TextureName;
}