#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Audio/Music.hpp>

#include "GameBase.hpp"
#include "Options.hpp"

class Game : public GameBase
{
	public:
		Game();
		virtual ~Game();
		
		Options options;
	
	private:
		virtual void initialize();
		virtual void terminate();
};

#endif // GAMEBASE_HPP
