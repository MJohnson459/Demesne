#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdint.h>


/// \brief The camera controls the viewport and the Perspective and View matrices.
class Camera
{
public:
	Camera(uint32_t width, uint32_t height);
	~Camera();

	/// The matrix representing Perspective * View
	glm::mat4 GetPVMatrix();

	/// Update view matrix
	void Update();

	/// Change the viewport size
	void ChangeSize(uint32_t width, uint32_t height);

private:
	/// Current position of the camera
	glm::vec3 position;

	/// Viewport height
	uint32_t HEIGHT;
	/// Viewport width
	uint32_t WIDTH;
};


