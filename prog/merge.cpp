/*
 * merge.cpp
 *
 *  Created on: 25.7.2012
 *      Author: akin
 */

#include "merge.hpp"

Merge::Merge()
{
}

Merge::~Merge()
{
}

void Merge::help( const StrStrMap& args ) const
{
	std::cout << "Merge help." << std::endl;
}

bool Merge::shouldRun( const StrStrMap& args ) const
{
	return false;
}

bool Merge::run( const StrStrMap& args )
{
	return false;
}


