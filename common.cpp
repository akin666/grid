/*
 * common.cpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#include "common.hpp"


template <>
bool fromData( StrStrMap& map , std::string key , std::string& target )
{
	StrStrMap::iterator iter = map.find( key );
	if( iter != map.end() )
	{
		target = iter->second;
		return true;
	}
	return false;
}

