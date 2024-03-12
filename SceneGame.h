#pragma once
#include "Scene.h"
#include "Player.h"

class SceneGame : public Scene
{
public:
	/// \enum PlayerSelected
	/// \brief The selected player
	enum PlayerSelected {
		WARRIOR,
		VALKYRIE,
		WIZARD,
		ELF
	};

private:
	int _actualMapID; ///< The actual map ID
	Player* _player; ///< The player

protected:
	PlayerSelected _playerSelected; ///< The selected player

public:
	SceneGame();
	~SceneGame();

	void Init() override;
	void ReInit() override;
	void Update() override;
	void Render() override;
};