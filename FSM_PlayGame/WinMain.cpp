#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>

#include "Player.h"

Player player;

void GameInit()
{
	player.Initialize();
}

bool GameLoop(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		player.Update(deltaTime);
	}

	ImGui::Begin("FSM", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		player.DebugUI();
	}
	ImGui::End();

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	player.Terminate();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("FSM_PlayGame");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}