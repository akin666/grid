/*
 * act.cpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#include "act.hpp"
#include "prog/create.hpp"
#include "prog/merge.hpp"
#include "prog/erode.hpp"

int act( StrStrMap& args )
{
	srand( time(NULL) ); // init random..

	Create create;
	Erode erode;
	Merge merge;

	if( create.shouldRun( args ) )
	{
		if( !create.run( args ) )
		{
			return -1;
		}
	}
	if( merge.shouldRun( args ) )
	{
		if( !merge.run( args ) )
		{
			return -1;
		}
	}
	if( erode.shouldRun( args ) )
	{
		if( !erode.run( args ) )
		{
			return -1;
		}
	}

	return 0;
}

