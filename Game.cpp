#include "Game.hpp"

#include "scenes/MainMenuScene.hpp"

Game::Game()
   : GameBase::GameBase( 50, 50 )
{
}

Game::~Game()
{
}

void Game::initialize()
{
	GameBase::initialize();

	changeScenes< MainMenuScene >();
}

void Game::terminate()
{
	GameBase::initialize();
}
