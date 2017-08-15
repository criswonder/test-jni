/*
 * Test.h
 *
 *  Created on: Feb 13, 2016
 *      Author: Joe
 */

#ifndef Test_H_
#define Test_H_

#include "Test.h"

class Test
{
public:
	Test(int ab,int cd,int dc);
	virtual ~Test();

	void setTransforamMatrix(float* fm);

private:

	double _alpha = 0;

};

#endif /* Test_H_ */
