#include "Precompiled.h"
#include "GroupBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 SeparationBehavior::Calculate(Agent& agent)
{
    const float forceMultiplier = 5.0f;
    X::Math::Vector2 separationForce = X::Math::Vector2::Zero();
    for (auto& n : agent.neighbors)
    {
        if (n != agent.target)
        {
            X::Math::Vector2 dirToNeighbor = n->position - agent.position;
            float distance = X::Math::Magnitude(dirToNeighbor);
            float overlapDistance = (n->radius + agent.radius) - distance;
            if (overlapDistance > 0.0f)
            {
                dirToNeighbor /= distance;
                if (X::Math::Dot(dirToNeighbor, agent.heading) > 0.0f)
                {
                    float desiredSpeed = (overlapDistance / agent.radius) * forceMultiplier * agent.maxSpeed;
                    desiredSpeed = X::Math::Min(desiredSpeed, agent.maxSpeed);
                    separationForce += (-dirToNeighbor * desiredSpeed);
                }
            }
        }
    }
    separationForce = separationForce - agent.velocity;
    if (IsDebug())
    {
        X::DrawScreenCircle(agent.position, agent.radius, X::Colors::Honeydew);
    }
    return separationForce;
}
