/*
 * create.cpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#include "create.hpp"

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
	float bigsize = 0;
	float size = 0;
	float min = 0;
	float max = 0;
	std::string type;

	int perlinDimensions;

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
	if( !fromData( args , "create" , type ) )
	{
		std::cout << "Warning, no create type specified, defaulting to perlin." << std::endl;
		type = "perlin";
	}
	// validity Checks!

	if( min >= max || bigsize < size )
	{
		std::cout << "Error validity check failed." << std::endl;
		error = true;
	}

	if( error )
	{
		return false;
	}

	// Got all params, generate.
	if( type == "perlin" )
	{
		if( !fromData( args , "dimension" , perlinDimensions ) )
		{
			perlinDimensions = 256;
			std::cout << "Warning! No dimension specified, defaulting to perlin dimension to " << perlinDimensions << "." << std::endl;
		}

		perlin( bigsize , size , min , max , perlinDimensions );
	}
	else
	{
		std::cout << "Error unknown type specified." << std::endl;
		return false;
	}

	return true;
}

// factorial? No!
long getNumberOfPointsInTriangle( long size )
{
	return (size*(size+1))/2;
}

template <class CType>
CType getRandom()
{
	return rand()/((CType)RAND_MAX);
}

template <class CType>
CType getRandom(CType min , CType max)
{
	CType diff = max - min;
	return min + (getRandom<double>() * diff);
}

float getPointFromTriangle( float *map , int npx , int npy , int max )
{
	// TODO
	return 0;
}

float getPoint( float *map , int px , int py , int max )
{
	px %= max; // [0,max]
	py %= max; // [0,max]

	float fy = py / (float)max;
	float fx = px / (float)max;
	// the triangle width shrinks the closer to the top, in sync with height.
	float fxm = fx - fy;
	px = fxm * max;

	// Now PX and PY are mapped to triangle space..

	return getPointFromTriangle( map , px , py , max );
}

float samplePointSquare( float x , float y , float *map , int max )
{
	x = fmod( x , max );
	y = fmod( y , max );

	// a--b
	// |* |
	// c--d
	// get offsets in map
	int ix = x;
	int iy = y;
	int oy = iy*max;
	int oy2= ((iy+1)%max)*max;
	int oa = oy+ix;
	int ob = oy+((ix+1)%max);
	int oc = oy2+ix;
	int od = oy2+((ix+1)%max);

	// calculate the normalized 'weights' for each dimensions
	float fpx = x - ix;
	float fpy = y - iy;

	float fpx2 = 1.0f - fpx;
	float fpy2 = 1.0f - fpx;

	// (( A*xweight + B*xweight2 ) * yweight) + (( C*xweight + D*xweight2 ) * yweight2)
	return (( map[oa] * fpx2 + map[ob] * fpx ) * fpy2) + (( map[oc] * fpx2 + map[od] * fpx ) * fpy);
}

float getNoiseAt( float x , float y , float *map , int dimension , int maxrect )
{
	// how many times? maxrect / max
	int times = maxrect/dimension;

	float val = 0;
	float weight = 0.5f;
	for( int i = 1 ; i < times ; ++i )
	{
		val += samplePointSquare( x * i , y * i , map , dimension ) * weight;
		weight /= 2;
	}
	return val;
}

void Create::perlin( int bsize , int size , float min , float max , int dimension )
{
	std::cout << "Generating perlin BigSize: " << bsize << " Size: " << size <<" Min: " << min << " Max: " << max << " Dimension: " << dimension << std::endl;

	// So first create a randomized cube of 'dimension' size
	int randomSize = dimension * dimension;

	float *minimap = new float[ randomSize ];

	for( int i = 0 ; i < randomSize ; ++i )
	{
		minimap[i] = getRandom<float>(min , max);
	}

	// Now we have tiny random square..
	// We use virtual square to map the perlin noise on to the triangle.
	// By going through each point once, (single pass) and calculating the height of the point.
	// ________X*Y
	// |  /\  |
	// | /  \ |
	// |/____\|
	// 0*0
	//
	// |\
	// | \
	// |  \
	// |___\
	//
	// This way goes the thing into the file.
	// at each point, calculate the X,Y coordinate in the virtual rectangle.
	long vertexCountSide = bsize / size;
	//long vertexCountTotal = getNumberOfPointsInTriangle( vertexCountSide );

	// Open File

	float current;

	//float half = bsize/2.0f;
	long xmax;
	float yspot;
	float xspot;
	for( long y = 0 ; y < vertexCountSide ; ++y )
	{
		xmax = y+1;
		yspot = y * size;
		xspot = -(xmax / 2.0f) * size;
		for( long x = 0 ; x < xmax ; ++x )
		{
			current = getNoiseAt( xspot + (x * size) , yspot , minimap , dimension , bsize );
			std::cout << current << " ";
			// output current
		}
		std::cout << std::endl;
	}
	// close file.
}


