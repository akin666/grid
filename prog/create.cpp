/*
 * create.cpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#include "create.hpp"
#include "create/noiseinterface.hpp"
#include "create/perlin.hpp"
#include "create/flat.hpp"
#include <fstream>
#include <iostream>

#define CREATE_STYLE_NONE			0x0000
#define CREATE_STYLE_TRIANGLE		0x0001
#define CREATE_STYLE_RECTANGLE		0x0002

#define CREATE_STYLE_DEFAULT		CREATE_STYLE_NONE

using namespace create;

Create::Create()
{
}

Create::~Create()
{
}

void Create::help( const StrStrMap& args ) const
{
	std::cout << "Create help." << std::endl;
}

bool Create::shouldRun( const StrStrMap& args ) const
{
	return args.find( "create" ) != args.end();
}

bool Create::run( const StrStrMap& args )
{
	// Check that all needed things are in args, if not, bail out.
	std::string type;
	NoiseInterface *noiseptr = NULL;

	std::string outputFile;
	bool debug = false;
	float size = 0;
	int style = CREATE_STYLE_DEFAULT;

	bool error = false;
	if( !fromData( args , "create-out" , outputFile ) )
	{
		std::cout << "Error no create output ('create-out') specified." << std::endl;
		error = true;
	}
	if( !fromData( args , "size" , size ) )
	{
		std::cout << "Error no size specified." << std::endl;
		error = true;
	}
	if( error )
	{
		return false;
	}

	// style
	std::string tmpstr = "triangle";
	if( !fromData( args , "style" , tmpstr ) )
	{
		tmpstr = "triangle";
		std::cout << "Warning! No style specified, defaulting to "<< tmpstr <<"." << std::endl;
	}
	if( tmpstr == "triangle" )
	{
		style |= CREATE_STYLE_TRIANGLE;
	}
	else if( tmpstr == "rectangle" )
	{
		style |= CREATE_STYLE_RECTANGLE;
	}

	// debug
	if( fromData( args , "debug" , tmpstr ) )
	{
		debug = false;
		if( tmpstr == "true" )
		{
			debug = true;
		}
		std::cout << "Warning! debug set to '"<< (debug?"true":"false") <<"'." << std::endl;
	}

	// create
	if( !fromData( args , "create" , type ) )
	{
		std::cout << "Warning, no create type specified, defaulting to perlin." << std::endl;
		type = "perlin";
	}

	// Create noise function.
	if( type == "perlin" )
	{
		noiseptr = new Perlin;
	}
	else if( type == "flat" )
	{
		noiseptr = new Flat;
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

	if( debug )
	{
		if( !noise.debugOutput() )
		{
			std::cout << "Error while debug output." << std::endl;
			delete noiseptr;
			return false;
		}
	}

	// Open File
	std::ofstream output(outputFile.c_str(), std::ios::out | std::ios::binary);
	if( !output.is_open() )
	{
		std::cout << "Error output opening output '" << outputFile << "'." << std::endl;
		delete noiseptr;
		return false;
	}

	float current;
	long xmax;
	float yspot;
	float xspot;

	switch( style )
	{
		case CREATE_STYLE_TRIANGLE :
		{
			for( long y = 0 ; y < size ; ++y )
			{
				xmax = y+1;
				yspot = y * size;
				xspot = -((xmax-1) / 2.0f);
				for( long x = 0 ; x < xmax ; ++x )
				{
					current = noise.getPointAt( xspot + x , yspot );
					output.put( current );
				}
			}
			break;
		}
		case CREATE_STYLE_RECTANGLE :
		{
			for( long y = 0 ; y < size ; ++y )
			{
				yspot = y * size;
				for( long x = 0 ; x < size ; ++x )
				{
					current = noise.getPointAt( x , yspot );
					output.put( current );
				}
			}
			break;
		}
		default:
			std::cout << "No output style specified." << std::endl;
			break;
	}
	// close file.
	output.close();

	delete noiseptr;
	return true;
}

// factorial? No!
long getNumberOfPointsInTriangle( long size )
{
	return (size*(size+1))/2;
}



