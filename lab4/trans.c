/* 
 * Nikhil Grover
 * 1435083
 *
 * trans.c - Natrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part I of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M])
{
  // Assume M and N are positive
  int i, j, block_row, block_column, block_size, temp, diag, isDiag;

  // 32x32 case
  if(M == 32 && N == 32) {
    block_size = 8;
    for(block_row = 0; block_row < N; block_row += block_size) {
      for(block_column = 0; block_column < M; block_column += block_size) {
	for(i = block_row; i < block_row + block_size; i++) {
	  for(j = block_column; j < block_column + block_size; j++) {
	    if(i == j) {
	      temp = A[i][j];
	      diag = i;
	      isDiag = 1;
	    } else {
	      B[j][i] = A[i][j];
	    }
	  }
	  
	  if(isDiag == 1) {
	    B[diag][diag] = temp;
	    isDiag = 0;
	  }
	}
      }
    }
  }

  // 64x64 case
  if(M == 64 && N == 64) {
    block_size = 4;
    for(block_row = 0; block_row < M; block_row += block_size) {
      for(block_column = 0; block_column < N; block_column += block_size) {
	for(i = block_row; i < block_row + block_size; i++) {
	  for(j = block_column; j < block_column + block_size; j++) {
	    if(i == j) {
	      temp = A[i][j];
	      diag = i;
	      isDiag = 1;
	    } else {
	      B[j][i] = A[i][j];
	    }
	  }
	  
	  if(isDiag == 1) {
	    B[diag][diag] = temp;
	    isDiag = 0;
	  }
	}
      }
    }
  }

  // 67x61 case
  if(M == 61 && N == 67) {
    block_size = 16;
    for(block_row = 0; block_row < M; block_row += 16) {
      for(block_column = 0; block_column < N; block_column += 4) {
	for(i = block_row; (i < block_row + 16) && (i < N); i++) {
	  for(j = block_column; (j < block_column + 4) && (j < M); j++) {
	    if((i - block_row) == (j - block_column)) {
	      temp = A[i][j];
	    } else {
	      B[j][i] = A[i][j];
	    }
	  }
	  for(j = block_column; (j < block_column + 4) && (j < M); j++) {
	    if((i - block_row) == (j - block_column)) {
	      B[i][j] = temp;
	    }
	  }
	}
      }
    }
  }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M])
{
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M])
{
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

