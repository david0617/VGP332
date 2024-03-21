#include <XEngine.h> // <> for external includes, "" for internal includes
#include "AI.h"
#include <ImGui/Inc/imgui.h>

#include "SCV.h"

using namespace AI;

//--------------------------------------------------
AIWorld aiWorld;
SCV target(aiWorld);
std::vector<std::unique_ptr<SCV>> scvAgents;

X::Math::Vector2 destination = X::Math::Vector2::Zero();

bool showDebug = false;
bool useSeek = false;
bool useFlee = false;
bool useArrive = false;
bool useWander = false;
bool usePursuit = false;
bool useEvade = false;
bool useSeparation = false;
float wanderJitter = 5.0f;
float wanderRadius = 20.0f;
float wanderDistance = 50.0f;
float radius = 50.0f;

void SpawnAgent()
{
	auto& agent = scvAgents.emplace_back(std::make_unique<SCV>(aiWorld));
	agent->Load();

	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();
	agent->position = X::RandomVector2({ 100.0f, 100.0f },
		{ screenWidth - 100.0f, screenHeight - 100.0f });
	agent->destination = destination;
	agent->target = &target;
	agent->radius = radius;
	agent->ShowDebug(showDebug);
	agent->SetSeek(useSeek);
	agent->SetFlee(useFlee);
	agent->SetArrive(useArrive);
	agent->SetWander(useWander);
	agent->SetPursuit(usePursuit);
	agent->SetEvade(useEvade);
	agent->SetSeparation(useSeparation);
}

void KillAgent()
{
	if (!scvAgents.empty())
	{
		auto& agent = scvAgents.back();
		agent->Unload();
		agent.reset();
		scvAgents.pop_back();
	}
}

void GameInit()
{
	aiWorld.Initialize();
	target.Load();
	target.SetWander(true);
}

bool GameLoop(float deltaTime)
{
	ImGui::Begin("Steering", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		if (ImGui::Button("SpawnAgent"))
		{
			SpawnAgent();
		}
		if (ImGui::Button("killAgent"))
		{
			KillAgent();
		}
		if (ImGui::Checkbox("ShowDebug", &showDebug))
		{
			for (auto& agent : scvAgents)
			{
				agent->ShowDebug(showDebug);
			}
		}
		if (ImGui::Checkbox("Seek", &useSeek))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetSeek(useSeek);
			}
		}
		if (ImGui::Checkbox("Flee", &useFlee))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetFlee(useFlee);
			}
		}
		if (ImGui::Checkbox("Arrive", &useArrive))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetArrive(useArrive);
			}
		}
		if (ImGui::Checkbox("Wander", &useWander))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetWander(useWander);
			}
		}
		if (useWander)
		{
			if (ImGui::CollapsingHeader("WanderSettings", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::DragFloat("Jitter", &wanderJitter, 0.1f, 0.1f, 10.0f);
				ImGui::DragFloat("Radius", &wanderRadius, 0.1f, 0.1f, 100.0f);
				ImGui::DragFloat("Distance", &wanderDistance, 0.1f, 0.1f, 500.0f);
			}
		}
		if (ImGui::Checkbox("Pursuit", &usePursuit))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetPursuit(usePursuit);
			}
		}
		if (ImGui::Checkbox("Evade", &useEvade))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetEvade(useEvade);
			}
		}
		if (ImGui::Checkbox("Separate", &useSeparation))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetSeparation(useSeparation);
			}
		}
		if (useSeparation)
		{
			if (ImGui::DragFloat("Radius", &radius))
			{
				for (auto& agent : scvAgents)
				{
					agent->radius = radius;
				}
			}
		}
	}
	ImGui::End();

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const float mouseX = static_cast<float>(X::GetMouseScreenX());
		const float mouseY = static_cast<float>(X::GetMouseScreenY());
		destination = { mouseX, mouseY };
		for (auto& agent : scvAgents)
		{
			agent->destination = destination;
		}
	}

	aiWorld.Update();

	for (auto& agent : scvAgents)
	{
		EntityPtrs neighbors = aiWorld.GetEntitiesInRange({ agent->position, 500.0f }, 0);
		agent->neighbors.clear();
		for (auto& n : neighbors)
		{
			if (n != agent.get())
			{
				agent->neighbors.push_back(static_cast<Agent*>(n));
			}
		}
	}

	target.Update(deltaTime);
	for (auto& agent : scvAgents)
	{
		agent->Update(deltaTime);
	}

	target.Render();
	for (auto& agent : scvAgents)
	{
		agent->Render();
	}

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	target.Unload();
	for (auto& agent : scvAgents)
	{
		agent->Unload();
		agent.reset();
	}
	scvAgents.clear();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Steering");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}