#pragma once
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class Inputs
{
private:
	static std::map<std::string, sf::Keyboard::Key> _keyboardMapping;

public:
	static void load_inputs();
	static sf::Keyboard::Key GetKeyboardKeyCode(std::string control);
	static void SetKeyboardKeyCode(std::string control, sf::Keyboard::Key keycode);
};