#pragma once

#include "SteeringBehavior.h"

namespace AI
{
    class EvadeBehavior : public SteeringBehavior
    {
    public:
        X::Math::Vector2 Calculate(Agent& agent) override;
    };
}
