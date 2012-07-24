/*
 * create.cpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#include "create.hpp"
#include "create/noiseinterface.hpp"
#include "create/perlin.hpp"

using namespace create;

Create::Create()
{
}

Create::~Create()
{
}

bool Create::shouldRun( StrStrMap& args )
{
	return args.find( "create" ) != args.end();
}

bool Create::run( StrStrMap& args )
{
	std::cout << "Running create." << std::endl;

	// Check that all needed things are in args, if not, bail out.
	std::string type;
	NoiseInterface *noiseptr = NULL;

	float bigsize = 0;
	float size = 0;

	bool error = false;
	if( !fromData( args , "bigsize" , bigsize ) )
	{
		std::cout << "Error no bigsize specified." << std::endl;
		error = true;
	}
	if( !fromData( args , "size" , size ) )
	{
		std::cout << "Error no size specified." << std::endl;
		error = true;
	}


	if( !fromData( args , "create" , type ) )
	{
		std::cout << "Warning, no create type specified, defaulting to perlin." << std::endl;
		type = "perlin";
	}

	// Got all params, generate.
	if( type == "perlin" )
	{
		noiseptr = new Perlin;
	}
	else
	{
		std::cout << "Error unknown type specified." << std::endl;
		return false;
	}

	if( noiseptr == NULL )
	{
		return false;
	}
	NoiseInterface& noise = *noiseptr;

	if( !noise.initialize( args ) )
	{
		delete noiseptr;
		return false;
	}

	if( !noise.debugOutput() )
	{
		return false;
	}

	// Open File
	float current;
	long vertexCountSide = bigsize / size;
	long xmax;
	float yspot;
	float xspot;
	for( long y = 0 ; y < vertexCountSide ; ++y )
	{
		xmax = y+1;
		yspot = y * size;
		xspot = -((xmax-1) / 2.0f) * size;
		for( long x = 0 ; x < xmax ; ++x )
		{
			current = noise.getPointAt( xspot + (x * size) , yspot );
//			std::cout << current << " ";
			// output current
		}
//		std::cout << std::endl;
	}
	// close file.

	return true;
}

// factorial? No!
long getNumberOfPointsInTriangle( long size )
{
	return (size*(size+1))/2;
}



