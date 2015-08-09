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
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetPVMatrix()
{
	// Focus on centre of block (0,0)
	
	glm::mat4 Projection = glm::ortho(WIDTH / -zoom + 1, WIDTH / zoom + 1, HEIGHT / -zoom + 1, HEIGHT / zoom + 1, 0.1f, 100.0f);


	// Camera matrix
	return Projection*glm::lookAt(
		entity.position + position, // Camera in World Space
		glm::vec3(entity.position[0], entity.position[1], 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
}

void Camera::Update() 
{
}

void Camera::ChangeSize(uint32_t width, uint32_t height)
{
	WIDTH = width;
	HEIGHT = height;
}

void Camera::Zoom(int delta)
{
	zoom += delta;
}

glm::vec2 Camera::ScreenToWorld(int x, int y)
{

	//std::cout << "************************" << std::endl;
	//std::cout << "x: " << x << " y: " << y << std::endl;

	glm::vec3 window_coord(x, HEIGHT - y, 0);

	//std::cout << "window_coord: " << glm::to_string(window_coord) << std::endl;

	glm::mat4 view = glm::lookAt(
		entity.position + position, // Camera in World Space
		glm::vec3(entity.position[0], entity.position[1], 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	//std::cout << "view: " << glm::to_string(view) << std::endl;

	glm::mat4 projection = glm::ortho(WIDTH / -zoom + 1, WIDTH / zoom + 1, HEIGHT / -zoom + 1, HEIGHT / zoom + 1, 0.1f, 100.0f);

	//std::cout << "projection: " << glm::to_string(projection) << std::endl;

	glm::vec4 viewport(0, 0, WIDTH, HEIGHT);

	

	glm::vec3 pos = glm::unProject(window_coord, view, projection, viewport);

	//std::cout << "pos: " << glm::to_string(pos) << std::endl;

	return glm::vec2(pos[0], pos[1]);
}