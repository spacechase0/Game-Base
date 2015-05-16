#include "res/Types.hpp"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <util/Logger.hpp>

#include "res/Data.hpp"
#include "res/Manager.hpp"
#include "res/ReloadNotify.hpp"

namespace
{
	template< class RES >
	RES& getResource( res::Reference ref );
	
	template< class RES >
	class ResourceHolder : public res::ReloadNotify
	{
		public:
			virtual void onLoad( const res::Data& data )
			{
				const std::string& str = data.getData();
				if ( !res.loadFromMemory( str.data(), str.size() ) )
				{
					#define STR(x) #x
					data.getManager().log( "Failed to load '%s' as %s.\n", data.getName(), STR( RES ) );
					#undef STR
				}
			}
		
		private:
			friend RES& getResource< RES >( res::Reference ref );
			
			RES res;
	};
	
	template< typename RES >
	RES& getResource( res::Reference ref )
	{
		res::Data& data = ( * ref );
		res::ReloadNotify* notifier = data.notifierForType( typeid( ResourceHolder< RES > ) );
		if ( !notifier )
		{
			notifier = new ResourceHolder< RES >();
			data.notify( notifier );
		}
		
		notifier->onLoad( data );
		return dynamic_cast< ResourceHolder< RES >* >( notifier )->res;
	}
}

namespace res
{
	sf::Font& font( Reference ref )
	{
		return getResource< sf::Font >( ref );
	}
	
	sf::SoundBuffer& soundBuffer( Reference ref )
	{
		return getResource< sf::SoundBuffer >( ref );
	}
	
	sf::Texture& texture( Reference ref )
	{
		return getResource< sf::Texture >( ref );
	}
	
}
