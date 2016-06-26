/* 
 * File:   common.h
 * Author: peter 
 *
 * Created on March 26, 2013, 2:54 PM
 */
#include <curand_kernel.h>
#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct{
    //data count for this plan
    int dataCount;
    //Host-side data source
    float* a;
    float increment;
} DataPlan;

#define blockSize 4

//host side interface to increment_gpu
void do_cuda_increment_gpu(DataPlan* plan); 
#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

