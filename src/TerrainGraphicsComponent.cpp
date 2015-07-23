#include "TerrainGraphicsComponent.h"

TerrainGraphicsComponent::TerrainGraphicsComponent(GameState& state)
	:g_vertex_buffer_data()
{
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		throw;
	}
	
	g_vertex_buffer_data.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	g_vertex_buffer_data.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	g_vertex_buffer_data.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	g_color_buffer_data.push_back(glm::vec3(1, 0, 0));
	g_color_buffer_data.push_back(glm::vec3(0, 1, 0));
	g_color_buffer_data.push_back(glm::vec3(0, 0, 1));


	modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(state.terrain.WIDTH / -2.0f, state.terrain.HEIGHT / -2.0f, 0.0f)); // Changes for each model !


	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("data/shaders/SimpleVertexShader.vertexshader", "data/shaders/SimpleFragmentShader.fragmentshader");

	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);


	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	MatrixID = glGetUniformLocation(programID, "MVP");

	glGenBuffers(1, &colorbuffer);	


	g_vertex_buffer_data.clear();
	g_color_buffer_data.clear();
	g_vertex_buffer_data.reserve(state.terrain.WIDTH*state.terrain.HEIGHT);
	g_vertex_buffer_data.reserve(state.terrain.WIDTH*state.terrain.HEIGHT);

	for (int i = 0; i < state.terrain.WIDTH; ++i)
	{
		for (int j = 0; j < state.terrain.HEIGHT; ++j)
		{
			g_vertex_buffer_data.push_back(glm::vec3(i, j, 0));
			g_vertex_buffer_data.push_back(glm::vec3(i + 1.0, j, 0));
			g_vertex_buffer_data.push_back(glm::vec3(i + 1.0, j + 1.0, 0));

			g_vertex_buffer_data.push_back(glm::vec3(i, j, 0));
			g_vertex_buffer_data.push_back(glm::vec3(i + 1.0, j + 1.0, 0));
			g_vertex_buffer_data.push_back(glm::vec3(i, j + 1.0, 0));

			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
		}
	}





	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size()*sizeof(g_vertex_buffer_data[0]), g_vertex_buffer_data.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, g_color_buffer_data.size()*sizeof(g_color_buffer_data[0]), g_color_buffer_data.data(), GL_STATIC_DRAW);
}


TerrainGraphicsComponent::~TerrainGraphicsComponent()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
}



void TerrainGraphicsComponent::Render(GameState& state)
{
	

	// TODO: Cull Terrain

	// Use our shader
	glUseProgram(programID);

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = state.camera.GetPVMatrix() * modelMatrix; // Remember, matrix multiplication is the other way around

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

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

}
