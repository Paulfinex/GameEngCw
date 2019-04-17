#include "sound.h"

#include<iostream>
using namespace std;



SoundEffects::SoundEffects()
{
	breakableBuffer.loadFromFile("res/sounds/breakable.wav");
	pickaxeBuffer.loadFromFile("res/sounds/pickaxe.wav");
	ghostDetBuffer.loadFromFile("res/sounds/pickaxe.wav");// Da cambiare ____________________
	tickBuffer.loadFromFile("res/sounds/metalTick.ogg");
	clickBuffer.loadFromFile("res/sounds/metalClick.ogg");
	grooveMusicBuffer.loadFromFile("res/sounds/mainGroove.wav");
	timerBuffer.loadFromFile("res/sounds/clock.wav");
	treasureLootBuffer.loadFromFile("res/sounds/treasure.wav");
	treasureSpawnBuffer.loadFromFile("res/sounds/treasure_spawn.wav");
	chasingBuffer.loadFromFile("res/sounds/chasing.wav");
}
void SoundEffects::play_chasing()
{
	chasingSound.setVolume(volume);
	chasingSound.setBuffer(chasingBuffer);
	chasingSound.play();
	chasingSound.setLoop(true);
}
void SoundEffects::stop_chasing()
{
	chasingSound.setLoop(false);
}
void SoundEffects::play_timer()
{
	timerSound.setVolume(volume);
	timerSound.setBuffer(timerBuffer);
	timerSound.play();
	timerSound.setLoop(true);
}
void SoundEffects::stop_timer()
{
	timerSound.setLoop(false);
}
void SoundEffects::play_groove()
{
	grooveMusicSound.setVolume(volume);
	grooveMusicSound.setBuffer(grooveMusicBuffer);
	grooveMusicSound.play();
	grooveMusicSound.setLoop(true);
}
void SoundEffects::stop_groove()
{
	grooveMusicSound.setLoop(false);
}
void SoundEffects::play_treasure_loot()
{
	treasureLootSound.setVolume(volume);
	treasureLootSound.setBuffer(treasureLootBuffer);
	treasureLootSound.play();
}
void SoundEffects::play_trasure_spawn()
{
}
void SoundEffects::play_tick()
{
	clickSound.setVolume(volume);
	clickSound.setBuffer(clickBuffer);
	clickSound.play();
}
void SoundEffects::play_click()
{
	breakableSound.setVolume(volume);
	breakableSound.setBuffer(breakableBuffer);
	breakableSound.play();
}
void SoundEffects::play_break_block()
{
	breakableSound.setVolume(volume);
	breakableSound.setBuffer(breakableBuffer);
	breakableSound.play();
}


void SoundEffects::play_pickaxe_hit()
{

	pickaxeSound.setVolume(volume);
	pickaxeSound.setBuffer(pickaxeBuffer);
	pickaxeSound.play();

}

void SoundEffects::play_ghost_detection()
{

	ghostDetSound.setVolume(volume);
	ghostDetSound.setBuffer(ghostDetBuffer);
	ghostDetSound.play();
}


