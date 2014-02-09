#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "Scene.hpp"

class GameScene : public Scene
{
	public:
		GameScene( Game& theGame );
		
		virtual void update();
		virtual void update( const sf::Event& event );
		virtual void render( sf::RenderWindow& window );
};

#endif // GAMESCENE_HPP
