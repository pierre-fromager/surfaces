/**
 * @file profile.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief time profiler
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_PROFILE_
#define _SURFACES_PROFILE_

#include <math.h>
#include <sys/time.h>

/**
 * @brief profile struct type
 * 
 */
typedef struct profile_s
{
    struct timeval tstart;
    struct timeval tstop;
} profile_t;

/**
 * @brief start profiling
 * 
 * @param profile 
 */
void profile_start(profile_t *profile);

/**
 * @brief stop profiling
 * 
 * @param profile 
 */
void profile_stop(profile_t *profile);

/**
 * @brief calculate elapse between start and stop
 * 
 * @param profile 
 * @return double 
 */
double profile_elapse(profile_t *profile);

#endif // _SURFACES_PROFILE_