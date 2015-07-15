#include "Demesne.h"

using namespace std;

int main(int argc, char* argv[]) {

	/* Code adapted from the SFML 2 "Window" example */

	//cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

	sf::Window App(sf::VideoMode(800, 600), "Demesne");

	OpenGLRenderer renderer(App);
	GameState state;

	while (App.isOpen()) {
		sf::Event Event;
		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();
		} 

		renderer.Render(state);
	}
}

Demesne::Demesne()
{
}


Demesne::~Demesne()
{
}
