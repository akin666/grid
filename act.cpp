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

int act( StrStrMap& args , bool help )
{
	srand( time(NULL) ); // init random..
	std::string strtmp;

	Create create;
	Erode erode;
	Merge merge;

	if( create.shouldRun( args ) )
	{
		if( help )
		{
			create.help( args );
		}
		else if( !create.run( args ) )
		{
			return -1;
		}
	}
	if( merge.shouldRun( args ) )
	{
		if( help )
		{
			merge.help( args );
		}
		else if( !merge.run( args ) )
		{
			return -1;
		}
	}
	if( erode.shouldRun( args ) )
	{
		if( help )
		{
			erode.help( args );
		}
		else if( !erode.run( args ) )
		{
			return -1;
		}
	}

	return 0;
}

