#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <map>

#include "InputBinding.hpp"

class Options
{
	public:
		Options();
		
		void save( const std::string& filename );
		void load( const std::string& filename );
		
		std::map< std::string, InputBinding > controls;
};

#endif // OPTIONS_HPP
