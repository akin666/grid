/*
 * perlin.hpp
 *
 *  Created on: 24.7.2012
 *      Author: akin
 */

#ifndef PERLIN_HPP_
#define PERLIN_HPP_

#include "noiseinterface.hpp"

namespace create
{

class Perlin : public NoiseInterface
{
protected:
	float bigsize;
	float size;
	float min;
	float max;
	int dimension;
	long vertexCountSide;
	float *map;

	float getNoiseAt( float x , float y );
	float samplePointSquare( float x , float y );
public:
	Perlin();
	virtual ~Perlin();

	virtual bool initialize( StrStrMap& args );
	virtual bool debugOutput();
	virtual float getPointAt( float x , float y );
};

} // namespace create 
#endif // PERLIN_HPP_ 
