#include "res/Reference.hpp"

#include "res/Data.hpp"

namespace res
{
	Reference::Reference( const Reference& other )
	   : res( other.res )
	{
		res->refs++;
	}
	
	Reference::Reference( Reference&& other )
	{
		// Is this the right way to do a move constructor?
		// I know NULL technically doesn't leave the other one 'valid', but
		// what other option is there?
		res = other.res;
		other.res = NULL;
	}
	
	Reference::~Reference()
	{
		res->refs--;
	}
	
	Reference& Reference::operator = ( const Reference& other )
	{
		res->refs--;
		
		res = other.res;
		res->refs++;
		
		return ( * this );
	}
	
	Data* Reference::operator -> ()
	{
		return res;
	}
	
	const Data* Reference::operator -> () const
	{
		return res;
	}
	
	Reference::operator Data* ()
	{
		return res;
	}
	
	Reference::operator const Data* () const
	{
		return res;
	}
	 
	Reference::Reference( Data* theRes )
	   : res( theRes )
	{
		res->refs++;
	}
}
