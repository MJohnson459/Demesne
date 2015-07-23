#include "PlayerGraphics.h"


PlayerGraphics::PlayerGraphics(Entity& entity, OpenGLRenderer& renderer)
	: entity(entity)
	, renderer(renderer)
{
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

	glGenBuffers(1, &colorbuffer);

	

	g_color_buffer_data.push_back(glm::vec3(1, 0, 0));
	g_color_buffer_data.push_back(glm::vec3(0, 1, 0));
	g_color_buffer_data.push_back(glm::vec3(0, 0, 1));
	g_color_buffer_data.push_back(glm::vec3(1, 0, 0));
	g_color_buffer_data.push_back(glm::vec3(0, 0, 1));
	g_color_buffer_data.push_back(glm::vec3(1, 0, 1));
	

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, g_color_buffer_data.size()*sizeof(g_color_buffer_data[0]), g_color_buffer_data.data(), GL_STATIC_DRAW);
}


PlayerGraphics::~PlayerGraphics()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
}

void PlayerGraphics::Render(GameState& state)
{
	g_vertex_buffer_data.clear();
	g_vertex_buffer_data.push_back(entity.position);
	g_vertex_buffer_data.push_back(glm::vec3(entity.position[0] + entity.size[0], entity.position[1], entity.position[2]));
	g_vertex_buffer_data.push_back(glm::vec3(entity.position[0] + entity.size[0], entity.position[1] + entity.size[1], entity.position[2]));

	g_vertex_buffer_data.push_back(entity.position);
	g_vertex_buffer_data.push_back(glm::vec3(entity.position[0] + entity.size[0], entity.position[1] + entity.size[1], entity.position[2]));
	g_vertex_buffer_data.push_back(glm::vec3(entity.position[0], entity.position[1] + entity.size[1], entity.position[2]));

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size()*sizeof(g_vertex_buffer_data[0]), g_vertex_buffer_data.data(), GL_STATIC_DRAW);

	// Use our shader
	glUseProgram(renderer.programID);

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = state.camera.GetPVMatrix() * modelMatrix; // Remember, matrix multiplication is the other way around

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	glUniformMatrix4fv(renderer.matrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);


	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, g_vertex_buffer_data.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}