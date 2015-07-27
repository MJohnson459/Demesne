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

	uint32_t width = 1600, height = 1200;

	sf::Window window(sf::VideoMode(width, height), "Demesne");

	sf::ContextSettings settings = window.getSettings();

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;


	Entity player;

	GameState state(player, width, height);
	//TerrainGraphicsComponent renderer(state);

	PlayerController playerController(player);

	std::vector<ControllerComponent *> controllerComponents;
	controllerComponents.push_back(&playerController);

	TerrainPhysicsComponent terrainPhysics(state.terrain);
	std::vector<PhysicsComponent> physicsComponents;
	physicsComponents.push_back(PhysicsComponent(player));


	OpenGLRenderer renderer;
	std::vector<GraphicsComponent *> graphicsComponents;
	graphicsComponents.push_back(new TerrainGraphicsComponent(state, renderer));
	graphicsComponents.push_back(new PlayerGraphics(player, renderer));


	sf::Clock fpsClock;
	float lastTime = 0;
	int fps = 0;

	int MS_PER_UPDATE = 10;
	sf::Clock updateClock;
	double lag = 0.0;

	while (window.isOpen()) {
		double elapsed = updateClock.restart().asMicroseconds()/1000.0;
		lag += elapsed;

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

			if (event.type == sf::Event::KeyPressed)
				playerController.HandleKeyPressed(event.key.code);

			if (event.type == sf::Event::KeyReleased)
				playerController.HandleKeyReleased(event.key.code);
				
		}

		state.camera.Update();
		while (lag >= MS_PER_UPDATE)
		{
			for (ControllerComponent* c : controllerComponents)
			{
				c->Update(state);
			}

			for (PhysicsComponent& p : physicsComponents)
			{
				p.Update(state);
				terrainPhysics.CheckCollision(p);
			}

			lag -= MS_PER_UPDATE;
		}

		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
		glClearColor(0.1f, 0.3f, 8.0f, 0.0f);

		for (GraphicsComponent* g : graphicsComponents)
		{
			g->Render(state);
		}
		

		window.display();

		if (fpsClock.getElapsedTime().asSeconds() > 1.0)
		{

			std::stringstream title;
			title << "Demense (FPS " << 1000.0/fps << ", Position (" << player.position[0] << ", " << player.position[1] << "))";
			window.setTitle(title.str());

			fpsClock.restart();
			fps = 0;
		}

		fps++;

	}
}
