#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(double dt) {
	_text.setPosition(_parent->getPosition());
}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
	: Component(p), _string(str) {
	_text.setString(_string);
	_font = Resources::get<sf::Font>("VCR_OSD_MONO_1.001.ttf");
	_text.setFont(*_font);
}

void TextComponent::SetText(const std::string& str) {
	_string = str;
	_text.setString(_string);
}