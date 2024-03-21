#pragma once

#include "SteeringBehavior.h"

namespace AI
{
    class PursuitBehavior : public SteeringBehavior
    {
    public:
        X::Math::Vector2 Calculate(Agent& agent) override;
    };
}