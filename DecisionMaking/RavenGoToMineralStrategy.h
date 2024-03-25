#pragma once

#include <AI.h>

#include "Raven.h"

class RavenGoToMineralStrategy : public AI::Strategy<Raven>
{
public:
    void SetPerception(const AI::PerceptionModule* perception);
    float CalculateDesirability(Raven& agnet) const override;
    std::unique_ptr<AI::Goal<Raven>> CreateGoal() const override;

private:
    const AI::PerceptionModule* mPerception = nullptr;
};