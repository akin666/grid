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
	Interface() {}
	virtual ~Interface() {}

	virtual bool shouldRun( StrStrMap& args ) = 0;
	virtual bool run( StrStrMap& args ) = 0;
};

#endif // INTERFACE_HPP_ 
