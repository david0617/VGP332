#include "Precompiled.h"
#include "SteeringModule.h"
#include "Agent.h"

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
    
    float totalForceSqr = X::Math::MagnitudeSqr(totalForce);
    if (totalForceSqr > mAgent.maxSpeed * mAgent.maxSpeed)
    {
        totalForce = X::Math::Normalize(totalForce) * mAgent.maxSpeed;
    }
    else if (totalForceSqr <= 1.0f)
    {
        totalForce = -mAgent.velocity;
    }

    return totalForce;
}
