#include "SceneManager.h"
#include "DoubleBuffer.h"

int main()
{
	DoubleBuffer::Get().InitBuffer();
	SceneManager::Get().LoadScene(LOGO);

	while (true)
	{
		system("cls");

		SceneManager::Get().Progress();
		SceneManager::Get().Render();

		DoubleBuffer::Get().FlipBuffer();
		DoubleBuffer::Get().ClearBuffer();


		Sleep(50);
	}

	SceneManager::Get().Release();
	DoubleBuffer::Get().ReleaseBuffer();

	return 0;
}