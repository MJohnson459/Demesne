#include "Camera.h"

Camera::Camera()
	:position(0,0,50)
{
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	// Camera matrix
	return glm::lookAt(
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