/*
 * flat.hpp
 *
 *  Created on: 25.7.2012
 *      Author: akin
 */

#ifndef FLAT_HPP_
#define FLAT_HPP_

#include "noiseinterface.hpp"

namespace create
{

class Flat: public NoiseInterface
{
protected:
	float size;
	float height;
public:
	Flat();
	virtual ~Flat();

	virtual void help() const;
	virtual bool initialize( const StrStrMap& args );
	virtual bool debugOutput() const;
	virtual float getPointAt( float x , float y ) const;
};

} // namespace create 
#endif // FLAT_HPP_ 
