#include "scenes/ControlsScene.hpp"

#include <cmath>
#include <SFML/Audio/Listener.hpp>
#include <SFML/Window/Event.hpp>
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
			case InputBinding::Keyboard: return "'" + keyToString( input.key ) + "' Key";
			case InputBinding::MouseButton:
				switch ( input.mouseButton )
				{
					case sf::Mouse::Left: return "Left Mouse Button";
					case sf::Mouse::Right: return "Right Mouse Button";
					case sf::Mouse::Middle: return "Middle Mouse Button";
					case sf::Mouse::XButton1: return "Extra (1) Mouse Button";
					case sf::Mouse::XButton2: return "Extra (2) Mouse Button";
					default: return "??? Mouse Button";
				}
				
			case InputBinding::JoystickAxis:
				{
					std::string data = ( input.joystickAxis.dir > 0 ) ? "+" : "-";
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
					data += " Axis on Joy " + util::toString( input.joystickAxis.id );
					return data;
				}
				
			case InputBinding::JoystickButton: return "Button " + util::toString( input.joystickButton.button ) + " on Joy " + util::toString( input.joystickButton.id );
		}
		
		return "???";
	}
}

ControlsScene::ControlsScene( Game& theGame, const SceneChangeEvent& event )
   : Scene::Scene( theGame ),
     font( * theGame.getFont( "res/ken_fonts/kenpixel.ttf" ) ),
     currPage( 0 )
{
	title.setString( "Controls" );
	title.setFont( font );
	title.setCharacterSize( 45 );
	title.setColor( sf::Color::White );
	title.setPosition( ( game.getWindow().getSize().x - title.getLocalBounds().width ) / 2, 35 );
	
	back = title;
	back.setString( "Back" );
	back.setCharacterSize( 30 );
	back.setPosition( 25, game.getWindow().getSize().y - back.getLocalBounds().height - 25 );
	
	pageRight = title;
	pageRight.setCharacterSize( 30 );
	pageRight.setString( ">" );
	pageRight.setOrigin( pageRight.getGlobalBounds().width, 0 );
	pageRight.setPosition( game.getWindow().getSize().x - 25, game.getWindow().getSize().y - pageRight.getLocalBounds().height - 25 );
	
	page = pageRight;
	page.setString( "1/1" );
	page.move( -pageRight.getGlobalBounds().width - 15, 0 );
	
	pageLeft = page;
	pageLeft.setString( "<" );
	pageLeft.setOrigin( pageLeft.getGlobalBounds().width, 0 );
	pageLeft.move( -page.getGlobalBounds().width - 15, 0 );
	
	page.move( -page.getGlobalBounds().width / 2, 0 );
	page.setOrigin( page.getGlobalBounds().width / 2, 0 );
	
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
	if ( changing and newControlEvents.size() > 0 )
	{
		for ( std::size_t i = 0; i < newControlEvents.size(); ++i )
		{
			sf::Event event = newControlEvents[ i ];
			if ( event.type == sf::Event::MouseButtonPressed )
			{
				( * changing->first ) = InputBinding( event.mouseButton.button );
			}
			else if ( event.type == sf::Event::KeyPressed )
			{
				( * changing->first ) = InputBinding( event.key.code );
			}
			else if ( event.type == sf::Event::JoystickMoved )
			{
				( * changing->first ) = InputBinding( event.joystickMove.joystickId, event.joystickMove.axis, static_cast< int >( event.joystickMove.position / std::abs( event.joystickMove.position ) ) );
			}
			else if ( event.type == sf::Event::JoystickButtonPressed )
			{
				( * changing->first ) = InputBinding( event.joystickButton.joystickId, event.joystickButton.button );
			}
		}
		std::size_t index = 0;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) or sf::Keyboard::isKeyPressed( sf::Keyboard::RShift ) ) ++index;
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) or sf::Keyboard::isKeyPressed( sf::Keyboard::RControl ) ) ++index;
		if ( index < newControlEvents.size() )
		{
			sf::Event event = newControlEvents[ index ];
			if ( event.type == sf::Event::MouseButtonPressed )
			{
				( * changing->first ) = InputBinding( event.mouseButton.button );
			}
			else if ( event.type == sf::Event::KeyPressed )
			{
				( * changing->first ) = InputBinding( event.key.code );
			}
			else if ( event.type == sf::Event::JoystickMoved )
			{
				( * changing->first ) = InputBinding( event.joystickMove.joystickId, event.joystickMove.axis, static_cast< int >( event.joystickMove.position / std::abs( event.joystickMove.position ) ) );
			}
			else if ( event.type == sf::Event::JoystickButtonPressed )
			{
				( * changing->first ) = InputBinding( event.joystickButton.joystickId, event.joystickButton.button );
			}
		
			updateControls();
			changing = NULL;
		}
		newControlEvents.clear();
	}
}

void ControlsScene::update( const sf::Event& event )
{
	if ( changing )
	{
		if ( event.type == sf::Event::MouseButtonPressed    or event.type == sf::Event::KeyPressed or 
		     event.type == sf::Event::JoystickButtonPressed or event.type == sf::Event::JoystickMoved )
		{
			if ( event.type == sf::Event::JoystickMoved and ( event.joystickMove.position == 0 or std::abs( event.joystickMove.position ) < 50 ) )
			{
				return;
			}
			
			newControlEvents.push_back( event );
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
			else if ( pageLeft.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
			{
				if ( currPage > 0 )
				{
					--currPage;
				}
			}
			else if ( pageRight.getGlobalBounds().contains( event.mouseButton.x, event.mouseButton.y ) )
			{
				if ( currPage < controls.size() - 1 )
				{
					++currPage;
				}
			}
			else
			{
				for ( auto it = controls[ currPage ].begin(); it != controls[ currPage ].end(); ++it )
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
	
	for ( auto it = controls[ currPage ].begin(); it != controls[ currPage ].end(); ++it )
	{
		window.draw( it->second.title );
		
		handleHighlight( window, it->second.text );
		window.draw( it->second.text );
	}
	
	handleHighlight( window, pageLeft );
	handleHighlight( window, pageRight );
	page.setString( util::toString( currPage + 1 ) + "/" + util::toString( controls.size() ) );
	page.setOrigin( page.getGlobalBounds().width / 2, 0 );
	window.draw( pageLeft );
	window.draw( page );
	window.draw( pageRight );
	
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
	std::vector< std::string > controlList = game.options.getControlList();
	InputPage currPage;
	for ( auto it = controlList.begin(); it != controlList.end(); ++it )
	{
		InputBinding& input = game.options.getInputBinding( * it );
		
		InputText display;
		display.title = back;
		display.title.setString( * it );
		display.title.setPosition( 25, y );
		
		display.text = display.title;
		display.text.setString( stringify( input ) );
		display.text.setPosition( game.getWindow().getSize().x - 25, display.text.getPosition().y );
		display.text.setOrigin( display.text.getGlobalBounds().width, 0 );
		
		currPage.push_back( std::make_pair( &input, display ) );
		
		y += 35;
		
		if ( y + 35 > back.getPosition().y )
		{
			controls.push_back( currPage );
			currPage.clear();
			y = 100;
		}
	}
	
	if ( currPage.size() > 0 )
	{
		controls.push_back( currPage );
	}
}
