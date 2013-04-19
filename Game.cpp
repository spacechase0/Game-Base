#include "Game.hpp"

#include "scenes/GameScene.hpp"

Game::Game()
   : GameBase::GameBase( 50, 50 )
{
}

void Game::initialize()
{
	GameBase::initialize();
	//window.setTitle( "Game" );

	addScene( "Game", std::shared_ptr< Scene >( new GameScene( * this ) ) );

	changeScenes( "Game", SceneChangeEvent() );
}

void Game::terminate()
{
	GameBase::initialize();
}
