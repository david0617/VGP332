#pragma once

#include <Ai.h>

enum class Location
{
    Home,
    Mine,
    Saloon,
    Bank
};

enum class MinerState
{
    GoHomeAndSleepUntilRested,
    EnterMineAndDigForNugget,
    QuenchThirst,
    VisitBanlAndDepositGold
};

class Miner
{
public:
    Miner() = default;
    void Initialize();
    void Terminate();
    void Update(float deltaTime);
    void ChangeState(MinerState newState);
    void DebugUI();

    // check miner status
    Location GetLocation() const;
    bool IsThirsty() const;
    bool IsPocketFull() const;
    bool IsWealthy() const;
    bool IsRested() const;

    // update status fuctions
    void SetLocation(Location location);
    void IncreaseFatigue();
    void AddGoldCarried(int amount);
    void AddGoldToBank();

    void ResetThirst();
    void ResetFatigue();

private:
    AI::StateMachine<Miner> mStateMachine;
    Location mLocation;
    int mGoldCarried;
    int mMoneyInBank;
    int mThirst;
    int mFatigue;
};