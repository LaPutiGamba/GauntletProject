#pragma once
#include "Scene.h"
class SceneGameOver : public Scene
{
	int _ripID;
public:

	void Init() override;

	void ReInit() override;
	void Update() override;
	void Render() override;
};

