#pragma once
#include "Scene.h"

class SceneMain : public Scene
{
public:
	SceneMain();
	~SceneMain();

	void Init() override {};
	void ReInit() override {};
	void Update() override {};
	void Render() override {};
};