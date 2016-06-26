/* 
 * File:   increment_gpu.cpp
 * Author: peter 
 *
 * Created on March 26, 2013, 2:58 PM
 */

#include <stdlib.h>
#include <stdio.h>
//#include <helper_cuda.h>
#include <curand_kernel.h>

#include <cuda_runtime.h>
// includes, project
//#include <helper_cuda.h>
//#include <helper_functions.h> // helper utility functions 

#include "common.h"
#include <algorithm>
#include <vector>
/*
 * 
 */

static __global__ void increment_gpu(float* a, float b, int N){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if( idx < N){
        a[ idx] = a[ idx] + b;
    }
}

void func(){
    printf("jkl");
}

void do_cuda_increment_gpu(DataPlan* plan){ //plan will be stored in device global memory
    increment_gpu<<< plan->dataCount/blockSize, blockSize>>> ( plan->a, plan->increment, plan->dataCount);
    std::vector<int> v(100,0);
    std::sort( v.begin(), v.end());
} 
