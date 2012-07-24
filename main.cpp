//============================================================================
// Name        : main.cpp
// Author      : Mikael Korpela
// Version     :
// Copyright   : all rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "common.hpp"
#include "prog/act.hpp"

void help()
{
	std::cout << "plane help:" << std::endl;
}

bool parseArgs( int argc , char *argv[] , StrStrMap& args )
{
	// 0 == exec
	for( int i = 1 ; i < argc ; ++i )
	{
		if( argv[i][0] == '-' )
		{
			std::string key( &(argv[i][1]) );

			if( key == "?" )
			{
				help();
				return false;
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
			help();
			return false;
		}
	}
	return true;
}

int main( int argc , char *argv[] )
{
	help();

	StrStrMap args;
	if( !parseArgs( argc , argv , args ) )
	{
		return 0;
	}

	return act( args );
}
