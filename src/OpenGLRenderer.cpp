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

	textureCount = 0;

	terrainTextureId = 0;

	glGenTextures(1, &terrainTextureId);
	glBindTexture(GL_TEXTURE_2D_ARRAY, terrainTextureId);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 4, 33778, terrainTileWidth, terrainTileHeight, maxTerrainTiles);
	DEBUG_OPENGL("glTexStorage3D");

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(maxTerrainTiles - 1));

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}


OpenGLRenderer::~OpenGLRenderer()
{
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vertexArrayID);
}

GLuint OpenGLRenderer::LoadTexture(std::string Filename)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, terrainTextureId);

	gli::texture2D Texture(gli::load_dds(Filename));
	assert(!Texture.empty());
	gli::gl GL;
	gli::gl::format const Format = GL.translate(Texture.format());

	glCompressedTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, textureCount++,
		static_cast<GLsizei>(Texture[0].dimensions().x),
		static_cast<GLsizei>(Texture[0].dimensions().y),
		1,
		Format.External,
		static_cast<GLsizei>(Texture[0].size()),
		Texture[0].data()
		);
	printf("isCompressed: %s\n", gli::is_compressed(Texture.format()) ? "true" : "false");
	printf("Format.Internal: %d\n", Format.Internal);
	printf("Format.External: %d\n", Format.External);
	printf("size: %d\n", static_cast<GLsizei>(Texture[0].size()));
	printf("size.x: %d\n", static_cast<GLsizei>(Texture[0].dimensions().x));
	printf("size.y: %d\n", static_cast<GLsizei>(Texture[0].dimensions().y));

	DEBUG_OPENGL("glCompressedTexSubImage3D");
	
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_R, Format2.Swizzle[0]);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_G, Format2.Swizzle[1]);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_B, Format2.Swizzle[2]);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_SWIZZLE_A, Format2.Swizzle[3]);

	// GLint param = 0;
	// glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &param);
	// printf("GL_TEXTURE_WIDTH: %d\n", param);
	// glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_HEIGHT, &param);
	// printf("GL_TEXTURE_HEIGHT: %d\n", param);
	// glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_INTERNAL_FORMAT, &param);
	// printf("GL_TEXTURE_INTERNAL_FORMAT: %d\n", param);
	// glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_COMPRESSED, &param);
	// printf("GL_TEXTURE_COMPRESSED: %d\n", param);
	// glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &param);
	// printf("GL_TEXTURE_COMPRESSED_IMAGE_SIZE: %d\n", param);
	// glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_BUFFER_OFFSET, &param);
	// printf("GL_TEXTURE_BUFFER_OFFSET : %d\n", param);
	// glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_DEPTH, &param);
	// printf("GL_TEXTURE_DEPTH: %d\n", param);
	// 
	// glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &param);
	// printf("GL_PIXEL_UNPACK_BUFFER_BINDING: %d\n", param);

	DEBUG_OPENGL("glTexParameteri");

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	return terrainTextureId;
}