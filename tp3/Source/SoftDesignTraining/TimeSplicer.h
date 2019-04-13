#pragma once
#include "CoreGlobals.h"

class TimeSplicer
{
public:
	TimeSplicer();

	void increaseAiCount();
	bool canExecute(uint64&);

private:
	const double TOTAL_BUDGET = 1.0 / 30.0 / 2.0; // we're only using half the time corresponding to 30 FPS
	const double AVG_EXEC_TIME = TOTAL_BUDGET / 2.0; // average execution time should be around half of the previous value
	double budgetPerFrame;
	int deltaExecuteTime;
	int aiCount = 0;
};
