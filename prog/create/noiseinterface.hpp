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

	virtual bool initialize( StrStrMap& args ) = 0;
	virtual bool debugOutput() = 0;
	virtual float getPointAt( float x , float y ) = 0;
};

} // namespace create 
#endif // NOISEINTERFACE_HPP_
