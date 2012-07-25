/*
 * iperlin.hpp
 *
 *  Created on: 25.7.2012
 *      Author: akin
 */

#ifndef IPERLIN_HPP_
#define IPERLIN_HPP_

#include "noiseinterface.hpp"

namespace create
{

class IPerlin : public NoiseInterface
{
public:
	IPerlin();
	virtual ~IPerlin();

	virtual void help() const;
	virtual bool initialize( const StrStrMap& args );
	virtual bool debugOutput() const;
	virtual float getPointAt( float x , float y ) const;
};

}

#endif // IPERLIN_HPP_ 
