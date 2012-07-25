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
	float size;
	float min;
	float max;
	float extraUpscale;
	int dimension;
	float *map;

	float getNoiseAt( float x , float y ) const;
	float samplePointSquare( float x , float y ) const;
public:
	Perlin();
	virtual ~Perlin();

	virtual void help() const;
	virtual bool initialize( const StrStrMap& args );
	virtual bool debugOutput() const;
	virtual float getPointAt( float x , float y ) const;
};

} // namespace create 
#endif // PERLIN_HPP_ 
