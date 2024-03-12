#pragma once
class TimerManager
{
private:
	int _startTicks; ///< Start ticks
	int _pausedTicks; ///< Paused ticks
	bool _paused; ///< Paused flag
	bool _started; ///< Started flag
	int _timer; ///< Timer
	int _deltaTime; ///< Delta time
	int _timeCounter; ///< Time counter

	static TimerManager* _pInstance; ///< Singleton instance
	TimerManager(void);	


	public:
	~TimerManager(void) {}
	void Init(); ///< Initialize the timer
	void SetTimeCounter(int timer); ///< Set the timer
	int GetTimer(); ///< Get the timer
	void ResetTimer(); ///< Reset the timer
	void StopTimer(); ///< Stop the timer
	void StartTimer(); ///< Start the timer
	void PauseTimer(); ///< Pause the timer
	void UnpauseTimer(); ///< Unpause the timer
	int GetTicks(); ///< Get the ticks
	int GetDeltaTime(); ///< Get the delta time
	bool CheckTimer(); ///< Check the timer
	void Update(); ///< Update the timer
	static TimerManager* GetInstance() {
		if (_pInstance == nullptr)
			_pInstance = new TimerManager();
		return _pInstance;
	}
	

};

