#include "Demesne.h"

using namespace std;

int main(int argc, char* argv[]) {

	/* Code adapted from the SFML 2 "Window" example */

	//cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

	sf::Window window(sf::VideoMode(800, 600), "Demesne");

	sf::ContextSettings settings = window.getSettings();

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	
	GameState state;
	TerrainGraphicsComponent renderer(state);

	sf::Clock clock;
	float lastTime = 0;
	int fps = 0;

	while (window.isOpen()) {
		sf::Event Event;
		while (window.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				window.close();
			
		} 

		state.camera.Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
		renderer.Render(state);

		window.display();

		if (clock.getElapsedTime().asSeconds() > 1.0)
		{
		
			std::stringstream title;
			title << "Demense (FPS " << fps << ")";
			window.setTitle(title.str());

			clock.restart();
			fps = 0;
		}

		fps++;
		
	}
}

Demesne::Demesne()
{
}


Demesne::~Demesne()
{
}
