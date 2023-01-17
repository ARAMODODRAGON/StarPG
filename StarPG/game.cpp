#include "game.hpp"

game::game() : m_texture(nullptr), m_sprite(nullptr) {
	// subscribe
	subscribe<&game::on_update>("on_update", this);
	subscribe<&game::on_draw>("on_draw", this);
	// load data
	m_texture = new sf::Texture();
	if (m_texture->loadFromFile("resources/textures/sprite00.png")) {
		m_sprite = new sf::Sprite(*m_texture);
	}
}

game::~game() {
	delete m_texture;
	delete m_sprite;
}

void game::on_update(void*) {
	DEBUG_LOG("Test");
}

void game::on_draw(void*) {
	if (m_sprite) renderer::draw(*m_sprite);
}
