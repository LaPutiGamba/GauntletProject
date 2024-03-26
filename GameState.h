#pragma once

class GameState
{
public:
	enum PlayerSelected {
		PL_WARRIOR,
		PL_VALKYRIE,
		PL_WIZARD,
		PL_ELF
	};
private:
	static GameState* _pInstance; ///< Singleton instance
	PlayerSelected _playerSelected; ///< The selected player
protected:
	GameState();

public:
	~GameState() {}
	static GameState* GetInstance() {
		if (_pInstance == nullptr)
			_pInstance = new GameState();
		return _pInstance;
	}
	void SetPlayerSelected(PlayerSelected player) { _playerSelected = player; }
	PlayerSelected GetPlayerSelected() { return _playerSelected; }
};

