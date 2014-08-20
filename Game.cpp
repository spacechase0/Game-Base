#include "Game.hpp"

#include "scenes/MainMenuScene.hpp"

Game::Game()
   : GameBase::GameBase( 50, 50 )
{
	options.load( "config.ini" );
}

Game::~Game()
{
	options.save( "config.ini" );
}

void Game::initialize()
{
	GameBase::initialize();
	//window.setTitle( "Game" );

	changeScenes< MainMenuScene >();
}

void Game::terminate()
{
	GameBase::initialize();
}
