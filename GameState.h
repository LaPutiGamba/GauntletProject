#pragma once

class GameState
{
public:
	enum PlayerSelected {
		PL_WARRIOR,
		PL_VALKYRIE,
		PL_WIZARD,
		PL_ELF,
		EN_GHOST,
		EN_DOGGY
	};
private:
	static GameState* _pInstance; ///< Singleton instance
	PlayerSelected _playerSelected; ///< The selected player
	int _score; ///< The player's score
	int _life; ///< The player's life
	int _kills; ///< The player's kills
	bool _bGameOver; ///< The game over flag
protected:
	GameState();

public:
	~GameState() {}
	static GameState* GetInstance() {
		if (_pInstance == nullptr)
			_pInstance = new GameState();
		return _pInstance;
	}
	void SetGameOver(bool bGameOver) { _bGameOver = bGameOver; }
	bool IsGameOver() { return _bGameOver; }
	void SetPlayerSelected(PlayerSelected player) { _playerSelected = player; }
	PlayerSelected GetPlayerSelected() { return _playerSelected; }
	void AddScore(int score) { _score += score; }
	int GetScore() { return _score; }
	void AddLife(int life) { _life += life; }
	void SetLife(int life) { _life = life; }
	int GetLife() { return _life; }
	void AddKills() { _kills++; }
	int GetKills() { return _kills; }
};

