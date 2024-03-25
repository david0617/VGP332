#include "GoalHarvestMineral.h"

GoalHarvestMineral::GoalHarvestMineral()
{
}

void GoalHarvestMineral::Activate(Raven& agent)
{
    mStartTime = X::GetTime();
}

GoalHarvestMineral::Status GoalHarvestMineral::Process(Raven& agent)
{
    return Status();
}

void GoalHarvestMineral::Terminate(Raven& agent)
{

}
