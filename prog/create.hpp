/*
 * create.hpp
 *
 *  Created on: 21.7.2012
 *      Author: akin
 */

#ifndef CREATE_HPP_
#define CREATE_HPP_

#include "interface.hpp"

class Create : public Interface
{
public:
	Create();
	virtual ~Create();

	virtual void help( const StrStrMap& args ) const;
	virtual bool shouldRun( const StrStrMap& args ) const;
	virtual bool run( const StrStrMap& args );
};

#endif // CREATE_HPP_ 
