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
	sf::SoundBuffer tickBuffer;
	sf::Sound tickSound;
	sf::SoundBuffer clickBuffer;
	sf::Sound clickSound;
	sf::SoundBuffer treasureSpawnBuffer;
	sf::Sound treasureSpawnSound;
	sf::SoundBuffer treasureLootBuffer;
	sf::Sound treasureLootSound;
	sf::SoundBuffer grooveMusicBuffer;
	sf::Sound grooveMusicSound;
	sf::SoundBuffer timerBuffer;
	sf::Sound timerSound;
	sf::SoundBuffer chasingBuffer;
	sf::Sound chasingSound;
	sf::SoundBuffer defeatBuffer;
	sf::Sound defeatSound;
	sf::SoundBuffer victoryBuffer;
	sf::Sound victorySound;
	sf::SoundBuffer ghostSpawnBuffer;
	sf::Sound ghostSpawnSound;

	double volume = 30.f;
	double main_theme_volume = 10.0f;
public:
	SoundEffects();
	void stop_all();
	void play_defeat();
	void play_ghost_spawn();
	void play_chasing();
	void stop_chasing();
	void play_timer();
	void stop_timer();
	void play_groove();
	void stop_groove();
	void play_treasure_loot();
	void play_trasure_spawn();
	void play_tick();
	void play_click();
	void play_break_block();
	void play_pickaxe_hit();
	void play_ghost_detection();
	void play_victory();
	void setVolume(int level);
	void setVolumeMainTheme(int level);
};

