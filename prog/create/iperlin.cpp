/*
 * iperlin.cpp
 *
 * improved perlin.. TODO!
 *
 *  Created on: 25.7.2012
 *      Author: akin
 */

#include "iperlin.hpp"
#include <fstream>
#include <iostream>

namespace create
{

IPerlin::IPerlin()
{
}

IPerlin::~IPerlin()
{
}

void IPerlin::help() const
{
}

bool IPerlin::initialize( const StrStrMap& args )
{
	return true;
}

bool IPerlin::debugOutput() const
{
	return true;
}

float IPerlin::getPointAt( float x , float y ) const
{
	return 0;
}

}

