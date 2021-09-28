/**
 * @file profile.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief time profile
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_PROFILE_
#define _SURFACES_PROFILE_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

typedef struct profile_s
{
    struct timeval tstart;
    struct timeval tstop;
} profile_t;

void profile_start(profile_t *profile);
void profile_stop(profile_t *profile);
double profile_elapse(profile_t *profile);

#endif // _SURFACES_PROFILE_