#ifndef GAME_HPP
#define GAME_HPP
#include "object.hpp"
#include <SFML\Graphics.hpp>

class game final : public object {
public:

	game();
	virtual ~game();

	void on_update();
	void on_draw(sf::RenderTarget& rt);

private:
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;
};

#endif // !GAME_HPP