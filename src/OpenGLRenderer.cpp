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

GLuint OpenGLRenderer::LoadTextures(std::string Filename)
{
	gli::texture2D Texture(gli::load_dds(Filename));
	assert(!Texture.empty());
	gli::gl GL;
	gli::gl::format const Format = GL.translate(Texture.format());
	GLint const MaxLevels = static_cast<GLint>(Texture.levels() - 1);

	GLuint TextureName = 0;
	GLsizei width = 128;
	GLsizei height = 128;
	GLsizei layerCount = 64;
	GLsizei mipLevelCount = 1;

	glGenTextures(1, &TextureName);
	glBindTexture(GL_TEXTURE_2D_ARRAY, TextureName);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipLevelCount, GL_RGBA8, width, height, layerCount);
	DEBUG_OPENGL("glTexStorage3D");

	//Upload pixel data.
	//The first 0 refers to the mipmap level (level 0, since there's only 1)
	//The following 2 zeroes refers to the x and y offsets in case you only want to specify a subrectangle.
	//The final 0 refers to the layer index offset (we start from index 0 and have 2 levels).
	//Altogether you can specify a 3D box subset of the overall texture, but only one mip level at a time.
	glCompressedTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, layerCount, Format.Internal, static_cast<GLsizei>(Texture[0].size()), Texture[0].data());
	DEBUG_OPENGL("glCompressedTexSubImage3D");

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	printf("texture size: %d\n", static_cast<GLsizei>(Texture[0].size()));
	printf("texture Format.Internal: %d\n", Format.Internal);
	printf("texture size.x: %d\n", static_cast<GLsizei>(Texture[0].dimensions().x));
	printf("texture size.y: %d\n", static_cast<GLsizei>(Texture[0].dimensions().y));
	printf("texture id: %d\n", TextureName);

	DEBUG_OPENGL("LoadTextures");
	return TextureName;
}