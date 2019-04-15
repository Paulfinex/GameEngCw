#include "sound.h"

#include<iostream>
using namespace std;



SoundEffects::SoundEffects()
{
	breakableBuffer.loadFromFile("res/sounds/breakable.wav");
	pickaxeBuffer.loadFromFile("res/sounds/pickaxe.wav");
	ghostDetBuffer.loadFromFile("res/sounds/pickaxe.wav");
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


