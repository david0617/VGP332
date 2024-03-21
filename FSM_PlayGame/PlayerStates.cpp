#include "PlayerStates.h"
#include <ImGui/Inc/imgui.h>

void RestingState::Enter(Player& agent)
{
    agent.SetLocation(Location::Bed);
}

void RestingState::Update(Player& agent, float deltaTime)
{
    agent.ResetFatigue();
    if (!agent.IsRested())
    {
        agent.ChangeState(PlayerState::WhatToDo);
    }
    else
    {
        // we are done
    }
}

void RestingState::Exit(Player& agent)
{

}

void RestingState::DebugUI()
{
    ImGui::Text("RestingState: Player is resting");
}

void PlayingGameState::Enter(Player& agent)
{
    agent.SetLocation(Location::PC);
}

void PlayingGameState::Update(Player& agent, float deltaTime)
{
    agent.IncreaseFatigue();
    if (agent.IsThirsty())
    {
        agent.PlayGame();
        agent.ChangeState(PlayerState::QuenchThirst);
    }
    else if (agent.IsRested())
    {
        agent.PlayGame();
        agent.ChangeState(PlayerState::Resting);
    }
    else if(!agent.CanPlay())
    {
        agent.ChangeState(PlayerState::Working);
    }
}

void PlayingGameState::Exit(Player& agent)
{

}

void PlayingGameState::DebugUI()
{
    ImGui::Text("PlayingGameState: Player is playing game");
}

void QuenchThirstState::Enter(Player& agent)
{
    agent.SetLocation(Location::Sink);
}

void QuenchThirstState::Update(Player& agent, float deltaTime)
{
    agent.ResetThirst();
    if (!agent.IsThirsty())
    {
        agent.ChangeState(PlayerState::WhatToDo);
    }
}

void QuenchThirstState::Exit(Player& agent)
{

}

void QuenchThirstState::DebugUI()
{
    ImGui::Text("QuenchThirstState: Player is drinking");
}

void WorkingState::Enter(Player& agent)
{
    agent.SetLocation(Location::Work);
}

void WorkingState::Update(Player& agent, float deltaTime)
{
    agent.AddMoney();
    agent.IncreaseFatigue();
    if (agent.IsThirsty())
    {
        agent.ChangeState(PlayerState::QuenchThirst);
    }
    else if (agent.IsRested())
    {
        agent.ChangeState(PlayerState::Resting);
    }
    else if (agent.IsWealthy())
    {
        agent.ChangeState(PlayerState::Shopping);
    }
}

void WorkingState::Exit(Player& agent)
{

}

void WorkingState::DebugUI()
{
    ImGui::Text("WorkingState: Player is Working");
}

void ShoppingState::Enter(Player& agent)
{
    agent.SetLocation(Location::Shop);
}

void ShoppingState::Update(Player& agent, float deltaTime)
{
    agent.AddGames();
    if (agent.CanPlay())
    {
        agent.ChangeState(PlayerState::PlayingGame);
    }
}

void ShoppingState::Exit(Player& agent)
{
}

void ShoppingState::DebugUI()
{
    ImGui::Text("ShoppingState: Player is shoping");
}

void WhatToDoState::Enter(Player& agent)
{
    agent.SetLocation(Location::Home);
}

void WhatToDoState::Update(Player& agent, float deltaTime)
{
    if (agent.IsRested())
    {
        agent.ChangeState(PlayerState::Resting);
    }
    else if (agent.IsThirsty())
    {
        agent.ChangeState(PlayerState::QuenchThirst);
    }
    else if (agent.IsWealthy())
    {
        agent.ChangeState(PlayerState::Shopping);
    }
    else if (agent.CanPlay())
    {
        agent.ChangeState(PlayerState::PlayingGame);
    }
    else
    {
        agent.ChangeState(PlayerState::Working);
    }
}

void WhatToDoState::Exit(Player& agent)
{
}

void WhatToDoState::DebugUI()
{
    ImGui::Text("WhatToDoState: Player...");
}
