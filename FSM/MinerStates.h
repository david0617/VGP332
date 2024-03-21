#pragma once

#include <AI.h>
#include "Miner.h"

class GoHomeAndSleepUntilRestedState : public AI::State<Miner>
{
public:
    void Enter(Miner& agent) override;
    void Update(Miner& agent, float deltaTime) override;
    void Exit(Miner& agent) override;
    void DebugUI() override;
};
class EnterMineAndDigForNuggetState : public AI::State<Miner>
{
public:
    void Enter(Miner& agent) override;
    void Update(Miner& agent, float deltaTime) override;
    void Exit(Miner& agent) override;
    void DebugUI() override;
};
class QuenchThirstState : public AI::State<Miner>
{
public:
    void Enter(Miner& agent) override;
    void Update(Miner& agent, float deltaTime) override;
    void Exit(Miner& agent) override;
    void DebugUI() override;
};
class VisitBanlAndDepositGoldState : public AI::State<Miner>
{
public:
    void Enter(Miner& agent) override;
    void Update(Miner& agent, float deltaTime) override;
    void Exit(Miner& agent) override;
    void DebugUI() override;
};