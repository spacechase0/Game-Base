#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Audio/Music.hpp>

#include "GameBase.hpp"

class Game : public GameBase
{
	public:
		Game();
		virtual ~Game();
	
	private:
		virtual void initialize();
		virtual void terminate();
};

#endif // GAMEBASE_HPP
