#include <iostream>
#include "core/timer.h"
#include <cuda_runtime.h>
#include <limits>

__constant__ double sp_mat_dev[128];

__global__
void
initialize_vector(const uint64_t rows, const int fortune, double * __restrict__ v)
{
    const uint64_t index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < rows) {
        v[index] = 1.0 * fortune / rows;
    }
}

__global__
void
sparse_multiply(const uint64_t rows, const uint64_t offset, const int cost, const uint64_t entriesPerRow, const uint64_t nonzeroRows,
                double * __restrict__ v, double * __restrict__ r)
{
    const uint64_t index = blockIdx.x * blockDim.x + threadIdx.x + offset;
    if(index < rows) {
        double sum = 0.0;
        if(index < cost - 1) {
            sum = v[index];
        }
        else {
            int spIndex = 0;
            const int offset = index - cost + 1;
            int i = 0;
            while(spIndex < 2*entriesPerRow && i < nonzeroRows && i < rows) {
                i = sp_mat_dev[spIndex] + offset;
                const double value = sp_mat_dev[spIndex + 1];
                spIndex += 2;
                if(i < rows) {
                    sum += value * v[i];
                }
            }
        }
        r[index] = sum;
    }
}

__global__
void
element_sum(const uint64_t rows, double * __restrict__ v, double * __restrict__ sum)
{
    const uint64_t index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < rows) {
        atomicAdd(&sum[0], v[index]);
    }
}

__global__
void
element_squared_sum(const uint64_t rows, double * __restrict__ v, double * __restrict__ sum)
{
    const uint64_t index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < rows) {
        const double val = v[index];
        atomicAdd(&sum[0], val * val);
    }
}

__global__
void
vector_scale(const uint64_t rows, const double scale, double * __restrict__ v)
{
    const uint64_t index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < rows) {
        v[index] *= scale;
    }
}

__global__
void
vector_difference_l1_norm(const uint64_t rows, double * __restrict__ v, double * __restrict__ r,
                          double * __restrict__ l1Norm)
{
    const uint64_t index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < rows) {
        atomicAdd(&l1Norm[0], abs(v[index] - r[index]));
    }
}

__global__
void
vector_difference_sum_of_squares(const uint64_t rows, double * __restrict__ v, double * __restrict__ r,
                                 double * __restrict__ sum)
{
    const uint64_t index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < rows) {
        const double val = abs(v[index] - r[index]);
        atomicAdd(&sum[0], val*val);
    }
}

double
problem499_arnoldi(const uint64_t &fortune, const uint64_t &cost)
{
    std::cout << "begin arnoldi compute" << std::endl;
    return 0.0;

}

