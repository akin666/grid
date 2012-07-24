/*
 * common.hpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_


#include <iostream>
#include <map>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

typedef std::map<std::string , std::string> StrStrMap;

template <class CType>
CType getRandom()
{
	return rand()/((CType)RAND_MAX);
}

template <class CType>
CType getRandom(CType min , CType max)
{
	CType diff = max - min;
	return min + (getRandom<double>() * diff);
}

template<typename T, typename F>
T to_ot( const F from )
{
	std::stringstream temp;
	temp << from;
	T to = T();
	temp >> to;
	return to;
}

template <class CType>
bool fromData( StrStrMap& map , std::string key , CType& target )
{
	StrStrMap::iterator iter = map.find( key );
	if( iter != map.end() )
	{
		target = to_ot<CType, std::string>( iter->second );
		return true;
	}
	return false;
}

template <>
bool fromData( StrStrMap& map , std::string key , std::string& target );

#endif // COMMON_HPP_ 
