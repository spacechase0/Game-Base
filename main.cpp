#include <util/Logger.hpp>

#include "Game.hpp"

int main()
{
	util::Logger::setName( "Log", "log.txt" );
	
    Game game;
    game.run();
}
