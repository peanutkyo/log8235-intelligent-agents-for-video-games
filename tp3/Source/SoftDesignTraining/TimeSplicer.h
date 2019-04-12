#pragma once
#include "CoreGlobals.h"

class TimeSplicer
{
public:
	static TimeSplicer& instance();
	TimeSplicer(const TimeSplicer&) = delete;
	TimeSplicer(TimeSplicer&&) = delete;
	TimeSplicer& operator=(const TimeSplicer&) = delete;
	TimeSplicer& operator=(TimeSplicer&&) = delete;

	void increaseCount();
	bool canExecute(uint64&);

private:
	TimeSplicer();
	~TimeSplicer();
	const double ALLOWED_TIME = 1.0 / 30.0 / 2.0;
	const double AVERAGE_EXECUTE_TIME = ALLOWED_TIME / 2.0;
	double budgetPerFrame;
	int deltaExecuteTime;
	int aiCount = 0;
};
