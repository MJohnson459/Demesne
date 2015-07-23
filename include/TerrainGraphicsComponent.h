#pragma once
#include "GraphicsComponent.h"
#include <Terrain.h>
#include <SFML/Window.hpp>
#include <GameState.h>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.hpp>

/// Draws the terrain
class TerrainGraphicsComponent :
	public GraphicsComponent
{
public:
	TerrainGraphicsComponent(GameState& state);
	~TerrainGraphicsComponent();

	/// Render the terrain held in state
	void Render(GameState& state);

private:

	/// Model position matrix
	glm::mat4 modelMatrix;

	// Buffers
	/// Vertex position buffer
	std::vector<glm::vec3> g_vertex_buffer_data;
	/// Color buffer
	std::vector<glm::vec3> g_color_buffer_data;


	// OpenGL variables

	/// Loaded GLSL program
	GLuint programID;

	/// VAO id
	GLuint VertexArrayID;

	/// PVM matrix id
	GLuint MatrixID;

	/// Vertex position buffer id
	GLuint vertexbuffer;
	/// Vertex color buffer id
	GLuint colorbuffer;
	
};

