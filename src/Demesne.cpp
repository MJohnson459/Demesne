#include "Demesne.h"

using namespace std;



int main(int argc, char* argv[]) {
	Demesne demesne;
	demesne.Execute();
}

Demesne::Demesne()
{
}


Demesne::~Demesne()
{
}

void Demesne::Execute()
{
	/* Code adapted from the SFML 2 "Window" example */

	//cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

	sf::Window window(sf::VideoMode(800, 600), "Demesne");

	sf::ContextSettings settings = window.getSettings();

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;


	GameState state;
	//TerrainGraphicsComponent renderer(state);


	Entity player;

	std::vector<ControllerComponent *> controllerComponents;
	controllerComponents.push_back(new PlayerController(player));

	std::vector<PhysicsComponent> physicsComponents;
	physicsComponents.push_back(PhysicsComponent(player));

	std::vector<GraphicsComponent *> graphicsComponents;
	graphicsComponents.push_back(new PlayerGraphics(player));
	graphicsComponents.push_back(new TerrainGraphicsComponent(state));


	sf::Clock clock;
	float lastTime = 0;
	int fps = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::Resized)
			{
				state.camera.ChangeSize(event.size.width, event.size.height);
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
				
		}

		state.camera.Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
		glClearColor(0.1f, 0.3f, 8.0f, 0.0f);

		for (ControllerComponent* c : controllerComponents)
		{
			c->Update(state);
		}

		for (PhysicsComponent& p : physicsComponents)
		{
			p.Update(state);
		}

		for (GraphicsComponent* g : graphicsComponents)
		{
			g->Render(state);
		}
		

		window.display();

		if (clock.getElapsedTime().asSeconds() > 1.0)
		{

			std::stringstream title;
			title << "Demense (FPS " << 1000.0/fps << ")";
			window.setTitle(title.str());

			clock.restart();
			fps = 0;
		}

		fps++;

	}
}
