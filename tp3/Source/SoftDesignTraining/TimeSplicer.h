#pragma once
#include "CoreGlobals.h"

class TimeSplicer
{
public:
	TimeSplicer();

	void increaseAiCount();
	bool canExecute(uint64&);

private:
	const double ALLOWED_TIME = 1.0 / 30.0 / 2.0;
	const double AVERAGE_EXECUTE_TIME = ALLOWED_TIME / 2.0;
	double budgetPerFrame;
	int deltaExecuteTime;
	int aiCount = 0;
};
