#pragma once

#include <AI.h>
#include "Player.h"

class RestingState : public AI::State<Player>
{
public:
    void Enter(Player& agent) override;
    void Update(Player& agent, float deltaTime) override;
    void Exit(Player& agent) override;
    void DebugUI() override;
};
class PlayingGameState : public AI::State<Player>
{
public:
    void Enter(Player& agent) override;
    void Update(Player& agent, float deltaTime) override;
    void Exit(Player& agent) override;
    void DebugUI() override;
};
class QuenchThirstState : public AI::State<Player>
{
public:
    void Enter(Player& agent) override;
    void Update(Player& agent, float deltaTime) override;
    void Exit(Player& agent) override;
    void DebugUI() override;
};
class WorkingState : public AI::State<Player>
{
public:
    void Enter(Player& agent) override;
    void Update(Player& agent, float deltaTime) override;
    void Exit(Player& agent) override;
    void DebugUI() override;
};
class ShoppingState : public AI::State<Player>
{
public:
    void Enter(Player& agent) override;
    void Update(Player& agent, float deltaTime) override;
    void Exit(Player& agent) override;
    void DebugUI() override;
}; 
class WhatToDoState : public AI::State<Player>
{
public:
    void Enter(Player& agent) override;
    void Update(Player& agent, float deltaTime) override;
    void Exit(Player& agent) override;
    void DebugUI() override;
};