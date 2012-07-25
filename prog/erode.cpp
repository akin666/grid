/*
 * erode.cpp
 *
 *  Created on: 25.7.2012
 *      Author: akin
 */

#include "erode.hpp"

Erode::Erode()
{
}

Erode::~Erode()
{
}

void Erode::help( const StrStrMap& args ) const
{
	std::cout << "Erode help." << std::endl;
}

bool Erode::shouldRun( const StrStrMap& args ) const
{
	return false;
}

bool Erode::run( const StrStrMap& args )
{
	return false;
}
