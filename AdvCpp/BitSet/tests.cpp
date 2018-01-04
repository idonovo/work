
#include "mu_test.h"
#include "BitSet.h"

#include <wchar.h>
#include <iostream>
#include <cstdlib> // mbstowcs
#include <stdexcept>

using namespace advcpp;



/* ============================= 	*/
/*			char tests				*/
/* ============================= 	*/	
UNIT(bitset_CTOR)
	unsigned int array[12] = {1, 0, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset(array);
	std::cout <<  bitset;

END_UNIT

UNIT(bitset_copy_CTOR)
	unsigned int array[12] = {1, 0, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset(array);
	BitSet<12,char> another(bitset);
	std::cout <<  bitset;
	std::cout <<  another;
	
END_UNIT

UNIT(bitset_assign_operator)
	unsigned int array1[8] = {1, 0, 0, 1,1, 0, 1, 1};
	unsigned int array2[8] = {0, 0, 1, 1,0, 0, 1, 0,};  
	BitSet<12,char> bitset(array1);
	BitSet<12,char> another(array2);
	another = bitset;
	std::cout <<  bitset;
	std::cout <<  another;	
	
END_UNIT

UNIT(Get_Subscripe)
	unsigned int array1[8] = {1, 0, 0, 1,1, 0, 1, 1};
	BitSet<8,char> bitset(array1);
	bool r =false;
	r = bitset[1];
    ASSERT_THAT(r == 0);
	
END_UNIT

UNIT(Set_Subscripe)
	unsigned int array1[8] = {1, 0, 0, 1,1, 0, 1, 1};
	BitSet<8,char> bitset(array1);
	bitset[4] = false;
    ASSERT_THAT(bitset[4] == false);
	
END_UNIT

UNIT(Get_Bit)
	unsigned int array1[8] = {1, 0, 0, 1,1, 0, 1, 1};
	BitSet<8,char> bitset(array1);
	bool r =false;
	r = bitset.GetBit(7);
    ASSERT_THAT(r == 1);
	
END_UNIT

UNIT(count)
	unsigned int array1[5000] = {0};
	array1[23] = 1;
	array1[2022]= 1;
	BitSet<5000,char> bitset(array1);
    ASSERT_THAT(bitset.Count() == 2);
	
END_UNIT

UNIT(Bit_On)
	unsigned int array1[8] = {1, 0, 0, 1,1, 0, 1, 1};
	BitSet<8,char> bitset(array1);
	bool r =false;
	bitset.BitOn(1);
	r = bitset.GetBit(1);
    ASSERT_THAT(r == 1);
	
END_UNIT

UNIT(Bit_Off)
	unsigned int array1[8] = {1, 0, 0, 1,1, 0, 1, 1};
	BitSet<8,char> bitset(array1);
	bitset.BitOff(4);
    ASSERT_THAT(false == bitset[4]);
	
END_UNIT

UNIT(Any)
	unsigned int array1[8] = {1, 0, 0, 1,1, 0, 1, 1};
	BitSet<8,char> bitset(array1);
	bitset.BitOff(4);
    ASSERT_THAT(bitset.Any());
	
END_UNIT

UNIT(All)
	unsigned int array1[10] = {1, 1, 1, 1,1, 0, 1, 1, 1 , 0};
	BitSet<9,char> bitset(array1);
    ASSERT_THAT(!bitset.All());
	
END_UNIT

UNIT(None)
	unsigned int array1[1000] = {0};
	BitSet<1000,char> bitset(array1);
    ASSERT_THAT(bitset.None());
	
END_UNIT

UNIT(Print)
	unsigned int array1[12] = {1, 0, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset(array1);
	std::cout << bitset;
	
END_UNIT

UNIT(Op_andEq)
	unsigned int array1[12] = {1, 0, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset1(array1);
	unsigned int array2[12] = {1, 1, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset2(array2);
	bitset2 &=bitset1;
	ASSERT_THAT(bitset2[1] ==false);
	
END_UNIT

UNIT(Op_orEq)
	unsigned int array1[12] = {1, 0, 1, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset1(array1);
	unsigned int array2[12] = {1, 0, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset2(array2);
	bitset2 |=bitset1;
	ASSERT_THAT(bitset2[2] ==true);
	
END_UNIT

UNIT(Op_xorEq)
	unsigned int array1[12] = {1, 0, 1, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset1(array1);
	unsigned int array2[12] = {1, 0, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset2(array2);
	bitset2 ^=bitset1;
	ASSERT_THAT(bitset2[2] ==true);
	
END_UNIT

UNIT(Op_flip)
	unsigned int array2[12] = {1, 0, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset2(array2);
	std::cout << bitset2;
	~bitset2;
	std::cout << bitset2;
	ASSERT_THAT(bitset2[2] ==true);
	
END_UNIT

UNIT(Op_Shift_Eq)
	unsigned int array2[12] = {1, 0, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset2(array2);
	std::cout << bitset2;
	bitset2 <<=4;
	std::cout << bitset2;
	
END_UNIT

UNIT(Op_RShift_Eq)
	unsigned int array2[12] = {1, 0, 0, 1,1, 0, 1, 0,0,0,1,1}; 
	BitSet<12,char> bitset2(array2);
	std::cout << bitset2;
	bitset2 >>= 4;
	std::cout << bitset2;
	
END_UNIT

UNIT(Op_eq)
	unsigned int array1[8] = {1, 0, 0, 1, 1, 0, 0, 1}; 
	BitSet<8,char> bitset1(array1);
	unsigned int array2[8] = {1, 0, 0, 1, 1, 0, 0, 1}; 
	BitSet<8,char> bitset2(array2);
	ASSERT_THAT(bitset1 == bitset2);
	
END_UNIT

/* ============================= 	*/
/*			TEST SUIT				*/
/* ============================= 	*/	

TEST_SUITE(bitset)
    TEST(bitset_CTOR)
    TEST(bitset_copy_CTOR)
    TEST(bitset_assign_operator)
    TEST(Get_Subscripe)
    TEST(Set_Subscripe)
    TEST(Get_Bit)
    TEST(count)
    TEST(Bit_On)
    TEST(Bit_Off)
    TEST(Any)
    TEST(All)
    TEST(None)
    TEST(Print)
    TEST(Op_andEq) 
    TEST(Op_orEq) 
    TEST(Op_xorEq) 
    TEST(Op_flip)
    TEST(Op_eq)
	TEST(Op_Shift_Eq)
	TEST(Op_RShift_Eq)
END_SUITE

/* ============================= 	*/

