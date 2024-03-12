#include "TimerManager.h"

TimerManager* TimerManager::_pInstance = nullptr;

void TimerManager::Init()
{
	_timer = 0;
	_timeCounter = 0;
	_started = false;
	_paused = false;
	_deltaTime = 0;
}

void TimerManager::SetTimeCounter(int timer)
{
	_timeCounter = timer;
}

int TimerManager::GetTimer()
{
	return _timer;
}

void TimerManager::ResetTimer()
{
	_timer = 0;
}

void TimerManager::StopTimer()
{
	_timer = 0;
	_started = false;
}

void TimerManager::StartTimer()
{
	_started = true;
}

void TimerManager::PauseTimer()
{
	_paused = true;
}

void TimerManager::UnpauseTimer()
{
	_paused = false;
}

int TimerManager::GetTicks()
{
	return _timer;
}

int TimerManager::GetDeltaTime()
{
	return _deltaTime;
}

bool TimerManager::CheckTimer()
{
	if (_timer >= _timeCounter) 
		return true;
	else
		return false;
}

void TimerManager::Update()
{
	if (_started && !_paused)
		_timer++;
}
