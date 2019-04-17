#include "inputs.h"

#include <stdexcept>

using namespace std;
using namespace sf;

std::map<std::string, Keyboard::Key> Inputs::_keyboardMapping;

void Inputs::load_inputs()
{
	Inputs::SetKeyboardKeyCode("Up", Keyboard::Up);
	Inputs::SetKeyboardKeyCode("Down", Keyboard::Down);
	Inputs::SetKeyboardKeyCode("Left", Keyboard::Left);
	Inputs::SetKeyboardKeyCode("Right", Keyboard::Right);
	Inputs::SetKeyboardKeyCode("Dig", Keyboard::Z);
}

Keyboard::Key Inputs::GetKeyboardKeyCode(string control)
{
	auto key = _keyboardMapping.find(control);
	if(key != _keyboardMapping.end())
		return key->second;
}


void Inputs::SetKeyboardKeyCode(string control, Keyboard::Key keycode)
{
	_keyboardMapping[control] = keycode;
}
