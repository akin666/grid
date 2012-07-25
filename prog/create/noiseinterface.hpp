/*
 * NoiseInterface.hpp
 *
 *  Created on: 24.7.2012
 *      Author: akin
 */

#ifndef NOISEINTERFACE_HPP_
#define NOISEINTERFACE_HPP_

#include "../../common.hpp"

namespace create
{

class NoiseInterface
{
public:
	virtual ~NoiseInterface() {}

	virtual void help() const = 0;
	virtual bool initialize( const StrStrMap& args ) = 0;
	virtual bool debugOutput() const = 0;
	virtual float getPointAt( float x , float y ) const = 0;
};

} // namespace create 
#endif // NOISEINTERFACE_HPP_
