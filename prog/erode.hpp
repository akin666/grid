/*
 * erode.hpp
 *
 *  Created on: 25.7.2012
 *      Author: akin
 */

#ifndef ERODE_HPP_
#define ERODE_HPP_

#include "interface.hpp"

class Erode : public Interface
{
public:
	Erode();
	virtual ~Erode();

	virtual void help( const StrStrMap& args ) const;
	virtual bool shouldRun( const StrStrMap& args ) const;
	virtual bool run( const StrStrMap& args );
};

#endif // ERODE_HPP_ 
