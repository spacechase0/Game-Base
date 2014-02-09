#include "Game.hpp"


Game::Game()
   : GameBase::GameBase( 50, 50 )
{
}

void Game::initialize()
{
	GameBase::initialize();
	//window.setTitle( "Game" );

	changeScenes< GameScene >();
}

void Game::terminate()
{
	GameBase::initialize();
}
