#include "renderer.hpp"

void renderer::clear(const sf::Color& color) { 
	s_target->clear(color);
}

void renderer::set_view(const sf::View& view) { 
	s_target->setView(view);
}

const sf::View& renderer::get_view() {
	return s_target->getView();
}

const sf::View& renderer::get_default_view() {
	return s_target->getDefaultView();
}

sf::IntRect renderer::get_viewport(const sf::View& view) {
	return s_target->getViewport(view);
}

sf::Vector2f renderer::map_pixel_to_coords(const sf::Vector2i& point) {
	return s_target->mapPixelToCoords(point);
}

sf::Vector2f renderer::map_pixel_to_coords(const sf::Vector2i& point, const sf::View& view) {
	return s_target->mapPixelToCoords(point, view);
}

sf::Vector2i renderer::map_coords_to_pixel(const sf::Vector2f& point) {
	return s_target->mapCoordsToPixel(point);
}

sf::Vector2i renderer::map_coords_to_pixel(const sf::Vector2f& point, const sf::View& view) {
	return s_target->mapCoordsToPixel(point, view);
}

void renderer::draw(const sf::Drawable& drawable, const sf::RenderStates& states) { 
	s_target->draw(drawable, states);
}

void renderer::draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates& states) { 
	s_target->draw(vertices, vertexCount, type, states);
}

void renderer::draw(const sf::VertexBuffer& vertexBuffer, const sf::RenderStates& states) { 
	s_target->draw(vertexBuffer, states);
}

void renderer::draw(const sf::VertexBuffer& vertexBuffer, std::size_t firstVertex, std::size_t vertexCount, const sf::RenderStates& states) { 
	s_target->draw(vertexBuffer, firstVertex, vertexCount, states);
}

sf::Vector2u renderer::get_size() {
	return s_target->getSize();
}

void renderer::push_gl_states() { 
	s_target->pushGLStates();
}

void renderer::pop_gl_states() { 
	s_target->popGLStates();
}

void renderer::reset_gl_states() { 
	s_target->resetGLStates();
}

void renderer::__set_target(sf::RenderTarget* target) { 
	s_target = target;
}
