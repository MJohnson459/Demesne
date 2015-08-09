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
	glGenBuffers(1, &texture_buffer);


	GenerateBuffers(state.terrain, renderer);


	terrain_texture_atlas = renderer.LoadTexture("data/textures/terrain/stonebrick.dds");
	terrain_texture_atlas = renderer.LoadTexture("data/textures/terrain/dirt.dds");
	terrain_texture_atlas = renderer.LoadTexture("data/textures/terrain/stonebrick.dds");

	
}


TerrainGraphicsComponent::~TerrainGraphicsComponent()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &color_buffer);
	glDeleteBuffers(1, &texture_buffer);
}



void TerrainGraphicsComponent::Render(GameState& state)
{
	if (state.terrain.updated.size() > 0)
	{
		UpdateBuffers(state.terrain, renderer);
		state.terrain.updated.clear();
	}
		

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
	glBindTexture(GL_TEXTURE_2D_ARRAY, terrain_texture_atlas);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(renderer.samplerID, 0);

	//DEBUG_OPENGL("Terrain: Set Up Rendering");

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
	glDisableVertexAttribArray(2);
	glBindTexture(GL_TEXTURE_2D, 0);

	//DEBUG_OPENGL("Terrain: Finished Rendering");

}

void TerrainGraphicsComponent::GenerateBuffers(Terrain& terrain, OpenGLRenderer& renderer)
{
	int vertices = terrain.WIDTH*terrain.HEIGHT * 6;
	g_vertex_buffer_data.clear();
	g_color_buffer_data.clear();
	g_texture_buffer_data.clear();
	g_vertex_buffer_data.reserve(vertices);
	g_color_buffer_data.reserve(vertices);
	g_texture_buffer_data.reserve(vertices);

	int xOffset = terrain.WIDTH / 2;
	int yOffset = terrain.HEIGHT / 2;


	float texture_size = 128.0;
	float texture_per_row = texture_size / 1024.0;
	uint32_t blocks_per_texture = 4;
	float block_texture = 1.0 / blocks_per_texture; // 0.25;

	for (int i = -xOffset; i < xOffset; ++i)
	{
		for (int j = -yOffset; j < yOffset; ++j)
		{
			float a = i + xOffset;
			float b = j + yOffset;
			BlockType type = terrain.block_types[terrain(i, j)];
			g_vertex_buffer_data.push_back(glm::vec3(a, b, 0.0f));
			g_vertex_buffer_data.push_back(glm::vec3(a + 1.0f, b, 0.0f));
			g_vertex_buffer_data.push_back(glm::vec3(a + 1.0f, b + 1.0f, 0.0f));

			g_vertex_buffer_data.push_back(glm::vec3(a, b, 0.0f));
			g_vertex_buffer_data.push_back(glm::vec3(a + 1.0f, b + 1.0f, 0.0f));
			g_vertex_buffer_data.push_back(glm::vec3(a, b + 1.0f, 0.0f));
		}
	}

	g_color_buffer_data.resize(vertices, glm::vec3(0, 0, 0));

	for (int i = -xOffset; i < xOffset; ++i)
	{
		for (int j = -yOffset; j < yOffset; ++j)
		{
			BlockType type = terrain.block_types[terrain(i, j)];
			float u = (i % blocks_per_texture)*block_texture;
			float v = (j % blocks_per_texture)*block_texture;
			g_texture_buffer_data.push_back(glm::vec3(u, v, type.id));
			g_texture_buffer_data.push_back(glm::vec3(u + block_texture, v, type.id));
			g_texture_buffer_data.push_back(glm::vec3(u + block_texture, v + block_texture, type.id));

			g_texture_buffer_data.push_back(glm::vec3(u, v, type.id));
			g_texture_buffer_data.push_back(glm::vec3(u + block_texture, v + block_texture, type.id));
			g_texture_buffer_data.push_back(glm::vec3(u, v + block_texture, type.id));

		}
	}

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size()*sizeof(g_vertex_buffer_data[0]), g_vertex_buffer_data.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, g_color_buffer_data.size()*sizeof(g_color_buffer_data[0]), g_color_buffer_data.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
	glBufferData(GL_ARRAY_BUFFER, g_texture_buffer_data.size()*sizeof(g_texture_buffer_data[0]), g_texture_buffer_data.data(), GL_DYNAMIC_DRAW);

	DEBUG_OPENGL("Initialised Terrain buffers");
}
void TerrainGraphicsComponent::UpdateBuffers(Terrain& terrain, OpenGLRenderer& renderer)
{
	int vertices = terrain.WIDTH*terrain.HEIGHT * 6;
	int xOffset = terrain.WIDTH / 2;
	int yOffset = terrain.HEIGHT / 2;

	float texture_size = 128.0;
	float texture_per_row = texture_size / 1024.0;
	uint32_t blocks_per_texture = 4;
	float block_texture = 1.0 / blocks_per_texture; // 0.25;

	printf("size(): %d, vertices: %d\n", g_texture_buffer_data.size(), vertices);

	for (glm::vec2 pos : terrain.updated)
	{
		int i = floor(pos[0]);
		int j = floor(pos[1]);

		int a = i + xOffset;
		int b = j + yOffset;

		int vertex_index = terrain.HEIGHT*6*a + b*6;

		assert(vertex_index < g_texture_buffer_data.size());

		BlockType type = terrain.block_types[terrain(i, j)];

		printf("updating id: %d to type: %d\n", vertex_index, type.id);
		printf("i: %d, j: %d,  a: %d, b: %d \n", i,j,a,b);

		float u = (a % blocks_per_texture)*block_texture;
		float v = (b % blocks_per_texture)*block_texture;
		g_texture_buffer_data[vertex_index++] = glm::vec3(u, v, type.id);
		g_texture_buffer_data[vertex_index++] = glm::vec3(u + block_texture, v, type.id);
		g_texture_buffer_data[vertex_index++] = glm::vec3(u + block_texture, v + block_texture, type.id);

		g_texture_buffer_data[vertex_index++] = glm::vec3(u, v, type.id);
		g_texture_buffer_data[vertex_index++] = glm::vec3(u + block_texture, v + block_texture, type.id);
		g_texture_buffer_data[vertex_index++] = glm::vec3(u, v + block_texture, type.id);
	}


	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
	glBufferData(GL_ARRAY_BUFFER, g_texture_buffer_data.size()*sizeof(g_texture_buffer_data[0]), g_texture_buffer_data.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	DEBUG_OPENGL("Initialised Terrain buffers");
}