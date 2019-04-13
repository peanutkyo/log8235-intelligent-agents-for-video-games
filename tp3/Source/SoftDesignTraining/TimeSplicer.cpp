#include "SoftDesignTraining.h"
#include "TimeSplicer.h"
#include "Engine.h"

TimeSplicer::TimeSplicer()
{
	budgetPerFrame = TOTAL_BUDGET / MAX_EXEC_TIME;
}

void TimeSplicer::increaseAiCount()
{
	aiCount++;

	deltaExecuteTime = (int) ceil(aiCount / budgetPerFrame);

	UE_LOG(LogTemp, Display, TEXT("execute every: %i"), deltaExecuteTime)
}

bool TimeSplicer::canExecute(uint64& lastFrameExecuted)
{
	uint64 deltaFrame = GFrameCounter - lastFrameExecuted;

	UE_LOG(LogTemp, Display, TEXT("deltaFrame: %i"), deltaFrame)

	bool canExecute = deltaFrame >= deltaExecuteTime;

	if (canExecute)
	{
		lastFrameExecuted = GFrameCounter;
	}
	else 
	{
		UE_LOG(LogTemp, Display, TEXT("can't execute now"))
	}
	return canExecute;
}
