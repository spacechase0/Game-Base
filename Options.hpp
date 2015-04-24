#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <vector>

#include "InputBinding.hpp"

class Options
{
	public:
		Options();
		
		void save( const std::string& filename );
		void load( const std::string& filename );
		
		const InputBinding& getInputBinding( const std::string& str ) const;
		InputBinding& getInputBinding( const std::string& str );
		std::vector< std::string > getControlList() const;
		
		void updateInput();
	
	private:
		std::vector< std::pair< std::string, InputBinding > > controls;
};

#endif // OPTIONS_HPP
