#pragma once
#include "GraphicsComponent.h"
#include <OpenGLRenderer.h>
#include <Entity.h>

/// The graphics component of the player entity
class PlayerGraphics :
	public GraphicsComponent
{
public:
	PlayerGraphics(Entity& entity, OpenGLRenderer& renderer);
	~PlayerGraphics();

	/// Render the player
	void Render(GameState& state);

private:
	/// The player entity
	Entity& entity;

	OpenGLRenderer& renderer;


	/// Model position matrix
	glm::mat4 modelMatrix;

	// Buffers
	/// Vertex position buffer
	std::vector<glm::vec3> g_vertex_buffer_data;
	/// Color buffer
	std::vector<glm::vec3> g_color_buffer_data;


	// OpenGL variables

	/// PVM matrix id
	GLuint MatrixID;

	/// Vertex position buffer id
	GLuint vertexbuffer;
	/// Vertex color buffer id
	GLuint colorbuffer;
};

