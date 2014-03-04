/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 26, 2013, 2:29 PM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;
// includes CUDA Runtime
#include <cuda_runtime.h>
// includes, project
//#include <helper_cuda.h>
//#include <helper_functions.h> // helper utility functions 

#include "common.h"
/*
 * 
 */
void print(float* tab, int N){

    for(unsigned int i=0;i<N;i++){
        printf("\ni:%d, tab=%f",i,*(tab+i));
    }
}


int main(int argc, char** argv) {

    unsigned int N = 16;//vector size
    
    //allocate host memory
    unsigned int numBytes = N * sizeof( float);
    float* h_A = ( float*) malloc( numBytes);
    
    //allocate device memory
    float* d_A=0;
    cudaMalloc( (void**) &d_A, numBytes);
    
    //initialize memory
    for(unsigned int i = 0; i < N; i++){
        *( h_A + i) = 0;
    }
    print( h_A, N);
    
    //copy data from host to device
    cudaMemcpy( d_A, h_A, numBytes, cudaMemcpyHostToDevice);
    
    //execute the kernel
    DataPlan* plan = new DataPlan();
    plan->a = d_A;
    plan->increment = 100;
    plan->dataCount = N;

    /* execute */
    do_cuda_increment_gpu( plan); //plan will be stored in device global memory
    
    //copy result from device back to host
    cudaMemcpy( h_A, d_A, numBytes, cudaMemcpyDeviceToHost);
    print( h_A, N);
    //free device memory
    cudaFree( d_A);
    
    return 0;
}

