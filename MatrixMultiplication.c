/*****************************************************************************
* Copyright (C) Intel Corporation. All Rights Reserved.
*
* The source code, information and material ("Material") contained herein is
* owned by Intel Corporation or its suppliers or licensors, and title to such
* Material remains with Intel Corporation or its suppliers or licensors. The
* Material contains proprietary information of Intel or its suppliers and
* licensors. The Material is protected by worldwide copyright laws and treaty
* provisions. No part of the Material may be used, copied, reproduced,
* modified, published, uploaded, posted, transmitted, distributed or disclosed
* in any way without Intel's prior express written permission. No license
* under any patent, copyright or other intellectual property rights in the
* Material is granted to or conferred upon you, either expressly, by
* implication, inducement, estoppel or otherwise. Any license under such
* intellectual property rights must be express and approved by Intel in
* writing.
*
* *Third Party trademarks are the property of their respective owners.

* Unless otherwise agreed by Intel in writing, you may not remove or alter
* this notice or any other notice embedded in Materials by Intel or Intel's
* suppliers or licensors in any way.
*
*****************************************************************************/

/*****************************************************************************
* This example measures performance of computing the matrix product
* using a triple nested loop, where A, B, and C are matrices.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Consider adjusting LOOP_COUNT based on the performance of your computer
// to ensure that total run time is at least 1 second
#define LOOP_COUNT 2

// matrix_muliply multiplies m x p and p x n matrices
int matrix_multiply(int loop_count, int m, int p, int n)
{
  double *A, *B, *C;
  int    i, j, k, r;
  double sum;
  struct timeval start, end;
  long   total_time, seconds, useconds;

  printf (" Initializing data for matrix multiplication C=A*B for matrix \n"
          " A(%ix%i) and matrix B(%ix%i)\n\n", m, p, p, n);

  // printf (" Allocating memory for matrices \n\n");
  A = (double *)malloc( m*p*sizeof( double ));
  B = (double *)malloc( p*n*sizeof( double ));
  C = (double *)malloc( m*n*sizeof( double ));
  if (A == NULL || B == NULL || C == NULL)
  {
    printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
    if (A)
      free(A);
    if (B)
      free(B);
    if (C)
      free(C);
    return 1;
  }

  //printf (" Intializing matrix data \n\n");
  for (i = 0; i < (m*p); i++)
    A[i] = (double)(i+1);

  for (i = 0; i < (p*n); i++)
    B[i] = (double)(-i-1);

  for (i = 0; i < (m*n); i++)
    C[i] = 0.0;

  //printf (" First matrix product using triple nested loop \n\n");
  /*for (i = 0; i < m; i++)
  {
#if OPT
    for (k = 0; k < p; k++)
#else
    for (j = 0; j < n; j++)
#endif
    {
      sum = 0.0;
#if OPT
      for (j = 0; j < n; j++)
#else
      for (k = 0; k < p; k++)
#endif
        sum += A[p*i+k] * B[n*k+j];
      C[n*i+j] = sum;
    }
  }
*/
  //printf (" Measuring performance of matrix product using triple nested loop \n\n");
  gettimeofday(&start, NULL);

  for (r = 0; r < loop_count; r++)
  {
    for (i = 0; i < m; i++)
    {
#if OPT
      for (k = 0; k < p; k++)
#else
      for (j = 0; j < n; j++)
#endif
      {
        sum = 0.0;
#if OPT
        for (j = 0; j < n; j++)
#else
        for (k = 0; k < p; k++)
#endif
          sum += A[p*i+k] * B[n*k+j];
        C[n*i+j] = sum;
      }
    }
  }
  gettimeofday(&end, NULL);

  seconds = end.tv_sec - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec ;
  total_time = ((seconds)*1000 + useconds/1000.0) + 0.5;

  printf("===== Matrix multiplication is completed =====\n"
         "===== %u iterations in %ld milliseconds (%f) =====\n\n",
         loop_count, total_time, sum);

  free(A);
  free(B);
  free(C);

  return 0;
}


int main(int argc, char** argv)
{
  int displayUsage=0, loop_count=LOOP_COUNT, m=2000, n=2500, p=500;

  printf ("\n This example measures performance of the matrix product\n\n");

  if (argc > 1)
  { // arguments specified
    for (int i = 1; i < argc; i++)
    {
      if (((argv[i][0] == '-') || (argv[i][0] == '/')) &&
            argv[i][1] && (argc > i + 1))
      {
        switch (argv[i][1])
        {
          case 'l':
            loop_count = atoi(argv[++i]);
	    break;
          case 'm':
            m = atoi(argv[++i]);
            break;
          case 'n':
            n = atoi(argv[++i]);
            break;
          case 'p':
            p = atoi(argv[++i]);
            break;
          default:
            displayUsage = 1;
        }
      }
      else
        displayUsage = 1;
    }

    if (displayUsage > 0)
    {
      printf("Usage: Matrix_Multiply [-l #] [-m #] [-n #] [-p #]\n");
      printf("where: # is an decimal integer value, and\n");
      printf("       l is the loop count\n");
      printf("       m, n, and p specify matrix MxP and PxN dimensions\n");
      printf("default: l=%i, m=%i, p=%i, n=%i\n", LOOP_COUNT, m, p, n);
    }
  }

  return (displayUsage == 0) ? matrix_multiply(loop_count, m, p, n) : 0;
}

