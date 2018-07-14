/*
* CS:APP Data Lab
*
* <Joel George 004786402>
*
* bits.c - Source file with your solutions to the Lab.
*          This is the file you will hand in to your instructor.
*
* WARNING: Do not include the <stdio.h> header; it confuses the dlc
* compiler. You can still use printf for debugging without including
* <stdio.h>, although you might get a compiler warning. In general,
* it's not good practice to ignore compiler warnings, but in this
* case it's OK.
*/

#if 0
/*
* Instructions to Students:
*
* STEP 1: Read the following instructions carefully.
*/

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES :

Replace the "return" statement in each function with one
or more lines of C code that implements the function.Your code
must conform to the following style :

int Funct(arg1, arg2, ...) {
	/* brief description of how your implementation works */
	int var1 = Expr1;
	...
		int varM = ExprM;

	varJ = ExprJ;
	...
		varN = ExprN;
	return ExprR;
}

Each "Expr" is an expression using ONLY the following :
1. Integer constants 0 through 255 (0xFF), inclusive.You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables(no global variables).
3. Unary integer operations !~
4. Binary integer operations & ^ | +<< >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators.You are not restricted to
one operator per line.

You are expressly forbidden to :
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, || , -, or ? :
	6. Use any form of casting.
	7. Use any data type other than int.This implies that you
	cannot use arrays, structs, or unions.


	You may assume that your machine :
1. Uses 2s complement, 32 - bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE :
/*
* pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
*/
int pow2plus1(int x) {
	/* exploit ability of shifts to compute powers of 2 */
	return (1 << x) + 1;
}

