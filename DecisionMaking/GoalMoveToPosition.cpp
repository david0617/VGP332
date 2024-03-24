#include "GoalMoveToPosition.h"

#include "GoalSeekToPosition.h"

GoalMoveToPosition::GoalMoveToPosition()
{

}

void GoalMoveToPosition::Activate(Raven& agent)
{
    mStatus = GoalMoveToPosition::Status::Active;
    RemoveAllSubGoal(agent);
    if (X::Math::DistanceSqr(agent.position, mDestination) > 10.0f)
    {
        GoalSeekToPosition* seek = AddSubGoal<GoalSeekToPosition>();
        seek->SetDestination(mDestination);
    }
}

GoalMoveToPosition::Status GoalMoveToPosition::Process(Raven& agent)
{
    ActivateIfInactive(agent);
    mStatus = ProcessSubGoal(agent);
    ReactiveIfFailed(agent);
    return mStatus;
}

void GoalMoveToPosition::Terminate(Raven& agent)
{
    RemoveAllSubGoal(agent);
}

void GoalMoveToPosition::SetDestination(const X::Math::Vector2& destination)
{
    mDestination = destination;
}
