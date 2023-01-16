#include <iostream>
#include <SFML\Main.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

int main(int argc, char** argv) {

	// window
	sf::RenderWindow rw;
	rw.setSize({ 1280, 720 });


	// main loop
	while (rw.isOpen()) {

		// handle events
		sf::Event ev;
		while (rw.pollEvent(ev)) {
			switch (ev.type) {
				case sf::Event::Closed:
					rw.close();
					break;
				default: break;
			}
		}

		// render
		
		// clear the screen to black
		rw.clear();

		// draw

		// show screen
		rw.display();

	}

	return 0;
}