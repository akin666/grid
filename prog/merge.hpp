/*
 * merge.hpp
 *
 *  Created on: 25.7.2012
 *      Author: akin
 */

#ifndef MERGE_HPP_
#define MERGE_HPP_

#include "interface.hpp"

class Merge : public Interface
{
public:
	Merge();
	virtual ~Merge();

	virtual void help( const StrStrMap& args ) const;
	virtual bool shouldRun( const StrStrMap& args ) const;
	virtual bool run( const StrStrMap& args );
};

#endif // MERGE_HPP_ 
