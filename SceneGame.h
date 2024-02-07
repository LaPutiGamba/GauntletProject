#pragma once
#include "Scene.h"

class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();

	void Init() override {};
	void ReInit() override {};
	void Update() override {};
	void Render() override {};
};