#include "scenes/ControlsScene.hpp"

#include <SFML/Audio/Listener.hpp>
#include <util/String.hpp>

#include "Game.hpp"
#include "InputBinding.hpp"
#include "scenes/OptionsScene.hpp"
#include "Utility.hpp"

namespace
{
	std::string stringify( const InputBinding& input )
	{
		switch ( input.type )
		{
			case InputBinding::Keyboard: return "Key " + keyToString( input.key );
			case InputBinding::MouseButton:
				switch ( input.mouseButton )
				{
					case sf::Mouse::Left: return "Left Mouse Button";
					case sf::Mouse::Right: return "Right Mouse Button";
					case sf::Mouse::Middle: return "Middle Mouse Button";
					case sf::Mouse::XButton1: return "Extra Mouse Button 1";
					case sf::Mouse::XButton2: return "Extra Mouse Button 2";
					default: return "??? Mouse Button";
				}
				
			case InputBinding::JoystickAxis:
				{
					std::string data = "Joystick " + util::toString( input.joystickAxis.id ) + ", ";
					data += ( input.joystickAxis.dir > 0 ) ? "+" : "-";
					switch ( input.joystickAxis.axis )
					{
						#define jb(a) case sf::Joystick::  a : data += #a; break;
						jb( X );
						jb( Y );
						jb( Z );
						jb( R );
						jb( U );
						jb( V );
						jb( PovX );
						jb( PovY );
						#undef jb
					}
					data += " Axis";
					return data;
				}
				
			case InputBinding::JoystickButton: return "Joystick " + util::toString( input.joystickButton.id ) + ", Button " + util::toString( input.joystickButton.button );
		}
		
		return "???";
	}
}

ControlsScene::ControlsScene( Game& theGame, SceneChangeEvent& event )
   : Scene::Scene( theGame ),
     font( * theGame.getFont( "res/dejavu/ttf/DejaVuSans.ttf" ) )
{
	title.setString( "Controls" );
	title.setFont( font );
	title.setCharacterSize( 45 );
	title.setColor( sf::Color::White );
	title.setPosition( ( game.getWindow().getSize().x - title.getLocalBounds().width ) / 2, 35 );
	
	back = title;
	back.setString( "Back" );
	back.setCharacterSize( 30 );
	back.setPosition( ( game.getWindow().getSize().x - back.getLocalBounds().width ) / 2,
	                  game.getWindow().getSize().y - back.getLocalBounds().height - 25 );
	
	updateControls();
	
	changeDialogBack.setSize( sf::Vector2f( 320, 240 ) );
	changeDialogBack.setFillColor( sf::Color( 192, 192, 192 ) );
	changeDialogBack.setPosition( ( game.getWindow().getSize().x - changeDialogBack.getSize().x ) / 2,
	                              ( game.getWindow().getSize().y - changeDialogBack.getSize().y ) / 2 );
	
	changeDialogText = back;
	changeDialogText.setString( "You are changing the\nbinding for a control. Wait\nfor the timer to expire \nto keep the current setting." );
	changeDialogText.setPosition( changeDialogBack.getPosition().x + 20, changeDialogBack.getPosition().y + 20 );
	changeDialogText.setCharacterSize( 20 );
	
	changeDialogName = changeDialogText;
	changeDialogName.move( 0, changeDialogText.getLocalBounds().height + 35 );
	changeDialogName.setCharacterSize( 15 );
	
	changeDialogCurr = changeDialogName;
	changeDialogCurr.move( 100, 0 );
	
	changeDialogTimer = changeDialogText;
}

void ControlsScene::update()
{
}

void ControlsScene::update( const sf::Event& event )
{
	if ( changing )
	{
		if ( event.type == sf::Event::MouseButtonPressed )
		{
			( * changing->first ) = InputBinding( event.mouseButton.button );
			updateControls();
			changing = NULL;
			return;
		}
		else if ( event.type == sf::Event::KeyPressed )
		{
			( * changing->first ) = InputBinding( event.key.code );
			updateControls();
			changing = NULL;
			return;
		}
		else if ( event.type == sf::Event::JoystickMoved )
		{
			if ( event.joystickMove.position == 0 || std::abs( event.joystickMove.position ) < 50 ) return;
			( * changing->first ) = InputBinding( event.joystickMove.joystickId, event.joystickMove.axis, static_cast< int >( event.joystickMove.position / std::abs( event.joystickMove.position ) ) );
			updateControls();
			changing = NULL;
			return;
		}
		else if ( event.type == sf::Event::JoystickButtonPressed )
		{
			( * changing->first ) = InputBinding( event.joystickButton.joystickId, event.joystickButton.button );
			updateControls();
			changing = NULL;
			return;
		}
	}
	
	if ( event.type == sf::Event::MouseButtonPressed )
	{
		if ( event.mouseButton.button == sf::Mouse::Left )
		{
			if ( back.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
			{
				game.changeScenes< OptionsScene >();
			}
			else
			{
				for ( auto it = controls.begin(); it != controls.end(); ++it )
				{
					if ( it->second.text.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
					{
						changing = &( * it );
						changeTimer.restart();
						
						changeDialogName.setString( it->second.title.getString() );
						changeDialogCurr.setString( it->second.text.getString() );
					}
				}
			}
		}
	}
}

void ControlsScene::render( sf::RenderWindow& window )
{
	window.draw( title );
	
	handleHighlight( window, back );
	window.draw( back );
	
	for ( auto it = controls.begin(); it != controls.end(); ++it )
	{
		window.draw( it->second.title );
		
		handleHighlight( window, it->second.text );
		window.draw( it->second.text );
	}
	
	if ( changing )
	{
		window.draw( changeDialogBack );
		window.draw( changeDialogText );
		
		window.draw( changeDialogName );
		window.draw( changeDialogCurr );
		
		changeDialogTimer.setString( util::toString< int >( 5.999 - changeTimer.getElapsedTime().asSeconds() ) );
		changeDialogTimer.setPosition( ( window.getSize().x - changeDialogTimer.getGlobalBounds().width ) / 2,
		                               changeDialogBack.getPosition().y + changeDialogBack.getSize().y - changeDialogTimer.getGlobalBounds().height - 20 );
		window.draw( changeDialogTimer );
		
		if ( changeTimer.getElapsedTime().asSeconds() >= 5 )
		{
			changing = NULL;
		}
	}
}

void ControlsScene::updateControls()
{
	controls.clear();
	
	int y = 100;
	for ( auto it = game.options.controls.begin(); it != game.options.controls.end(); ++it )
	{
		InputBinding& input = it->second;
		
		InputText display;
		display.title = back;
		display.title.setString( it->first );
		display.title.setPosition( 25, y );
		
		display.text = display.title;
		display.text.setString( stringify( input ) );
		display.text.move( 150, 0 );
		
		controls.insert( std::make_pair( &input, display ) );
		
		y += 35;
	}
}
