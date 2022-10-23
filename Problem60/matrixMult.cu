/*
 * Copyright (c) 2015-2017, 2020 Veran Medical Technologies
 * Do not reproduce without written permission.
 * All rights reserved.
 * 
 * Created By:       Troy Holsing Aug 11, 2015
 * Last Modified By: Andrew Dougherty Jul 28, 2020
 * 
 * Contributing Authors:
 *   Andrew Dougherty - 100% lines, 77.78% commits, 63 insertions, 14 deletions
 *   Troy Holsing     -   0% lines, 22.22% commits,  0 insertions,  0 deletions
 */

#include <vector>

__global__
void
matrix_mult(int dim1, int dim2, int *a, int *b, int *r)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < dim1*dim1) {
        int dotP = 0;
        int i = index / dim2;
        int j = index % dim2;
        for(int k=0; k<dim2; ++k) {
            dotP += (a[i*dim2 + k] * b[k*dim1 + j]);
        }
        r[i*dim1+j]=dotP;
    }
}

std::vector<std::vector<int>> matrix_mult(const std::vector<std::vector<int>> &A,
                                          const std::vector<std::vector<int>> &B)
{
    std::vector<std::vector<int>> ret = A;
    int *a, *b, *answer;
    int *a_dev, *b_dev, *answer_dev;
    int dim1 = (int)A.size();
    int dim2 = (int)A[0].size();
    int blockSize = 256;
    int numBlocks = (dim1*dim2 + blockSize - 1) / blockSize;
    a = new int[dim1*dim2];
    b = new int[dim1*dim2];
    answer = new int[dim1*dim2];
    for(int i=0; i<dim1; ++i) {
        memcpy(a + i*dim2,&A[i][0],dim2*sizeof(int));
        memcpy(b + i*dim2,&B[i][0],dim2*sizeof(int));
    }
    cudaMalloc((void **)&a_dev, dim1*dim2*sizeof(int));
    cudaMalloc((void **)&b_dev, dim1*dim2*sizeof(int));
    cudaMalloc((void **)&answer_dev, dim1*dim1*sizeof(int));
    cudaMemcpy( a_dev, a, dim1*dim2 * sizeof(int), cudaMemcpyHostToDevice );
    cudaMemcpy( b_dev, b, dim1*dim2 * sizeof(int), cudaMemcpyHostToDevice );
    matrix_mult<<<numBlocks, blockSize>>>(dim1, dim2, a_dev, b_dev, answer_dev);
    cudaMemcpy(answer, answer_dev, dim1*dim1 * sizeof(int), cudaMemcpyDeviceToHost);
    for(int i=0; i<dim1; ++i) {
        memcpy(&ret[i][0],answer + i*dim2,dim2*sizeof(int));
    }
    cudaFree(a_dev);
    cudaFree(b_dev);
    cudaFree(answer_dev);
    delete [] a;
    delete [] b;
    delete [] answer;
    return ret;
}
