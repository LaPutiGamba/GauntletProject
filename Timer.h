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

	/// \brief Initialize the timer
	void Init(); 

	/// \brief Set the time counter
	/// \param timer Time counter
	void SetTimeCounter(int timer);

	/// \brief Reset the timer
	void ResetTimer();

	/// \brief Stop the timer
	void StopTimer();

	/// \brief Start the timer
	void StartTimer();

	/// \brief Pause the timer
	void PauseTimer();

	/// \brief Resume the timer
	void ResumeTimer();

	/// \brief Get the time counter
	int GetTicks();

	/// \brief Add time to the timer
	void AddTime(int time);

	/// \brief Get the state of the timer
	TimeState GetState() { return _state; };
	

};

