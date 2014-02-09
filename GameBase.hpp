#ifndef GAMEBASE_HPP
#define GAMEBASE_HPP

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>
#include <type_traits>

#include "ResourceManager.hpp"
#include "SceneChangeEvent.hpp"

class Scene;

// Sub-class it and override initialize() to add scenes, and maybe window.setTitle( "YOUR_GAME" )
class GameBase : public ResourceManager
{
	public:
		GameBase( unsigned int theUpdateRate, unsigned int theRenderRate );
		
		void run();
		void close();
		
		template< class SCENE, typename... PARAMS >
		typename std::enable_if< std::is_base_of< Scene, typename SCENE >::value, void >::type
		void changeScenes( PARAMS&... params );
		
		unsigned int getUpdateRate() const;
		unsigned int getRenderRate() const;
		
		sf::RenderWindow& getWindow();
		const sf::RenderWindow& getWindow() const;
	
	protected:
		sf::RenderWindow window;
		
		virtual void initialize();
		virtual void terminate();
		
		void addScene( const std::string& name, std::shared_ptr< Scene > scene );
	
	private:
		const unsigned int updateRate;
		const unsigned int renderRate;
		bool isRunning;
		
		std::shared_ptr< Scene > currentScene; // I'd use unique, but then moving from next -> current would be an issue
		std::shared_ptr< Scene > nextScene;
		SceneChangeEvent changeEvent;
};

// TODO: Move to an inl
template< class SCENE, typename... PARAMS >
typename std::enable_if< std::is_base_of< Scene, typename SCENE >::value, void >::type
void GameBase::changeScenes( PARAMS&... params )
{
	// Should I use std::forward? I don't know
	nextScene.reset( new SCENE( ( * this ), params... ) );
}

#include "Game.hpp"

#endif // GAMEBASE_HPP
