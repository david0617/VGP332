#pragma once

#include <Ai.h>

enum class Location
{
    Bed,
    PC,
    Sink,
    Work,
    Shop,
    Home
};

enum class PlayerState
{
    Resting,
    PlayingGame,
    QuenchThirst,
    Working,
    Shopping,
    WhatToDo
};

class Player
{
public:
    Player() = default;
    void Initialize();
    void Terminate();
    void Update(float deltaTime);
    void ChangeState(PlayerState newState);
    void DebugUI();

    // check miner status
    Location GetLocation() const;
    bool IsThirsty();
    bool CanPlay();
    bool IsWealthy();
    bool IsRested();

    // update status fuctions
    void SetLocation(Location location);
    void IncreaseFatigue();
    void AddMoney();
    void AddGames();
    void PlayGame();

    void ResetThirst();
    void ResetFatigue();

private:
    AI::StateMachine<Player> mStateMachine;
    Location mLocation;
    int mGames;
    int mMoney;
    int mThirst;
    int mFatigue;
};