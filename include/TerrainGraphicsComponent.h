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

struct Position {
	GLfloat x;
	GLfloat y;
	GLfloat z;

	Position(GLfloat x = 0, GLfloat y = 0)
		:x(x), y(y), z(0){};
};

struct Color {
	GLfloat red;
	GLfloat green;
	GLfloat blue;

	Color(GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0)
		:red(red), green(green), blue(blue){};

	Color(glm::vec3 color)
		:red(color[0]), green(color[1]), blue(color[2]){};

	GLfloat& operator[](std::size_t idx)
	{
		if (idx == 0) return red;
		if (idx == 1) return green;
		if (idx == 2) return blue;
	};

};

class TerrainGraphicsComponent :
	public GraphicsComponent
{
public:
	TerrainGraphicsComponent(GameState& state);
	~TerrainGraphicsComponent();

	void Render(GameState& state);

private:
	
	GLuint programID;

	GLuint VertexArrayID;
	GLuint MatrixID;

	// An array of 3 vectors which represents 3 vertices
	std::vector<Position> g_vertex_buffer_data;
	std::vector<Color> g_color_buffer_data;

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	GLuint colorbuffer;
};

