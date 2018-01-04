#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"


UNIT(SimpleTest)
	int x = 5;
	int y = 10;
	int resault  = x+y;
	ASSERT_THAT(resault ==15);
END_UNIT



TEST_SUITE(framework test)

	TEST(SimpleTest)
	
END_SUITE