double
problem499_cuda(const uint64_t &fortune, const uint64_t &cost, const int &precision, const uint64_t &maxItrs,
                int maxNumBlocks, bool arnoldi)
{
    if(arnoldi) {
        return problem499_arnoldi(fortune,cost);
    }
    bool verbose = false;
    std::cout << "begin standard compute" << std::endl;
    Timer timer;
    double *sp_mat;
    double *v_dev, *r_dev;
    bool checkResidual = false;
    bool checkAnswer = false;
    uint64_t minAdditionalRows = 1022;
    uint64_t additionalRows = max((uint64_t)pow(2,ceil(log2(10*fortune))) - 1,minAdditionalRows);
    uint64_t rows = fortune + additionalRows;
    uint64_t blockSize = 1024;
//    uint64_t numBlocks = rows / blockSize;
    uint64_t numBlocks = min((uint64_t)maxNumBlocks,rows / blockSize + 1);
    uint64_t rowsPerProblem = blockSize * numBlocks;
    uint64_t numProblems = (uint64_t)ceil(1.0*rows/rowsPerProblem);
    uint64_t entriesPerRow = (uint64_t)ceil(log2(rows));
    std::cout << "rows: " << rows << std::endl;
    std::cout << "entriesPerRow: " << entriesPerRow << std::endl;
    std::cout << "numBlocks: " << numBlocks << std::endl;
    std::cout << "rowsPerProblem: " << rowsPerProblem << std::endl;
    std::cout << "numProblems: " << numProblems << std::endl;
    size_t availableMemory;
    size_t totalMemory;
    cudaMemGetInfo(&availableMemory, &totalMemory);
    std::cout << "availableMemory: " << availableMemory << std::endl;
    std::cout << "totalMemory: " << totalMemory << std::endl;
    std::cout << "blockSize*numBlocks: " << blockSize*numBlocks << std::endl;
    auto memNeeded = 2*rows*sizeof(double)+2*sizeof(double);
    std::cout << "memory needed: " << memNeeded << std::endl;
    std::cout << "% memory used: " << 1.0 * memNeeded / availableMemory << std::endl;
    cudaMalloc((void **)&v_dev, rows*sizeof(double));
    cudaMalloc((void **)&r_dev, rows*sizeof(double));
    cudaMemset(v_dev, 0, rows*sizeof(double));
    sp_mat = new double[2*entriesPerRow];
    uint64_t i = 0;
    double prob = 0.5;
    uint64_t mult=1;
    uint64_t spIndex = 0;
    while(i < rows) {
        sp_mat[spIndex] = i;
        sp_mat[spIndex + 1] = prob;
        spIndex += 2;
        prob *= 0.5;
        i += mult;
        mult *= 2;
    }
    cudaMemcpyToSymbol(sp_mat_dev, sp_mat, 2*entriesPerRow*sizeof(double));
    bool initFull = false;
    if(initFull) {
        initialize_vector<<<numBlocks, blockSize>>>(rows, fortune, v_dev);
    }
    else {
//        double firstEntry = 1;
        double firstEntry = std::numeric_limits<float>::max();
        cudaMemcpy(v_dev, &firstEntry, sizeof(double), cudaMemcpyHostToDevice);
    }
    double * res_norm_dev;
    double res_norm = 1.0;
    double tol = pow(10,-(precision*2+1));
    uint64_t itr = 0;
    double * sum_dev;
    double sum;
    cudaMalloc((void **)&sum_dev, sizeof(double));
    cudaMalloc((void **)&res_norm_dev, sizeof(double));
    bool l2Norm = false;
    double * state_vec = new double[fortune];
    Timer timer2;
    double answer = 0;
    double prevAnswer = 1;
    int fortuneDigits = (int)ceil(log10(fortune));
    int check = pow(10,fortuneDigits);
    bool scale=false;
    Timer timer3;
    while(res_norm > tol && itr < maxItrs) {
        for(uint64_t i=0; i<numProblems; ++i) {
            uint64_t offset = rowsPerProblem*i;
            if(offset > itr) {
                break;
            }
            sparse_multiply<<<numBlocks, blockSize>>>(rows, offset, cost, entriesPerRow, itr+1,
                                                      v_dev, r_dev);
        }
        if(scale) {
            cudaMemset(sum_dev, 0, sizeof(double));
            if(l2Norm) {
                element_squared_sum<<<numBlocks, blockSize>>>(rows, r_dev, sum_dev);
            }
            else {
                element_sum<<<numBlocks, blockSize>>>(rows, r_dev, sum_dev);
            }
            cudaMemcpy(&sum, sum_dev, sizeof(double), cudaMemcpyDeviceToHost);
            vector_scale<<<numBlocks, blockSize>>>(rows, l2Norm ? 1.0 / sqrt(sum) : 1.0 / sum, r_dev);
        }
        ++itr;
        if(checkResidual) {
            if(l2Norm) {
                cudaMemset(sum_dev, 0, sizeof(double));
                vector_difference_sum_of_squares<<<numBlocks, blockSize>>>(rows, v_dev, r_dev, sum_dev);
                cudaMemcpy(&sum, sum_dev, sizeof(double), cudaMemcpyDeviceToHost);
                res_norm = sqrt(sum);
            }
            else {
                cudaMemset(res_norm_dev, 0, sizeof(double));
                vector_difference_l1_norm<<<numBlocks, blockSize>>>(rows, v_dev, r_dev, res_norm_dev);
                cudaMemcpy(&res_norm, res_norm_dev, sizeof(double), cudaMemcpyDeviceToHost);
            }
            if(verbose && itr % (maxItrs / 10) == 0) {
                std::cout << "iterations: " << itr << std::endl;
                std::cout << "residual norm: " << res_norm << std::endl;
                std::cout << "itrs took " << timer2.ticks().count()/1000.0 << " ms" << std::endl;
                timer2.reset();
            }
        }
        else if(checkAnswer && itr % check == 0) {
            cudaMemcpy(state_vec, v_dev, fortune * sizeof(double), cudaMemcpyDeviceToHost);
            answer=0;
            for(uint64_t i=0 ; i < fortune-1; ++i) {
                answer += state_vec[i];
            }
            std::cout << "prevAnswer: " << prevAnswer << std::endl;
            std::cout << "answer: " << answer << std::endl;
            if(std::abs(prevAnswer - answer) < tol) {
                break;
            }
            if(verbose) {
                std::cout << "iterations: " << itr << std::endl;
                printf("current answer: %.8f\n",answer);
                std::cout << "itrs took " << timer2.ticks().count()/1000.0 << " ms" << std::endl;
                timer2.reset();
            }
            prevAnswer = answer;
        }
        cudaMemcpy(v_dev, r_dev, rows*sizeof(double), cudaMemcpyDeviceToDevice);
        if(rows > 10e6 && itr % 1000 == 0) {
            std::cout << "itrs " << itr-1000 << "-" << itr << " took " << timer3.ticks().count()/1000.0 << " ms" << std::endl;
            timer3.reset();
        }
    }
    std::cout << "total iterations: " << itr << std::endl;
    if(checkResidual) {
        std::cout << "final residual norm: " << res_norm << std::endl;
    }
    if(l2Norm || !scale) {
        cudaMemset(sum_dev, 0, sizeof(double));
        element_sum<<<numBlocks, blockSize>>>(rows, v_dev, sum_dev);
        cudaMemcpy(&sum, sum_dev, sizeof(double), cudaMemcpyDeviceToHost);
        vector_scale<<<numBlocks, blockSize>>>(rows, 1.0 / sum, v_dev);
    }
    cudaMemcpy(state_vec, v_dev, fortune * sizeof(double), cudaMemcpyDeviceToHost);
    answer=0;
    for(uint64_t i=0 ; i < fortune-1; ++i) {
        answer += state_vec[i];
    }
    cudaFree(v_dev);
    cudaFree(r_dev);
    cudaFree(sum_dev);
    cudaFree(res_norm_dev);
    delete [] state_vec;
    std::cout << "  calculating probability took " << timer.ticks().count()/1000.0 << " ms" << std::endl;
    return answer;
}
