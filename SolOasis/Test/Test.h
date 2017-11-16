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

// Class to run as last test in test list.
// Allows us to include whatever test in
// test array without consequence
class DummyTest : public Test{
public:
	DummyTest(){};
	~DummyTest(){};
	void RunTests(){};
};

#endif /* _TEST_TEST_H_ */
