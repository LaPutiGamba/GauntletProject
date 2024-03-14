#pragma once
//Child class of Entity
#include "Entity.h"
#include "InputManager.h"
#include "Timer.h"

class Player : public Entity
{
public:
	enum PlayerType
	{
		PL_WARRIOR,
		PL_VALKYRIE,
		PL_WIZARD,
		PL_ELF
	};

private:
	int _life; ///Player's life
	int _score; ///Player's score
	float _endurance; ///Player's endurance
	float _strength; ///Player's strength
	float _speed; ///Player's speed
	float _shootCooldown; ///Player's shoot cooldown
	State _state; ///Player's state
	State _lastNonIdleState; ///Player's last non idle state
	static Player* _pInstance; ///Player's instance
	int _player; ///Player's type
	Timer* _shootTimer; ///Player's shoot timer
	Timer* _frameTimer; ///Player's frame timer
	Player(void) {}


public:
	~Player(void) {}
	void Init();
	void LoadCharacter();
	void Update();
	void Render();
	static Player* GetInstance() {
		if (_pInstance == NULL)
			_pInstance = new Player();
		return _pInstance;
	}
	void SetState(State state);
	State GetState() { return _state; }
	void Shoot();

	protected:


};
