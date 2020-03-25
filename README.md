
[![Build status](https://ci.appveyor.com/api/projects/status/jpq4daut2bci9vuq?svg=true)](https://ci.appveyor.com/project/Paulfinex/gameengcw)

# Dig IT
Dig It is a 2D top-down game where the player controls a greedy dwarf who ventures into haunted mines. The dwarf was sent to find an ancient treasure armed only of a pick-axe and willpower.

The game puts the player in a maze-like map where the walls are made of “rock blocks”. Some of them can be destroyed by the main mechanic of the game: Dig.

In this way, the player can choose her/his own way by freeing up pace from the map creating new paths.

In order to add more tension to the exploration part of the game, when a block is destroyed, a ghost, nothing at all, or the desired ancient treasure will be spawned on the same position.

We wanted to make the exploration of the mine both exciting and dangerous, and for these reasons, we added this spawning system that balances the possible reward of the next block to be destroyed.

In the future we plan to develop a multiplayer mode, more maps, and a random items drop mechanic which will grant power-ups such as speed boosts, invisibility, crowd controls, etc, adding to the game more unpredictability that reflects the intended experience of a dangerous, mysterious, and rewarding exploration.


## How to build the project

1. Clone this repository.

2. Run Git or Git bash on the repo folder:

   git submodule update --init --recursive

   git submodule add https://github.com/dooglz/Box2D.git lib/b2d

   git submodule init

   git submodule update

3. Use CMake to generate a Visual Studio project on a new folder and open it.

4. Set PROJECT as a start up project.

5. Build and run it.

Website: https://harbrus.itch.io/dig-it

Playtest Reports (report a bug): https://docs.google.com/document/d/1rGg8w-A-XQymuYZOJIXoEyLI3zt2RsqD9JgYLTHDGlQ/edit?usp=sharing
