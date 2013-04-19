#ifndef GAME_HPP
#define GAME_HPP

#include "GameBase.hpp"

class Game : public GameBase
{
	public:
		Game();
	
	private:
		virtual void initialize();
		virtual void terminate();
};

#endif // GAMEBASE_HPP
