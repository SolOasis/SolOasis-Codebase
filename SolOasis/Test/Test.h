/*
 * Test.h
 *
 *  Created on: Nov 16, 2017
 *      Author: Chris
 */

#ifndef _TEST_TEST_H_
#define _TEST_TEST_H_

typedef enum ETestStatus{
	PASS,
	FAIL
}TestStatus;

class Test{
public:
	virtual ~Test(){};
	virtual void RunTests() = 0;
};

#endif /* _TEST_TEST_H_ */
