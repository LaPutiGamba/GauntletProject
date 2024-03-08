#pragma once
#include "Scene.h"

/// \class SceneMain
/// \brief Main Scene
class SceneMain : public Scene
{
private:
	int _menuID;

public:
	SceneMain();
	~SceneMain();

	/// \brief Init
	void Init() override;

	/// \brief ReInit
	void ReInit() override;

	/// \brief Update
	void Update() override;

	/// \brief Render
	void Render() override;
};