#include "TerrainGraphicsComponent.h"

#include <gli/gli.hpp>

TerrainGraphicsComponent::TerrainGraphicsComponent(GameState& state, OpenGLRenderer& renderer)
	: renderer(renderer)
{
	
	
	g_vertex_buffer_data.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	g_vertex_buffer_data.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	g_vertex_buffer_data.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	g_color_buffer_data.push_back(glm::vec3(1, 0, 0));
	g_color_buffer_data.push_back(glm::vec3(0, 1, 0));
	g_color_buffer_data.push_back(glm::vec3(0, 0, 1));


	modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(state.terrain.WIDTH / -2.0f, state.terrain.HEIGHT / -2.0f, 0.0f)); // Changes for each model !

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertex_buffer);
	glGenBuffers(1, &color_buffer);	


	g_vertex_buffer_data.clear();
	g_color_buffer_data.clear();
	g_vertex_buffer_data.reserve(state.terrain.WIDTH*state.terrain.HEIGHT);
	g_color_buffer_data.reserve(state.terrain.WIDTH*state.terrain.HEIGHT);

	for (int i = 0; i < state.terrain.WIDTH; ++i)
	{
		for (int j = 0; j < state.terrain.HEIGHT; ++j)
		{
			
		}
	}

	int xOffset = state.terrain.WIDTH / 2;
	int yOffset = state.terrain.HEIGHT / 2;

	float block_texture = 0.25;

	for (int i = -xOffset; i < xOffset / 2; ++i)
	{
		for (int j = -yOffset; j < yOffset / 2; ++j)
		{
			if (state.terrain(i, j) == 0) continue;

			float a = i + xOffset;
			float b = j + yOffset;
			g_vertex_buffer_data.push_back(glm::vec3(a,        b,        0.0f));
			g_vertex_buffer_data.push_back(glm::vec3(a + 1.0f, b,        0.0f));
			g_vertex_buffer_data.push_back(glm::vec3(a + 1.0f, b + 1.0f, 0.0f));

			g_vertex_buffer_data.push_back(glm::vec3(a,        b,        0.0f));
			g_vertex_buffer_data.push_back(glm::vec3(a + 1.0f, b + 1.0f, 0.0f));
			g_vertex_buffer_data.push_back(glm::vec3(a,        b + 1.0f, 0.0f));

			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);
			g_color_buffer_data.push_back(state.terrain.block_types[state.terrain(i, j)].color);

			float u = (i & 0x03)*block_texture;
			float v = (j & 0x03)*block_texture;
			g_texture_buffer_data.push_back(glm::vec2(u, v));
			g_texture_buffer_data.push_back(glm::vec2(u + block_texture, v));
			g_texture_buffer_data.push_back(glm::vec2(u + block_texture, v + block_texture));

			g_texture_buffer_data.push_back(glm::vec2(u, v));
			g_texture_buffer_data.push_back(glm::vec2(u + block_texture, v + block_texture));
			g_texture_buffer_data.push_back(glm::vec2(u, v + block_texture));
			
		}
	}


	terrain_texture_atlas = renderer.CreateTexture("data/textures/terrain/dirt.dds");

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size()*sizeof(g_vertex_buffer_data[0]), g_vertex_buffer_data.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, g_color_buffer_data.size()*sizeof(g_color_buffer_data[0]), g_color_buffer_data.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
	glBufferData(GL_ARRAY_BUFFER, g_texture_buffer_data.size()*sizeof(g_texture_buffer_data[0]), g_texture_buffer_data.data(), GL_STATIC_DRAW);

	
	DEBUG_OPENGL("Initialised Terrain buffers");
}


TerrainGraphicsComponent::~TerrainGraphicsComponent()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &color_buffer);
}



void TerrainGraphicsComponent::Render(GameState& state)
{
	

	// TODO: Cull Terrain

	// Use our shader
	glUseProgram(renderer.programID);

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = state.camera.GetPVMatrix() * modelMatrix; // Remember, matrix multiplication is the other way around

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	glUniformMatrix4fv(renderer.matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, terrain_texture_atlas);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(renderer.samplerID, 0);

	DEBUG_OPENGL("Terrain: Set Up Rendering");

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);
	

	// 3nd attribute buffer : texture uv
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, g_vertex_buffer_data.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindTexture(GL_TEXTURE_2D, 0);

	DEBUG_OPENGL("Terrain: Finished Rendering");

}