////////////////////////////////////////////////////////////
//
// Game Base
// Copyright (C) 2013 Chase Warrington (staff@spacechase0.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

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
		std::shared_ptr< Scene > scene;
		if ( currentScene != nextScene )
		{
			if ( currentScene != "" )
			{
				scenes[ currentScene ]->terminate();
			}

			scene = scenes[ nextScene ];
			scene->initialize( changeEvent );

			currentScene = nextScene;
		}
		else if ( currentScene != "" )
		{
			scene = scenes[ currentScene ];
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

				scene->update( event );
			}

			scene->update();

			updateBuffer -= DELTA;
		}
		updateBuffer += updateTimer.restart().asSeconds();

		window.clear();
		scene->render( window );
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
