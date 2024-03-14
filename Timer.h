#pragma once
#include <SDL.h>
class Timer
{
public:
	enum TimeState {
		TIM_INITIALIZED,
		TIM_STARTED,
		TIM_PAUSED,
		TIM_STOPPED
	};

protected:
	int _tickStart; ///< Start time
	int _tickPause; ///< Pause time
	int _ticks; ///< Ticks
	TimeState _state; ///< State of the timer



public:
	Timer();
	~Timer() {}
	void Init(); ///< Initialize the timer
	void SetTimeCounter(int timer); ///< Set the timer
	void ResetTimer(); ///< Reset the timer
	void StopTimer(); ///< Stop the timer
	void StartTimer(); ///< Start the timer
	void PauseTimer(); ///< Pause the timer
	void ResumeTimer(); ///< Unpause the timer
	int GetTicks(); ///< Get the ticks
	void AddTime(int time); ///< Add time
	TimeState GetState() { return _state; }; ///< Get the state
	

};

