#include "GameState.h"

GameState* GameState::_pInstance = nullptr;

GameState::GameState()
{
	_playerSelected = PL_WARRIOR;
	_score = 0;
	_life = 0;
	_kills = 0;
	_bGameOver = false;
}
