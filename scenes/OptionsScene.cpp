#include "scenes/OptionsScene.hpp"

#include <SFML/Audio/Listener.hpp>
#include <SFML/Window/Event.hpp>

#include "Game.hpp"
#include "scenes/MainMenuScene.hpp"
#include "scenes/ControlsScene.hpp"
#include "Utility.hpp"

OptionsScene::OptionsScene( Game& theGame, const SceneChangeEvent& event )
   : Scene::Scene( theGame ),
     font( * theGame.getFont( "res/ken_fonts/kenpixel.ttf" ) )
{
	title.setString( "Options" );
	title.setFont( font );
	title.setCharacterSize( 45 );
	title.setColor( sf::Color::White );
	title.setPosition( ( game.getWindow().getSize().x - title.getLocalBounds().width ) / 2, 35 );
	
	volume = title;
	volume.setString( "Volume" );
	volume.setCharacterSize( 30 );
	volume.setPosition( 50, 125 );
	
	float width = game.getWindow().getSize().x - ( 50 * 3 ) - volume.getGlobalBounds().width;
	volumeSliderBg.setSize( sf::Vector2f( width, 10 ) );
	volumeSliderBg.setFillColor( sf::Color::White );
	volumeSliderBg.setPosition( volume.getGlobalBounds().width + ( 50 * 2 ), volume.getPosition().y + 14 );
	
	volumeSliderFg.setSize( sf::Vector2f( 5, 30 ) );
	volumeSliderFg.setFillColor( sf::Color( 128, 128, 128 ) );
	volumeSliderFg.setOutlineColor( sf::Color::Black );
	volumeSliderFg.setOutlineThickness( 1 );
	
	controls = volume;
	controls.setString( "Controls" );
	controls.setPosition( ( game.getWindow().getSize().x - controls.getLocalBounds().width ) / 2,
	                      game.getWindow().getSize().y - controls.getLocalBounds().height - 75 );
	
	defaults = volume;
	defaults.setString( "Defaults" );
	defaults.setPosition( 50, game.getWindow().getSize().y - defaults.getLocalBounds().height - 25 );
	
	back = defaults;
	back.setString( "Back" );
	back.setPosition( game.getWindow().getSize().x - 50, defaults.getPosition().y );
	back.setOrigin( back.getGlobalBounds().width, 0 );
}

void OptionsScene::update()
{
}

void OptionsScene::update( const sf::Event& event )
{
	if ( event.type == sf::Event::MouseMoved )
	{
		if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
		{
			sf::FloatRect bounds = volumeSliderBg.getGlobalBounds();
			bounds.top -= 10;
			bounds.height += 20;
			
			if ( bounds.contains( event.mouseMove.x, event.mouseMove.y ) )
			{
				float spot = event.mouseMove.x - volumeSliderBg.getPosition().x;
				float perc = spot / volumeSliderBg.getSize().x;
				sf::Listener::setGlobalVolume( perc * 100 );
			}
		}
	}
	else if ( event.type == sf::Event::MouseButtonPressed )
	{
		if ( event.mouseButton.button == sf::Mouse::Left )
		{
			if ( controls.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
			{
				game.changeScenes< ControlsScene >();
			}
			else if ( defaults.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
			{
				game.options = Options();
				sf::Listener::setGlobalVolume( 100 );
			}
			else if ( back.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
			{
				game.changeScenes< MainMenuScene >();
			}
		}
	}
}

void OptionsScene::render( sf::RenderWindow& window )
{
	window.draw( title );
	
	window.draw( volume );
	window.draw( volumeSliderBg );
	volumeSliderFg.setPosition( volumeSliderBg.getPosition().x + ( sf::Listener::getGlobalVolume() / 100 * volumeSliderBg.getSize().x ) - 2, volumeSliderBg.getPosition().y - 10 );
	window.draw( volumeSliderFg );
	
	handleHighlight( window, controls );
	window.draw( controls );
	
	handleHighlight( window, defaults );
	window.draw( defaults );
	
	handleHighlight( window, back );
	window.draw( back );
}
