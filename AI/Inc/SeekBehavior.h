#pragma once

#include "SteeringBehavior.h"

namespace AI
{
    class SeekBehavior : public SteeringBehavior
    {
    public:
        X::Math::Vector2 Calculate(Agent& agent) override;
    };

    class FleeBehavior : public SteeringBehavior
    {
    public:
        X::Math::Vector2 Calculate(Agent& agent) override;

        float panicDistance = 100.0f;
    };
    class ArriveBehavior : public SteeringBehavior
    {
    public:
        enum class Deceleration
        {
            Fast,
            Normal,
            Slow
        };

        X::Math::Vector2 Calculate(Agent& agent) override;

        Deceleration deceleration = Deceleration::Normal;
    };
}