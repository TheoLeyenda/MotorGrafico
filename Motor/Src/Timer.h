#ifndef TIMER_H
#define TIMER_H

#include <time.h>

const clock_t _beign_time = clock();

class Timer
{
private:
	float timePassedOnSeconds;
public:
	Timer();
	~Timer();
	void CalcGlobalTime();
	double GetGlobalTime();
};
#endif // !TIMER_H