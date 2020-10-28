#include "Timer.h"

//=================================
Timer::Timer() { timePassedOnSeconds = 0; }
//=================================
Timer::~Timer(){}
//=================================
void Timer::CalcGlobalTime()
{
	timePassedOnSeconds = (float)((clock () - _beign_time) / CLOCKS_PER_SEC);
}
//=================================
double Timer::GetGlobalTime()
{
	return timePassedOnSeconds;
}
//=================================