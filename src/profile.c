
#include "profile.h"

void profile_start(profile_t *profile)
{
    gettimeofday(&profile->tstart, 0);
}

void profile_stop(profile_t *profile)
{
    gettimeofday(&profile->tstop, 0);
}

double profile_elapse(profile_t *profile)
{
    const long secs = profile->tstop.tv_sec - profile->tstart.tv_sec;
    const long msecs = profile->tstop.tv_usec - profile->tstart.tv_usec;
    return fabs((double)(secs + msecs) * 1e-6);
}