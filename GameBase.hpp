#ifndef GAMEBASE_HPP
#define GAMEBASE_HPP

#include <map>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <type_traits>

#include "Options.hpp"
#include "res/Manager.hpp"
#include "SceneChangeEvent.hpp"

class Game;
class Scene;

// Sub-class it and override initialize() to add scenes, and maybe window.setTitle( "YOUR_GAME" )
class GameBase : public res::Manager
{
	public:
		GameBase( unsigned int theUpdateRate, unsigned int theRenderRate );
		virtual ~GameBase();
		
		void run();
		void close();
		
		template< class SCENE, typename... PARAMS >
		typename std::enable_if< std::is_base_of< Scene, SCENE >::value, void >::type
		changeScenes( const PARAMS&... params );
		template< class SCENE, typename... PARAMS >
		typename std::enable_if< std::is_base_of< Scene, SCENE >::value, void >::type
		changeScenes( const SceneChangeEvent& event, const PARAMS&... params );
		
		unsigned int getUpdateRate() const;
		unsigned int getRenderRate() const;
		
		sf::RenderWindow& getWindow();
		const sf::RenderWindow& getWindow() const;
		
		Options options;
	
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
		
		Game* getGame();
};

#include "GameBase.inl"

#endif // GAMEBASE_HPP
