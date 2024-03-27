#include "Menu.h"
#include "SceneManager.h"
#include "DoubleBuffer.h"

void Menu::Initialize()
{
}

void Menu::Progress()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		SceneManager::Get().Release();
		SceneManager::Get().LoadScene(STAGE);
	}
}

void Menu::Render()
{
	DoubleBuffer::Get().WriteBuffer(10, 10, "MENU", 14);
}

void Menu::Release()
{
}
