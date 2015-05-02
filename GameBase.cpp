#include "GameBase.hpp"

#include <SFML/Window/Event.hpp>

#include "Game.hpp"
#include "Scene.hpp"
#include "Utility.hpp"

GameBase::GameBase( unsigned int theUpdateRate, unsigned int theRenderRate )
   : updateRate( theUpdateRate ),
     renderRate( theRenderRate ),
     isRunning( false )
{
	options.load( getWritablePathFor( "config.ini" ) );
}

GameBase::~GameBase()
{
	options.save( getWritablePathFor( "config.ini" ) );
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
			window.setView( sf::View( sf::FloatRect( 0, 0, window.getSize().x, window.getSize().y ) ) );
		}
		
		options.updateInput();
		sf::Event event;
		while ( window.pollEvent( event ) )
		{
			if ( event.type == sf::Event::Closed )
			{
				close();
			}
			#ifdef SFML_SYSTEM_IOS
			else if ( event.type == sf::Event::LostFocus )
			{
				options.save( getWritablePathFor( "config.ini" ) );
			}
			#endif

			currentScene->update( event );
		}
		while ( updateBuffer >= DELTA )
		{
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
}

void GameBase::terminate()
{
}

Game* GameBase::getGame()
{
	return dynamic_cast< Game* >( this );
}
