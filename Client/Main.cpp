#include <Windows.h>
#include "State/StatePlay.hpp"

#ifdef _DEBUG
int main(int argc, char *argv[])
#else
int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
#endif
{
	try
	{
		Antumbra::Window window;
		Antumbra::StatePtr currentState(new Antumbra::StatePlay(window));

		double thisTime = 0.0;
		double lastTime = glfwGetTime();
		double frameTime = 0.0;
		double deltaTime = 0.020; // 50 ticks/sec
		double accumulator = 0.0;

		while(currentState)
		{
			thisTime = glfwGetTime();
			frameTime = thisTime - lastTime;
			lastTime = thisTime;

			accumulator += frameTime;

			while(accumulator >= deltaTime)
			{
				currentState->Update(deltaTime);
				accumulator -= deltaTime;
			}

			currentState->Render(accumulator / deltaTime);
			currentState = currentState->GetNextState(currentState);
		}
	}
	catch(std::exception e)
	{
		MessageBox(nullptr, e.what(), "Error!", MB_OK | MB_ICONERROR);
	}

	return 0;
}