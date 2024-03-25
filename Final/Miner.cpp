#include "Miner.h"
#include "MinerStates.h"

#include <ImGui/Inc/imgui.h>

void Miner::Initialize()
{
    mLocation = Location::Home;
    mGoldCarried = 0;
    mMoneyInBank = 0;
    mThirst = 0;
    mFatigue = 0;

    mStateMachine.Initialize(this);
    mStateMachine.AddState<GoHomeAndSleepUntilRestedState>();
    mStateMachine.AddState<EnterMineAndDigForNuggetState>();
    mStateMachine.AddState<QuenchThirstState>();
    mStateMachine.AddState<VisitBanlAndDepositGoldState>();
    ChangeState(MinerState::GoHomeAndSleepUntilRested);
}

void Miner::Terminate()
{
    mStateMachine.Terminate();
}

void Miner::Update(float deltaTime)
{
    mStateMachine.Update(deltaTime);
}

void Miner::ChangeState(MinerState newState)
{
    mStateMachine.ChangeState((int)newState);
}

void Miner::DebugUI()
{
    mStateMachine.DebugUI();
    ImGui::Text("Status: Bank[%d] Gold[%d] Thirst[%d] Fatige[%d]", mMoneyInBank, mGoldCarried, mThirst, mFatigue);
}

Location Miner::GetLocation() const
{
    return mLocation;
}

bool Miner::IsThirsty() const
{
    return mThirst >= 5;
}

bool Miner::IsPocketFull() const
{
    return mGoldCarried >= 10;
}

bool Miner::IsWealthy() const
{
    return mMoneyInBank >= 100;
}

bool Miner::IsRested() const
{
    return mFatigue == 0;
}

void Miner::SetLocation(Location location)
{
    mLocation = location;
}

void Miner::IncreaseFatigue()
{
    ++mFatigue;
    ++mThirst;
}

void Miner::AddGoldCarried(int amount)
{
    mGoldCarried += amount;
}

void Miner::AddGoldToBank()
{
    mMoneyInBank += mGoldCarried;
    mGoldCarried = 0;
}

void Miner::ResetThirst()
{
    mThirst = 0;
}

void Miner::ResetFatigue()
{
    mFatigue = 0;
}