/*
* pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
*/
int pow2plus4(int x) {
	/* exploit ability of shifts to compute powers of 2 */
	int result = (1 << x);
	result += 4;
	return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implent floating - point operations,
the coding rules are less strict.You are allowed to use looping and
conditional control.You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to :
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned.This means that you
cannot use arrays, structs, or unions.
6. Use any floating point data types, operations, or constants.


NOTES:
1. Use the dlc(data lab checker) compiler(described in the handout) to
check the legality of your solutions.
2. Each function has a maximum number of operators(!~& ^ | +<< >> )
that you are allowed to use for your implementation of the function.
The max operator count is checked by dlc.Note that '=' is not
counted; you may use as many of these as you want without penalty.
3. Use the btest test harness to check your functions for correctness.
4. Use the BDD checker to formally verify your functions
5. The maximum number of ops for each function is given in the
header comment for each function.If there are any inconsistencies
between the maximum ops in the writeup and in this file, consider
this file the authoritative source.

/*
* STEP 2: Modify the following functions according the coding rules.
*
*   IMPORTANT. TO AVOID GRADING SURPRISES:
*   1. Use the dlc compiler to check that your solutions conform
*      to the coding rules.
*   2. Use the BDD checker to formally verify that your solutions produce
*      the correct answers.
*/


#endif
/*
* bang - Compute !x without using !
*   Examples: bang(3) = 0, bang(0) = 1
*   Legal ops: ~ & ^ | + << >>
*   Max ops: 12
*   Rating: 4
*/
int bang(int x) {
	/*This function determines if something is nonzero by smearing
	the sign of the value, and then taking the negative of that value and 
	smearing the sign of that too. Only for 0 will both of these smears be 0,
	and the adding of 1 allows us to return 1. If the value is non-zero,
	one of these smears will be -1, thus returning 0.*/
	return ((x >> 31) | ((~x + 1) >> 31)) + 1;
}
/*
* bitCount - returns count of number of 1's in word
*   Examples: bitCount(5) = 2, bitCount(7) = 3
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 40
*   Rating: 4
*/
int bitCount(int x) {
	int mask, mask_2, mask_3, mask_4, mask_5;
	/*This function counts the number of 1s in a bit sequence, 
	starting by grouping the bit sequence into groups of 16, 8, 4, 2, and then 1 final group. 
	The first section of the code breaks the bits into groups of two and counts the number of 1 in that 
	group by shifting that bit sequence one to the right, masking it to delete the shifted value, and then 
	subtracting the shifted value from the original value. The second section of the code works in a similar 
	way, breaking the bits into groups of 4 and counting the number of ones by shifting both the original value and 
	the subtraction value to the right, masking both, and this time subtracting the subtraction value from the other.
	and then adds the two. Then, it repeats this process until you process the sequence as a final group. */

	mask = 0x55;
	mask = 0x55 + (mask << 8);
	mask = mask + (mask << 16);
	x = ~((x >> 1) & mask) + 1 + x;

	mask_2 = 0x33;
	mask_2 = 0x33 + (mask_2 << 8);
	mask_2 = (mask_2 << 16) + mask_2; 

	x = (x & mask_2) + ((x >> 2) & mask_2);	

	mask_3 = 0x0f;
	mask_3 = (mask_3 << 8) + 0x0f;
	mask_3 = (mask_3 << 16) + mask_3; 

	x = (x & mask_3) + ((x >> 4) & mask_3); 

	mask_4 = 0xff;
	mask_4 = (mask_4 << 16) + mask_4; 

	x = (x & mask_4) + ((x >> 8) & mask_4); 

	mask_5 = 0xff;
	mask_5 = (mask_5 << 8) + 0xff; 

	return (x & mask_5) + ((x >> 16) & mask_5); 
}
/*
* bitOr - x|y using only ~ and &
*   Example: bitOr(6, 5) = 7
*   Legal ops: ~ &
*   Max ops: 8
*   Rating: 1
*/
int bitOr(int x, int y) {
	/*This works by taking and'ing the complement of both x and y,
	and then taking the complement of that and. The reason why this works is 
	because according to DeMorgan's laws, ~(~x & ~y) is equal to x | y.*/
	return ~(~x & ~y);
}
/*
* bitRepeat - repeat x's low-order n bits until word is full.
*   Can assume that 1 <= n <= 32.
*   Examples: bitRepeat(1, 1) = -1
*             bitRepeat(7, 4) = 0x77777777
*             bitRepeat(0x13f, 8) = 0x3f3f3f3f
*             bitRepeat(0xfffe02, 9) = 0x10080402
*             bitRepeat(-559038737, 31) = -559038737
*             bitRepeat(-559038737, 32) = -559038737
*   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
*             (This is more general than the usual integer coding rules.)
*   Max ops: 40
*   Rating: 4
*/
int bitRepeat(int x, int n) {
	int adjust_value, return_value, shift_size, test;
	unsigned int a;
	/*This function clears out the unwanted bits, then 
	shifts the shifts the desired bits by the size of those bits. Once that is done, it adds the desired
	bits to the end of the function, and repeating the process until the shifting value exceeds 32.
	*/

	adjust_value = 32 - n; 

	a = x;
	a = a << adjust_value;	
	a = a >> adjust_value;

	return_value = a;
	shift_size = n;

	test = !(shift_size/32);

	return_value = (return_value << (shift_size * test)) + return_value * test;
	shift_size = 2 * shift_size;
	test = !(shift_size / 32);

	return_value = (return_value << (shift_size * test)) + return_value * test;
	shift_size = 2 * shift_size;
	test = !(shift_size / 32);

	return_value = (return_value << (shift_size * test)) + return_value * test;
	shift_size = 2 * shift_size;
	test = !(shift_size / 32);

	return_value = (return_value << (shift_size * test)) + return_value * test;
	shift_size = 2 * shift_size;
	test = !(shift_size / 32);

	return_value = (return_value << (shift_size * test)) + return_value * test;

	return return_value;
}
/*
* fitsBits - return 1 if x can be represented as an
*  n-bit, two's complement integer.
*   1 <= n <= 32
*   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 15
*   Rating: 2
*/
int fitsBits(int x, int n) {
	int value;
	/*Left shifts the bits to drop off the n most significant bits, then left shifts
	the value back and compares it to x to see if the value did not change. If it did, 
	this function returns 0.*/
	value = (x << (32 + ~n + 1)) >> (32 + ~n + 1);
	return !(value ^ x);
}
/*
* getByte - Extract byte n from word x
*   Bytes numbered from 0 (LSB) to 3 (MSB)
*   Examples: getByte(0x12345678,1) = 0x56
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 6
*   Rating: 2
*/
int getByte(int x, int n) {
	/*Essentially just shifts the bit sequence over by n * 8 and 
	masks the sequence with 0xFF*/
	return (x >> (n << 3)) & 255;
}
/*
* isLessOrEqual - if x <= y  then return 1, else return 0
*   Example: isLessOrEqual(4,5) = 1.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 24
*   Rating: 3
*/
int isLessOrEqual(int x, int y) {
	int x_sign, y_sign, xy_same, a, b;
	/*Checks if x and y have the same sign; if they do, checks if the difference is negative.
	If the difference is negative, returns 0; if the difference is not, returns 1. If x and y have
	different signs, checks if x is negative; if it is, returns 1, else return 0.*/
	x_sign = x >> 31;
	y_sign = y >> 31;
	xy_same = x_sign ^ y_sign;//0000 if same, 1111 if not	//00000
	a = (~x + 1) + y;
	b = a >> 31;
	return ((xy_same & x_sign)& 1) | ((~xy_same & ~b) & 1);
}
/*
* isPositive - return 1 if x > 0, return 0 otherwise
*   Example: isPositive(-1) = 0.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 8
*   Rating: 3
*/
int isPositive(int x) {
	int x_inverse, y, y_sign, same_sign;
	/*Checks if inverse of x is negative, and then checks if x and the result of the inverse + 1 operation are the same.
	If they are, return 0; if not, return 1.*/
	x_inverse = ~x;
	y = x_inverse + 1;
	y_sign = y >> 31;
	same_sign = (x >> 31) ^ y_sign;
	return (same_sign & y_sign) & 1;
}
/*
* logicalShift - shift x to the right by n, using a logical shift
*   Can assume that 0 <= n <= 31
*   Examples: logicalShift(0x87654321,4) = 0x08765432
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 20
*   Rating: 3
*/
int logicalShift(int x, int n) {
	int a, b, z;
	/*First I left shift the bit sequence, and then mask it with b, which is essentially a 
	bit sequence of 'n' 0s followed by 1s, to 0 out the first 'n' bits of the 'x' bit sequence.*/
	a = x >> n;
	z = (!!n << 31) >> 31;
	b = ~((~0) << (z & (32 + ~n + 1))) + ~z;
	return (a & b);
}
/*
* tmin - return minimum two's complement integer
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 4
*   Rating: 1
*/
int tmin(void) {
	/*Just left shift 1 by 31 bits.*/
	return 1 << 31;
}
