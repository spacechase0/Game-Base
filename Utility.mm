#include "Utility.hpp"

#import <Foundation/Foundation.h>

std::string getWritablePathFor( const std::string& file )
{
	NSString* fileStr = [ NSString stringWithUTF8String: file.c_str() ];
	NSString* path = [ [ NSSearchPathForDirectoriesInDomains( NSDocumentDirectory, NSUserDomainMask, YES ) objectAtIndex: 0 ] stringByAppendingPathComponent: fileStr ];
	return std::string( [ path UTF8String ] );
}