/*
 * perlin.cpp
 *
 *  Created on: 24.7.2012
 *      Author: akin
 */

#include "perlin.hpp"
#include <fstream>
#include <iostream>

namespace create
{

Perlin::Perlin()
: bigsize( 0 ),
  size( 0 ),
  min( 0 ),
  max( 0 ),
  extraUpscale( 1.0f ),
  dimension( 0 ),
  map( NULL )
{
}

Perlin::~Perlin()
{
	delete[] map;
	map = NULL;
}

bool Perlin::initialize( const StrStrMap& args )
{
	bool error = false;
	std::string style;

	if( !fromData( args , "size" , size ) )
	{
		std::cout << "Error no size specified." << std::endl;
		error = true;
	}
	if( !fromData( args , "min" , min ) )
	{
		std::cout << "Error no min specified." << std::endl;
		error = true;
	}
	if( !fromData( args , "max" , max ) )
	{
		std::cout << "Error no max specified." << std::endl;
		error = true;
	}
	if( !fromData( args , "extraupscale" , extraUpscale ) )
	{
		std::cout << "Warning! No extraupscale specified. defaulting to " << extraUpscale << "." << std::endl;
	}

	// validity Checks!
	if( min >= max || size < 1 )
	{
		std::cout << "Error validity check failed." << std::endl;
		error = true;
	}

	if( !fromData( args , "dimension" , dimension ) )
	{
		dimension = 256;
		std::cout << "Warning! No dimension specified, defaulting to perlin dimension to " << dimension << "." << std::endl;
	}

	if( error )
	{
		return false;
	}

	// Generate random map.
	int randomPlaneSize = dimension * dimension;
	try
	{
		map = new float[ randomPlaneSize ];
	}
	catch( ... )
	{
		return false;
	}
	for( int i = 0 ; i < randomPlaneSize ; ++i )
	{
		map[i] = getRandom<float>(min , max);
	}

	return true;
}

bool Perlin::debugOutput() const
{
	if( map == NULL )
	{
		return false;
	}

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
			current = getNoiseAt( x , y );

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

float Perlin::getPointAt( float x , float y ) const
{
	return getNoiseAt( x , y );
}

float Perlin::samplePointSquare( float x , float y ) const
{
	/*
	x = fmod( x , max + 1 );
	y = fmod( y , max + 1 );
	int x1 = x;
	int y1 = y;
	int x2 = fmod( x + 1 , max + 1 );
	int y2 = fmod( y + 1 , max + 1 );

	int oa = y1*max + x1;
	int ob = y1*max + x2;
	int oc = y2*max + x1;
	int od = y2*max + x2;

	// calculate the normalized 'weights' for each dimensions
	float fpx = x - x1;
	float fpy = y - y1;

	float fpx2 = 1.0f - fpx;
	float fpy2 = 1.0f - fpy;

	double xcol = map[oa] * fpx2 + map[ob] * fpx;
	double xcol2 = map[oc] * fpx2 + map[od] * fpx;

	// (( A*xweight + B*xweight2 ) * yweight) + (( C*xweight + D*xweight2 ) * yweight2)
	return ( xcol * fpy2) + (xcol2 * fpy);
	*/
	x = fmod( x , dimension );
	y = fmod( y , dimension );

	// a--b
	// |* |
	// c--d
	// get offsets in map
	int ix = x;
	int iy = y;
	int oy = iy*dimension;
	int oy2= ((iy+1)%dimension)*dimension;
	int oa = oy+ix;
	int ob = oy+((ix+1)%dimension);
	int oc = oy2+ix;
	int od = oy2+((ix+1)%dimension);

	// calculate the normalized 'weights' for each dimensions
	double fpx = x - ix;
	double fpy = y - iy;

	double fpx2 = 1.0f - fpx;
	double fpy2 = 1.0f - fpy;
	double xx1 = map[oa] * fpx2 + map[ob] * fpx;
	double xx2 = map[oc] * fpx2 + map[od] * fpx;

	// (( A*xweight + B*xweight2 ) * yweight) + (( C*xweight + D*xweight2 ) * yweight2)
	return (xx1 * fpy2) + (xx2 * fpy);
}

float Perlin::getNoiseAt( float x , float y ) const
{
//	return samplePointSquare( x*0.2 , y*0.2 , map , dimension );
	float upscale = (dimension / (float)size)/extraUpscale;
	float val = 0;
	float weight = 0.5f;
	while( upscale < 1.0f )
	{
		val += samplePointSquare( x * upscale , y * upscale ) * weight;
		upscale *= 2.0f;
		weight /= 1.5f;
	}
	return val;
}

} // namespace create 
