#ifndef CONTROLSSCENE_HPP
#define CONTROLSSCENE_HPP

#include <map>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

#include "Scene.hpp"

class InputBinding;

class ControlsScene : public Scene
{
	public:
		ControlsScene( Game& theGame, SceneChangeEvent& event );
		
		virtual void update();
		virtual void update( const sf::Event& event );
		virtual void render( sf::RenderWindow& window );
	
	private:
		const sf::Font& font;
		sf::Text title;
		
		struct InputText
		{
			sf::Text title;
			sf::Text text;
		};
		std::size_t currPage;
		typedef std::vector< std::pair< InputBinding* const, InputText > > InputPage;
		std::vector< InputPage > controls;
		void updateControls();
		
		std::pair< InputBinding* const, InputText >* changing = NULL;
		sf::Clock changeTimer;
		sf::RectangleShape changeDialogBack;
		sf::Text changeDialogText;
		sf::Text changeDialogName;
		sf::Text changeDialogCurr;
		sf::Text changeDialogTimer;
		
		sf::Text back;
		sf::Text pageLeft;
		sf::Text page;
		sf::Text pageRight;
};

#endif // CONTROLSSCENE_HPP
