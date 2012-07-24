/*
 * create.hpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#ifndef CREATE_HPP_
#define CREATE_HPP_

#include "interface.hpp"

class Create
{
public:
	void perlin( float bsize , float size , float min , float max , int dimension );
public:
	Create();
	virtual ~Create();

	virtual bool shouldRun( StrStrMap& args );
	virtual bool run( StrStrMap& args );
};

#endif // CREATE_HPP_ 
