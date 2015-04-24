#ifndef INPUTBINDING_HPP
#define INPUTBINDING_HPP

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>

struct InputBinding
{
	public:
		enum Type
		{
			Keyboard = 0,
			MouseButton = 1,
			JoystickAxis = 2,
			JoystickButton = 3,
		};
		
		InputBinding( sf::Keyboard::Key theKey );
		InputBinding( sf::Mouse::Button theMouseButton );
		InputBinding( int joystickId, sf::Joystick::Axis axis, int dir );
		InputBinding( int joystickId, int button );
		
		struct JoystickAxisData
		{
			int id;
			sf::Joystick::Axis axis;
			int dir;
		};
		struct JoystickButtonData
		{
			int id;
			int button;
		};
		
		Type type;
		union
		{
			sf::Keyboard::Key key;
			sf::Mouse::Button mouseButton;
			JoystickAxisData joystickAxis;
			JoystickButtonData joystickButton;
		};
		
		bool isActive() const;
		bool wasActive() const;
		inline bool justActive() { return isActive() and !wasActive(); }
		
		float getState() const;
		float getLastState() const;
		
		std::string write() const;
		static InputBinding read( const std::string& str );
	
	private:
		float state;
		float prevState;
		
		friend class Options;
		void update();
		
		float check() const;
};

#endif // INPUTBINDING_HPP
