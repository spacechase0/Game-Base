////////////////////////////////////////////////////////////
//
// Game Base
// Copyright (C) 2012 Chase Warrington (staff@spacechase0.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

#include "SceneChangeEvent.h"

class Scene;

class Game
{
	public:
		Game();
		
		void run();
		void close();
		
		void changeScenes( const std::string& name, SceneChangeEvent event = SceneChangeEvent() );
		std::shared_ptr< Scene > getScene( const std::string& name );
		
		static const int UPDATE_RATE;
		static const int RENDER_RATE;
	
	private:
		sf::RenderWindow window;
		bool isRunning;
		
		void initialize();
		void terminate();
		
		std::map< std::string, std::shared_ptr< Scene > > scenes;
		std::string currentScene;
		std::string nextScene;
		SceneChangeEvent changeEvent;
		
		void addScene( const std::string& name, std::shared_ptr< Scene > scene );
};

#endif // GAME_H
