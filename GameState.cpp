#include "GameState.h"
#include "Player.h"

GameState* GameState::_pInstance = nullptr;

GameState::GameState() {
	_pPlayer = Player::GetInstance();

	_playerSelected = PL_WARRIOR;
	_score = 0;
	_life = 0;
	_kills = 0;
	_bGameOver = false;
}
