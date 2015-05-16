#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include <SFML/Graphics/Text.hpp>

#include "res/Reference.hpp"
#include "Scene.hpp"

class MainMenuScene : public Scene
{
	public:
		MainMenuScene( Game& theGame, const SceneChangeEvent& event );
		
		virtual void update();
		virtual void update( const sf::Event& event );
		virtual void render( sf::RenderWindow& window );
	
	private:
		res::Reference fontRes;
		sf::Text title;
		sf::Text play;
		sf::Text options;
		sf::Text quit;
};

#endif // MAINMENUSCENE_HPP
