#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include <SFML/Graphics/Text.hpp>

#include "Scene.hpp"

class MainMenuScene : public Scene
{
	public:
		MainMenuScene( Game& theGame, SceneChangeEvent& event );
		
		virtual void update();
		virtual void update( const sf::Event& event );
		virtual void render( sf::RenderWindow& window );
	
	private:
		const sf::Font& font;
		sf::Text title;
		sf::Text play;
		sf::Text options;
		sf::Text quit;
};

#endif // MAINMENUSCENE_HPP
