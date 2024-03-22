#pragma once

#include <AI.h>

#include "TypeId.h"

class VisualSensor : public AI::Sensor
{
public:
    virtual void Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltaTame) override;

    AgentType targetType = AgentType::Invalid;
    float viewRange = 0.0f;
    float viewHalfAngle = 0.0f;
};