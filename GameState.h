#pragma once

/// \class GameState
///	\brief Class for the game state
class GameState
{
public:
    /// \enum PlayerSelected
    /// \brief The selected player
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

    /// \brief Set the game over flag
    /// \param bGameOver The game over flag
	void SetGameOver(const bool bGameOver) { _bGameOver = bGameOver; }
    /// \brief Get the game over flag
    /// \return The game over flag
	bool IsGameOver() const { return _bGameOver; }

    /// \brief Set the player selected
    /// \param player The player selected
	void SetPlayerSelected(const PlayerSelected player) { _playerSelected = player; }
    /// \brief Get the player selected
    /// \return The player selected
	PlayerSelected GetPlayerSelected() const { return _playerSelected; }

    /// \brief Set the player
    /// \param player The player
	void SetPlayer(class Player* player) { _pPlayer = player; }
    /// \brief Get the player
    /// \return The player
	Player* GetPlayer() const { return _pPlayer; }

    /// \brief Add score to the player
    /// \param score The score to add
	void AddScore(const int score) { _score += score; }
    /// \brief Set the score of the player
    ///	\param score The score
    void SetScore(const int score) { _score = score; }
    /// \brief Get the score of the player
    ///	\return The score
	int GetScore() const { return _score; }

    /// \brief Add life to the player
    /// \param life The life to add
	void AddLife(const int life) { _life += life; }
    /// \brief Set the life of the player
    /// \param life The life
	void SetLife(const int life) { _life = life; }
    /// \brief Get the life of the player
    /// \return The life
	int GetLife() const { return _life; }

    /// \brief Add kills to the player
    /// \param kills The kills to add
	void AddKills() { _kills++; }
    /// \brief Set the kills of the player
    /// \param kills The kills
	int GetKills() const { return _kills; }

    /// \brief Singleton instance getter
    /// \return Singleton instance
	static GameState* GetInstance() {
		if (_pInstance == nullptr)
			_pInstance = new GameState();
		return _pInstance;
	}
};

