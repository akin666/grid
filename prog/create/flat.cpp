/*
 * flat.cpp
 *
 *  Created on: 25.7.2012
 *      Author: akin
 */

#include "flat.hpp"
#include <fstream>
#include <iostream>

namespace create
{

Flat::Flat()
: size( 0 ),
  height( 0 )
{
}

Flat::~Flat()
{
}

void Flat::help() const
{
}

bool Flat::initialize( const StrStrMap& args )
{
	bool error = false;
	std::string style;

	if( !fromData( args , "size" , size ) )
	{
		std::cout << "Error no size specified." << std::endl;
		error = true;
	}
	if( !fromData( args , "min" , height ) )
	{
		std::cout << "Error no min specified." << std::endl;
		error = true;
	}

	// validity Checks!
	if( size < 1 )
	{
		std::cout << "Error validity check failed." << std::endl;
		error = true;
	}

	if( error )
	{
		return false;
	}

	return true;
}

bool Flat::debugOutput() const
{
	std::string filename( "pic.tga" );
	std::ofstream o(filename.c_str(), std::ios::out | std::ios::binary);

	long rlsize = size;
	//Write the header
	o.put(0);
	o.put(0);
	o.put(2);                         // uncompressed RGB
	o.put(0); 	o.put(0);
	o.put(0); 	o.put(0);
	o.put(0);
	o.put(0); 	o.put(0);           // X origin
	o.put(0); 	o.put(0);           // y origin
	o.put((rlsize & 0x00FF));
	o.put((rlsize & 0xFF00) / 256);
	o.put((rlsize & 0x00FF));
	o.put((rlsize & 0xFF00) / 256);
	o.put(32);                        // 24 bit bitmap
	o.put(0);

	float current;
	char val;
	for( long y = 0 ; y < rlsize ; ++y )
	{
		for( long x = 0 ; x < rlsize ; ++x )
		{
			current = getPointAt( x , y );

			val = (char)(current) & 0xFF;

			// BGRA
			o.put( val );
			o.put( val );
			o.put( val );
			o.put( 0xFF );
		}
	}

	//close the file
	o.close();

	return true;
}

float Flat::getPointAt( float x , float y ) const
{
	return height;
}

} // namespace create 
