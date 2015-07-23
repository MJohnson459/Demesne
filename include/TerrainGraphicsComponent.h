#pragma once
#include "GraphicsComponent.h"
#include <Terrain.h>
#include <SFML/Window.hpp>
#include <GameState.h>
#include <vector>
#include <OpenGLRenderer.h>


/// Draws the terrain
class TerrainGraphicsComponent :
	public GraphicsComponent
{
public:
	TerrainGraphicsComponent(GameState& state, OpenGLRenderer& renderer);
	~TerrainGraphicsComponent();

	/// Render the terrain held in state
	void Render(GameState& state);

private:

	OpenGLRenderer& renderer;

	/// Model position matrix
	glm::mat4 modelMatrix;

	// Buffers
	/// Vertex position buffer
	std::vector<glm::vec3> g_vertex_buffer_data;
	/// Color buffer
	std::vector<glm::vec3> g_color_buffer_data;


	

	/// Vertex position buffer id
	GLuint vertexbuffer;
	/// Vertex color buffer id
	GLuint colorbuffer;
	
};

