#include "game.hpp"

game::game() : m_texture(nullptr), m_sprite(nullptr) { 
	m_texture = new sf::Texture();
	if (m_texture->loadFromFile("resources/textures/sprite00.png")) {
		m_sprite = new sf::Sprite(*m_texture);
	}
}

game::~game() { 
	delete m_texture;
	delete m_sprite;
}

void game::on_update() { }

void game::on_draw(sf::RenderTarget& rt) { 
	if (m_sprite) rt.draw(*m_sprite);
}
