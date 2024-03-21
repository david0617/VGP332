#include "Player.h"
#include "PlayerStates.h"

#include <ImGui/Inc/imgui.h>

void Player::Initialize()
{
    mLocation = Location::Home;
    mGames = 0;
    mMoney = 0;
    mThirst = 0;
    mFatigue = 0;

    mStateMachine.Initialize(this);
    mStateMachine.AddState<RestingState>();
    mStateMachine.AddState<PlayingGameState>();
    mStateMachine.AddState<QuenchThirstState>();
    mStateMachine.AddState<WorkingState>();
    mStateMachine.AddState<ShoppingState>();
    mStateMachine.AddState<WhatToDoState>();
    ChangeState(PlayerState::WhatToDo);
}

void Player::Terminate()
{
    mStateMachine.Terminate();
}

void Player::Update(float deltaTime)
{
    mStateMachine.Update(deltaTime);
}

void Player::ChangeState(PlayerState newState)
{
    mStateMachine.ChangeState((int)newState);
}

void Player::DebugUI()
{
    mStateMachine.DebugUI();
    ImGui::Text("Status: Game[%d] Money[%d] Thirst[%d] Fatige[%d]", mGames, mMoney, mThirst, mFatigue);
}

Location Player::GetLocation() const
{
    return mLocation;
}

bool Player::IsThirsty()
{
    return mThirst >= 20;
}

bool Player::CanPlay()
{
    return mGames >= 1;
}

bool Player::IsWealthy()
{
    return mMoney >= 100;
}


bool Player::IsRested()
{
    return mFatigue >= 40;
}

void Player::SetLocation(Location location)
{
    mLocation = location;
}

void Player::IncreaseFatigue()
{
    if (mGames > 0)
    {
        ++mFatigue;
    }
    else
    {
        mFatigue += 2;
    }
    ++mThirst;
}

void Player::AddMoney()
{
    mMoney += 5;
}

void Player::AddGames()
{
    mGames = 5;
    mMoney = 0;
}

void Player::PlayGame()
{
    --mGames;
}

void Player::ResetThirst()
{
    mThirst = 0;
}

void Player::ResetFatigue()
{
    mFatigue = 0;
}
