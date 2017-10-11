/*
 * CSE 351 Lab 1 (Data Lab - Pointers)
 *
 * Nikhil Grover
 * 1435083
 *
 * pointer.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>. The included file, "common.c" contains a function declaration
 * that should prevent a compiler warning. In general, it's not good practice
 * to ignore compiler warnings, but in this case it's OK.
 */

#ifndef COMMON_H
#include "common.h"
#endif

/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

#if 0
You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

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

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xffffffff.
     However you are allowed to add constants to values greater
     than 255. e.g. 250+250 = 500.
  2. Function arguments and local variables (no global variables).
  3. For 1-3, only use the following:
     Pointer operations *, &. (Note that these are only for dereferencing
     and taking addresses, bitwise & is not allowed).
     Binary integer operations - + *.
     Unary interger operation !.
     For the last three, you may also use shifts (<<, >>), ~, ==, and ^.

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, ?:, sizeof,
     != or binary (bitwise & or |)
  6. Use the [] operator to index into arrays for reading or writing.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has *undefined* behavior when shifting by a negative amount or an amount
  greater than or equal to the number of bits in the value being shifted.
  e.g. For x >> n, shifts by n < 0 or n >= *size of x* are undefined
  e.g. if x is a 32-bit int, shifts by >= 32 bits are undefined
  Undefined means you do not know what result you will get from the operation.
#endif

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 * Test the code below in your own 'main' program.
 *
 */

/*
 * For the following exercises remember:
 * Pointer operations *, & are allowed and should be used vigorously.
 * Pointer operation & is for taking addresses, bitwise & is still not allowed.
 * Do not use the [] operator to index into arrays for reading or writing.
 */

/*
 * Return the size of an integer in bytes.
 */
int intSize() {
  int intArray[10];
  int * intPtr1;
  int * intPtr2;
  // Set the pointers to the 0th and 1st indexes of the
  // array, respectively. Return the difference of the two
  // addresses to find the int size.
  
  intPtr1 = intArray;
  intPtr2 = intPtr1 + 1;
  return (char*) intPtr2 - (char*)intPtr1;
}

/*
 * Return the size of a double in bytes.
 */
int doubleSize() {
  double doubArray[10];
  double * doubPtr1;
  double * doubPtr2;
  // Similar to arraySize, set the address to adjacent
  // indices array, and take the address difference.

  doubPtr1 = doubArray;
  doubPtr2 = doubPtr1 + 1;
  return (char*)doubPtr2 - (char*)doubPtr1;
}

/*
 * Return the size of a pointer in bytes.
 */
int pointerSize() {
  double * ptrArray[10];
  double ** ptrPtr1;
  double ** ptrPtr2;
  // Same concept as the previous two, only with pointer array

  ptrPtr1 = ptrArray;
  ptrPtr2 = ptrPtr1 + 1;
  return (char*)ptrPtr2 - (char*)ptrPtr1;
}

/*
 * For the 3 remaining problems you are allowed to use shifts (<<, >>), ~, ==, and ^
 * in addition to the previously specified operators.
 * The previous restrictions still apply.
 */

/*
 * Modify intArray[5] to be the value 351 using only intArray and pointer arithmetic.
 */
int changeValue() {
  int intArray[10];
  int * intPtr1 = intArray;
  // Remember not to use constants greater than 255.
  // Remember to use * to dereference.

  // Use shifts to set an int 'x' to 351,
  // then  set another ptr to 5 indices
  // beyond intPtr1, which will set the 
  // 5th index to 351.

  int x = 0x1;
  x = x << 8;
  x = x + 0x5F;
  intPtr2 = intPtr1 + 5;
  *intPtr2 = value;

  return intArray[5];
}

/*
 * Return 1 if the addresses stored in ptr1 and ptr2 are within the
 * *same* 64-byte aligned  block of memory. Return zero otherwise.
 * Operators / and % and loops are NOT allowed.
 */
int withinSameBlock(int *ptr1, int *ptr2) {
  // Mask out the last 6 bits and compare them,
  // because that should be th eonly thing
  // determing whether or not both addresses are 
  // in the same block.
  int x1 = (char*) &(*ptr1);
  int x2 = (char*) &(*ptr2);
  int mask = 0xFF;
  mask = (mask << 8) + 0xFF;
  mask = (mask << 8) + 0xFF;
  mask = (mask << 8) + 0XC0;
  x1 = x1 & mask;
  x2 = x2 & mask;
  return x1 == x2;
}

/*
 * Return 1 if ptr points to an element within the specified intArray, 0 otherwise.
 * Pointing anywhere in the array is fair game, ptr does not have to
 * point to the beginning of an element.
 * size is the size of intArray in number of ints. Can assume size != 0.
 * Operators / and % and loops are NOT allowed.
 */
int withinArray(int * intArray, int size, int * ptr) {
  /*
   * If the pointer, x,  is pointing to an element that is
   * is indeed within the array, then the difference between
   * the front of the array and x will be the same sign as 
   * the difference between the end of the array and x. If
   * this indeed the case, the sum of the sign bits will be zero.
   */
  int p1 = (char*) &(*intArray);
  int p2 = p1 + 4 * (size - 1);
  int p3 = (char*) &(*ptr);
  int firstElementSign = ((p3 - p1) >> 31) & 1;
  int secondElementSign = ((p2 - p3) >> 31) & 1;
  return (firstElementSign + secondElementSign) == 0;
}
