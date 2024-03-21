#include "Precompiled.h"
#include "SteeringModule.h"

using namespace AI;

AI::SteeringModule::SteeringModule(Agent& agent)
    : mAgent(agent)
{
}

X::Math::Vector2 AI::SteeringModule::Calculate()
{
    X::Math::Vector2 totalForce = X::Math::Vector2::Zero();
    for (auto& behavior : mBehaviors)
    {
        if (behavior->IsActive())
        {
            totalForce += behavior->Calculate(mAgent) * behavior->GetWeight();
        }
    }

    return totalForce;
}
