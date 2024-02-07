#pragma once
#include "Scene.h"

class SceneOptions : public Scene
{
public:
	SceneOptions();
	~SceneOptions();

	void Init() override {};
	void ReInit() override {};
	void Update() override {};
	void Render() override {};
};