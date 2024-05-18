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
	class Player* _pPlayer; ///< The player
	PlayerSelected _playerSelected; ///< The selected player
	int _score; ///< The player's score
	int _life; ///< The player's life
	int _kills; ///< The player's kills
	bool _bGameOver; ///< The game over flag

	static GameState* _pInstance; ///< Singleton instance

protected:
	GameState();

public:
	~GameState() {}
	
	void SetGameOver(const bool bGameOver) { _bGameOver = bGameOver; }
	bool IsGameOver() const { return _bGameOver; }
	void SetPlayerSelected(const PlayerSelected player) { _playerSelected = player; }
	
	void SetPlayer(class Player* player) { _pPlayer = player; }
	class Player* GetPlayer() const { return _pPlayer; }

	PlayerSelected GetPlayerSelected() const { return _playerSelected; }
	
	void AddScore(const int score) { _score += score; }
	int GetScore() const { return _score; }
	
	void AddLife(const int life) { _life += life; }
	void SetLife(const int life) { _life = life; }
	int GetLife() const { return _life; }

	void AddKills() { _kills++; }
	int GetKills() const { return _kills; }

	static GameState* GetInstance() {
		if (_pInstance == nullptr)
			_pInstance = new GameState();
		return _pInstance;
	}
};

