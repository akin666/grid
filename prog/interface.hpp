/*
 * interface.hpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include "../common.hpp"

class Interface
{
public:
	virtual ~Interface();

	virtual void help( const StrStrMap& args ) const = 0;
	virtual bool shouldRun( const StrStrMap& args ) const = 0;
	virtual bool run( const StrStrMap& args ) = 0;
};

#endif // INTERFACE_HPP_ 
