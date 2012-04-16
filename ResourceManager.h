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

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <SFML/System/Mutex.hpp>
#include <string>

namespace sf
{
	class Texture;
	class SoundBuffer;
	class Font;
}

class ResourceManager
{
	public:
		static bool loadTexture( const std::string& filename );
		static bool loadSoundBuffer( const std::string& filename );
		static bool loadFont( const std::string& filename );
		
		static std::shared_ptr< sf::Texture > getTexture( const std::string& filename, bool loadIfNotLoaded = true );
		static std::shared_ptr< sf::SoundBuffer > getSoundBuffer( const std::string& filename, bool loadIfNotLoaded = true );
		static std::shared_ptr< sf::Font > getFont( const std::string& filename, bool loadIfNotLoaded = true );
		
		static void unloadTexture( const std::string& filename );
		static void unloadSoundBuffer( const std::string& filename );
		static void unloadFont( const std::string& filename );
		static void unloadAll();
	
	private:
		~ResourceManager() = delete;
		
		static sf::Mutex texMutex;
		static sf::Mutex soundMutex;
		static sf::Mutex fontMutex;
		
		static std::map< std::string, std::shared_ptr< sf::Texture > > textures;
		static std::map< std::string, std::shared_ptr< sf::SoundBuffer > > soundBuffers;
		static std::map< std::string, std::shared_ptr< sf::Font > > fonts;
};

#endif // RESOURCEMANAGER_H
