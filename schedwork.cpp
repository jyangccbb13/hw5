#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool canSched(size_t worker, size_t day, const vector<size_t>& shifts, const size_t maxShifts, const AvailabilityMatrix& avail);
bool scheduleDay(const AvailabilityMatrix& avail, size_t dayIndex, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& shifts, size_t workerIndex = 0);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t n = avail.size();
    size_t k = avail[0].size();

    vector<size_t> shifts(k, 0);
    sched.resize(n);

    return scheduleDay(avail, 0, dailyNeed, maxShifts, sched, shifts);

}

bool canSched(size_t worker, size_t day, const vector<size_t>& shifts, const size_t maxShifts, const AvailabilityMatrix& avail)
{
    return avail[day][worker] && shifts[worker] < maxShifts;
}

bool scheduleDay(const AvailabilityMatrix& avail, size_t dayIndex, 
                const size_t dailyNeed, const size_t maxShifts, 
                DailySchedule& sched, vector<size_t>& shifts, size_t workerIndex)
{
    size_t n = avail.size();
    bool s;
    
    if (workerIndex == avail[0].size())
    {
        return false;
    }

    if (dayIndex >= n)
    {
        return true;
    }
 
    if (!canSched(workerIndex, dayIndex, shifts, maxShifts, avail))
    {
        return scheduleDay(avail, dayIndex, dailyNeed, maxShifts, sched, shifts, workerIndex + 1);
    }
    
    shifts[workerIndex]++;
    sched[dayIndex].push_back(workerIndex);

    //  if(workersToday == dailyNeed)
    // {
    //     if(scheduleDay(avail, dayIndex + 1, dailyNeed, maxShifts, sched, shifts))
    //     {
    //         return true;
    //     }

    if (dailyNeed == sched[dayIndex].size())
    {
        s = scheduleDay(avail, dayIndex + 1, dailyNeed, maxShifts, sched, shifts);
    }
    else
    {
        s = scheduleDay(avail, dayIndex, dailyNeed, maxShifts, sched, shifts, workerIndex + 1);
    }

    if (!s)
    {
        shifts[workerIndex]--;
        sched[dayIndex].pop_back();
        return scheduleDay(avail, dayIndex, dailyNeed, maxShifts, sched, shifts, workerIndex + 1);
    }
    return true;
}


