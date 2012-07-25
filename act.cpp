/*
 * act.cpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#include "act.hpp"
#include "prog/create.hpp"

int act( StrStrMap& args )
{
	srand( time(NULL) ); // init random..

	Create create;

	if( create.shouldRun( args ) )
	{
		if( !create.run( args ) )
		{
			return -1;
		}
	}

	return 0;
}

