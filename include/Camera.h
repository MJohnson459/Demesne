#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 GetViewMatrix();

	void Update();

private:
	glm::vec3 position;
};


