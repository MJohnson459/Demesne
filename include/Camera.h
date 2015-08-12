#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdint.h>
#include <Entity.h>

/// \brief The camera controls the viewport and the Perspective and View matrices.
class Camera
{
public:
	/// Constructor
	///
	/// \param width Width of the viewport
	/// \param height Height of the viewport
	/// \param entity The entity the camera is centered on
	Camera(uint32_t width, uint32_t height, Entity& entity);
	~Camera();

	/// The matrix representing Perspective * View
	glm::mat4 GetPVMatrix();

	/// Update view matrix
	void Update();

	/// Change the viewport size
	void ChangeSize(uint32_t width, uint32_t height);

	/// Zoom recalculates the projection matrix.
	///
	/// \param delta zoom factor
	void Zoom(int delta);

	glm::vec2 ScreenToWorld(int x, int y);

private:
	/// Current position of the camera
	glm::vec3 position;

	/// Store the last view matrix. This is calculated based on entity.position
	glm::mat4 view_matrix;

	/// The projection matrix is orthographic based on HEIGHT and WIDTH
	glm::mat4 projection_matrix;

	/// Entity the camera is centered on
	Entity& entity;

	/// Viewport height
	uint32_t HEIGHT;
	/// Viewport width
	uint32_t WIDTH;

	float zoom;
};


