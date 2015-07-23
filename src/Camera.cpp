#include "Camera.h"

Camera::Camera(uint32_t width, uint32_t height, Entity& entity)
	: position(0,0,50)
	, entity(entity)
	, HEIGHT(height)
	, WIDTH(width)
{
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetPVMatrix()
{
	// Focus on centre of block (0,0)
	glm::mat4 Projection = glm::ortho(WIDTH / -40.0f + 1, WIDTH / 40.0f + 1, HEIGHT / -40.0f + 1, HEIGHT / 40.0f + 1, 0.1f, 100.0f);


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