#include "scenes/MainMenuScene.hpp"

#include <SFML/Window/Event.hpp>

#include "Game.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/OptionsScene.hpp"
#include "Utility.hpp"

MainMenuScene::MainMenuScene( Game& theGame, const SceneChangeEvent& event )
   : Scene::Scene( theGame ),
     font( * theGame.getFont( "res/ken_fonts/kenpixel.ttf" ) )
{
	title.setString( "Game" );
	title.setFont( font );
	title.setCharacterSize( 75 );
	title.setColor( sf::Color::White );
	title.setPosition( ( game.getWindow().getSize().x - title.getLocalBounds().width ) / 2, 25 );
	
	play = title;
	play.setString( "Play" );
	play.setCharacterSize( 35 );
	play.setPosition( ( game.getWindow().getSize().x - play.getLocalBounds().width ) / 2, 200 );
	
	options = play;
	options.setString( "Options" );
	options.setPosition( ( game.getWindow().getSize().x - options.getLocalBounds().width ) / 2, options.getPosition().y );
	options.move( 0, options.getGlobalBounds().height + 10 );
	
	quit = options;
	quit.setString( "Quit" );
	quit.setPosition( ( game.getWindow().getSize().x - quit.getLocalBounds().width ) / 2, quit.getPosition().y );
	quit.move( 0, quit.getGlobalBounds().height + 10 );
}

void MainMenuScene::update()
{
}

void MainMenuScene::update( const sf::Event& event )
{
	if ( event.type == sf::Event::MouseButtonPressed )
	{
		if ( event.mouseButton.button == sf::Mouse::Left )
		{
			if ( play.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
			{
				game.changeScenes< GameScene >();
			}
			else if ( options.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
			{
				game.changeScenes< OptionsScene >();
			}
			else if ( quit.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
			{
				game.close();
			}
		}
	}
}

void MainMenuScene::render( sf::RenderWindow& window )
{
	window.draw( title );
	
	handleHighlight( window, play );
	window.draw( play );
	
	handleHighlight( window, options );
	window.draw( options );
	
	handleHighlight( window, quit );
	window.draw( quit );
}
