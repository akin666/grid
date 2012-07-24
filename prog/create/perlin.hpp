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
	float extraUpscale;
	int dimension;
	long vertexCountSide;
	float *map;

	float getNoiseAt( float x , float y ) const;
	float samplePointSquare( float x , float y ) const;
public:
	Perlin();
	virtual ~Perlin();

	virtual bool initialize( const StrStrMap& args );
	virtual bool debugOutput() const;
	virtual float getPointAt( float x , float y ) const;
};

} // namespace create 
#endif // PERLIN_HPP_ 
