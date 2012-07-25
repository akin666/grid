//============================================================================
// Name        : main.cpp
// Author      : Mikael Korpela
// Version     :
// Copyright   : all rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "common.hpp"
#include "act.hpp"

bool parseArgs( int argc , char *argv[] , StrStrMap& args , bool& help )
{
	// 0 == exec
	help = false;
	for( int i = 1 ; i < argc ; ++i )
	{
		if( argv[i][0] == '-' )
		{
			std::string key( &(argv[i][1]) );

			if( key == "?" )
			{
				help = true;
				continue;
			}

			++i;
			if( argc < i )
			{
				continue;
			}

			args[ key ] = std::string( &(argv[i][0]) );
		}
		else if( argv[i][0] == '?' )
		{
			help = true;
			continue;
		}
	}
	return true;
}

int main( int argc , char *argv[] )
{
	bool help;

	StrStrMap args;
	if( !parseArgs( argc , argv , args , help ) )
	{
		return 0;
	}

	return act( args , help );
}
