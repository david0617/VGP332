#include "GoalSeekToPosition.h"

GoalSeekToPosition::GoalSeekToPosition()
{

}

void GoalSeekToPosition::Activate(Raven& agent)
{
    mStatus = GoalSeekToPosition::Status::Active;
    agent.SetSeek(true);
    agent.destination = mDestination;
}

GoalSeekToPosition::Status GoalSeekToPosition::Process(Raven& agent)
{
    ActivateIfInactive(agent);
    if (X::Math::DistanceSqr(agent.position, mDestination) < 10.0f)
    {
        mStatus = GoalSeekToPosition::Status::Completed;
    }
    return mStatus;
}

void GoalSeekToPosition::Terminate(Raven& agent)
{
    agent.SetSeek(false);
}

void GoalSeekToPosition::SetDestination(const X::Math::Vector2& destination)
{
    mDestination = destination;
}
