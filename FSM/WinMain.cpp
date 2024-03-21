#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>

#include "Miner.h"

Miner miner;

void GameInit()
{
	miner.Initialize();
}

bool GameLoop(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		miner.Update(deltaTime);
	}

	ImGui::Begin("FSM", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		miner.DebugUI();
	}
	ImGui::End();

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	miner.Terminate();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("FSM");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}