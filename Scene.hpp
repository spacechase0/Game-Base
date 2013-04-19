////////////////////////////////////////////////////////////
//
// Game Base
// Copyright (C) 2013 Chase Warrington (staff@spacechase0.com)
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

#ifndef SCENE_HPP
#define SCENE_HPP

namespace sf
{
	class RenderWindow;
	class Event;
}
class Game;
class SceneChangeEvent;

class Scene
{
	public:
		Scene( Game& theGame );
		virtual ~Scene();
		
		virtual void initialize( SceneChangeEvent& event ) = 0;
		virtual void terminate() = 0;
		
		virtual void update() = 0;
		virtual void update( const sf::Event& event ) = 0;
		virtual void render( sf::RenderWindow& window ) = 0;
	
	protected:
		Game& game;
};

#endif // SCENE_HPP
