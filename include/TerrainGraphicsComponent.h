#pragma once
#include "GraphicsComponent.h"
#include <Terrain.h>
#include <SFML/Window.hpp>
#include <GameState.h>
#include <vector>
#include <OpenGLRenderer.h>
#include <iostream>
#include <algorithm> 


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

	/// Generates the complete opengl buffers containing vertices for every terrain block
	void GenerateBuffers(Terrain& terrain, OpenGLRenderer& renderer);
	/// Updates the block type buffer using the terrain.updated vector.
	void UpdateBuffers(Terrain& terrain, OpenGLRenderer& renderer);

	// OpenGL Variables

	OpenGLRenderer& renderer;

	/// Model position matrix
	glm::mat4 modelMatrix;

	// Buffers
	/// Vertex position buffer
	std::vector<glm::vec3> g_vertex_buffer_data;
	/// Color buffer
	std::vector<glm::vec3> g_color_buffer_data;
	/// UV texture coordinate array
	std::vector<glm::vec3> g_texture_buffer_data;

	/// id of the terrain texture
	GLuint terrain_texture_atlas;
	
	/// Vertex position buffer id
	GLuint vertex_buffer;
	/// Vertex color buffer id
	GLuint color_buffer;

	/// texture buffer
	GLuint texture_buffer;	
};

