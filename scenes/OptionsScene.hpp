#ifndef OPTIONSSCENE_HPP
#define OPTIONSSCENE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Scene.hpp"

class OptionsScene : public Scene
{
	public:
		OptionsScene( Game& theGame, const SceneChangeEvent& event );
		
		virtual void update();
		virtual void update( const sf::Event& event );
		virtual void render( sf::RenderWindow& window );
	
	private:
		const sf::Font& font;
		sf::Text title;
		
		sf::Text volume;
		sf::RectangleShape volumeSliderBg;
		sf::RectangleShape volumeSliderFg;
		
		sf::Text controls;
		
		sf::Text defaults;
		sf::Text back;
};

#endif // OPTIONSSCENE_HPP
