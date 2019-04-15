#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class SoundEffects  {
private:
	sf::SoundBuffer pickaxeBuffer;
	sf::Sound pickaxeSound;
	sf::SoundBuffer breakableBuffer;
	sf::Sound breakableSound;
	sf::SoundBuffer ghostDetBuffer;
	sf::Sound ghostDetSound;
	double volume = 50.f;
public:
	SoundEffects();
	void play_break_block();
	void play_pickaxe_hit();
	void play_ghost_detection();
};

