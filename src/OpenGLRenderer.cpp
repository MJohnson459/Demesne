#include "OpenGLRenderer.h"


OpenGLRenderer::OpenGLRenderer(sf::Window& window)
	: window(window)
{
}


OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::Render(GameState& state)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
	glLoadIdentity();

	RenderTerrain(state.terrain);

	window.display();

}

void OpenGLRenderer::RenderTerrain(Terrain& terrain)
{
	
	
	
	
	
	
	
	
	
	glLoadIdentity();

	glBegin(GL_TRIANGLES);                      // Drawing Using Triangles
	glVertex3f(0.0f, 1.0f, 0.0f);              // Top
	glVertex3f(-1.0f, -1.0f, 0.0f);              // Bottom Left
	glVertex3f(1.0f, -1.0f, 0.0f);              // Bottom Right
	glEnd();

}