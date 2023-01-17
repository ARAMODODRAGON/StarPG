#ifndef GAME_HPP
#define GAME_HPP
#include "object.hpp"
#include "renderer.hpp"
#include "debug.hpp"

class game final : public object {
public:

	game();
	virtual ~game();

private:

	void on_update(void*);
	void on_draw(void*);

	sf::Texture* m_texture;
	sf::Sprite* m_sprite;
};

#endif // !GAME_HPP