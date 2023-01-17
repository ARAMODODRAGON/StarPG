#include <iostream>
#include <SFML\Main.hpp>
#include <SFML\Window.hpp>
#include "renderer.hpp"
#include "game.hpp"

int main(int argc, char** argv) {

	// window
	sf::RenderWindow rw(sf::VideoMode(1280, 720), "Hello World!");
	renderer::__set_target(&rw);

	game* g = new game();

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
		object::send("on_update");

		// clear the screen to black
		rw.clear();

		// draw the game
		object::send("on_draw");

		// show screen
		rw.display();

	}

	delete g, g = nullptr;

	return 0;
}