#pragma once
#include "CoreGlobals.h"

class TimeSplicer
{
public:
	TimeSplicer();

	void increaseAiCount();
	bool canExecute(uint64&);

private:
	const double TOTAL_BUDGET = 1.0 / 30.0 / 5.0; // converts 30 fps into seconds and only uses a fifth of it
	const double MAX_EXEC_TIME = 0.003;
	double budgetPerFrame;
	int deltaExecuteTime;
	int aiCount = 0;
};
