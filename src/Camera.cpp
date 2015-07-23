#include "Camera.h"

Camera::Camera(uint32_t width, uint32_t height)
	:position(0,0,50)
	, HEIGHT(height)
	, WIDTH(width)
{
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetPVMatrix()
{

	glm::mat4 Projection = glm::ortho(0.0f, WIDTH/20.0f, 0.0f, HEIGHT/20.0f, 0.1f, 100.0f);


	// Camera matrix
	return Projection*glm::lookAt(
		position, // Camera is at (4,3,3), in World Space
		glm::vec3(position[0], position[1], 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
}

void Camera::Update() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		position[0] -= 0.005f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position[0] += 0.005f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		position[1] += 0.005f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position[1] -= 0.005f;
	}
}

void Camera::ChangeSize(uint32_t width, uint32_t height)
{
	WIDTH = width;
	HEIGHT = height;
}