#pragma once
#include "Scene.h"

class SceneGame : public Scene
{
public:
	enum PlayerSelected {
		WARRIOR,
		VALKYRIE,
		WIZARD,
		ELF
	};

protected:
	PlayerSelected _playerSelected;

public:
	SceneGame();
	~SceneGame();

	void Init() override {};
	void ReInit() override {};
	void Update() override;
	void Render() override;
};