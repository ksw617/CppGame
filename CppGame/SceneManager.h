#pragma once
#include "Singleton.h"
#include "Header.h"

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
private:
	class Scene* currentScene = nullptr;
public:
	void LoadScene(SCENE_ID id);
	void Progress();
	void Render();
	void Release();


};

