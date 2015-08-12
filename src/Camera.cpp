#include "Camera.h"

#include "glm/ext.hpp"
#include <iostream>

Camera::Camera(uint32_t width, uint32_t height, Entity& entity)
	: position(0,0,50)
	, entity(entity)
	, HEIGHT(height)
	, WIDTH(width)
	, zoom(30.0f)
{
	view_matrix = glm::lookAt(
		entity.position + position, // Camera in World Space
		glm::vec3(entity.position[0], entity.position[1], 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// Focus on centre of block (0,0)
	projection_matrix = glm::ortho(WIDTH / -zoom + 1, WIDTH / zoom + 1, HEIGHT / -zoom + 1, HEIGHT / zoom + 1, 0.1f, 100.0f);
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetPVMatrix()
{
	// Camera matrix
	return projection_matrix * view_matrix;
}

void Camera::Update() 
{
	view_matrix = glm::lookAt(
		entity.position + position, // Camera in World Space
		glm::vec3(entity.position[0], entity.position[1], 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
}

void Camera::ChangeSize(uint32_t width, uint32_t height)
{
	WIDTH = width;
	HEIGHT = height;
}

void Camera::Zoom(int delta)
{
	zoom += delta;
	projection_matrix = glm::ortho(WIDTH / -zoom + 1, WIDTH / zoom + 1, HEIGHT / -zoom + 1, HEIGHT / zoom + 1, 0.1f, 100.0f);
}

glm::vec2 Camera::ScreenToWorld(int x, int y)
{
	glm::vec3 window_coord(x, HEIGHT - y, 0);

	glm::vec4 viewport(0, 0, WIDTH, HEIGHT);

	glm::vec3 pos = glm::unProject(window_coord, view_matrix, projection_matrix, viewport);

	//std::cout << "pos: " << glm::to_string(pos) << std::endl;

	return glm::vec2(pos[0], pos[1]);
}