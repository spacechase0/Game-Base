#include "GameBase.hpp"

#include <iostream>

#include "Scene.hpp"
//#include "scenes/GameBaseScene.hpp"

GameBase::GameBase( unsigned int theUpdateRate, unsigned int theRenderRate )
   : updateRate( theUpdateRate ),
     renderRate( theRenderRate ),
     isRunning( false )
{
}

void GameBase::run()
{
	initialize();

	const float DELTA = 1.f / updateRate;
	float updateBuffer = 0.f; // Can't think of a good name. :P
	sf::Clock updateTimer;

	isRunning = true;
	while ( isRunning )
	{
		if ( nextScene )
		{
			currentScene = nextScene;
			nextScene.reset();
		}

		while ( updateBuffer >= DELTA )
		{
			sf::Event event;
			while ( window.pollEvent( event ) )
			{
				if ( event.type == sf::Event::Closed )
				{
					close();
				}

				currentScene->update( event );
			}

			currentScene->update();

			updateBuffer -= DELTA;
		}
		updateBuffer += updateTimer.restart().asSeconds();

		window.clear();
		currentScene->render( window );
		window.display();
	}

	terminate();
}

void GameBase::close()
{
	isRunning = false;
}

void GameBase::changeScenes( const std::string& name, SceneChangeEvent event )
{
	nextScene = name;
	changeEvent = event;
}

std::shared_ptr< Scene > GameBase::getScene( const std::string& name )
{
	if ( scenes.find( name ) == scenes.end() )
	{
		std::cout << "Failed to find scene '" << name << "'." << std::endl;
		return std::shared_ptr< Scene >();
	}

	return scenes.find( name )->second;
}

unsigned int GameBase::getUpdateRate() const
{
	return updateRate;
}

unsigned int GameBase::getRenderRate() const
{
	return renderRate;
}

sf::RenderWindow& GameBase::getWindow()
{
	return window;
}

const sf::RenderWindow& GameBase::getWindow() const
{
	return window;
}

void GameBase::initialize()
{
	window.create( sf::VideoMode( 640, 480 ), "Game" );
	window.setFramerateLimit( renderRate );

	//addScene( "Game", std::shared_ptr< Scene >( new GameBaseScene( * this ) ) );

	//changeScenes( "Game", SceneChangeEvent() );
}

void GameBase::terminate()
{
}

void GameBase::addScene( const std::string& name, std::shared_ptr< Scene > scene )
{
	scenes.insert( std::make_pair( name, scene ) );
}
