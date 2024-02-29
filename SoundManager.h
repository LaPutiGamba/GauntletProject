#pragma once
#include <map>
#include <vector>
#include <string>
#include <SDL_mixer.h>

/// \class SoundManager
/// \brief Handles the load and management of the sounds in the game
class SoundManager
{
private:
	std::vector<Mix_Chunk*> _soundsVector; ///< Vector that stores Sounds. Useful in render methods and sequential access 
	std::map<std::string, Sint32> _idMap; ///< Map that stores ID. Links strings to ID, Useful for check if sound is has been loaded previously 
	Uint32 _firstFreeSlot; ///< First free slot in the _soundsVector 
	static SoundManager* _pInstance; ///< Singleton instance 

public:
	~SoundManager() {}

	///	\brief Initialize the SoundManager
	///	\return True if all went well, false if something fails
	bool Init();

	///	\brief Deletes a sound from the SoundManager map
	///	\param Filepath to the sound
	void RemoveSound(const char* file);

	///	\brief Plays a sound
	///	\param Filepath to the sound
	///	\return ID of the sound
	Sint32 LoadAndGetSoundID(const char* file);

	///	\brief Gets the sound path given an ID sound
	///	\param ID of the sound
	///	\return Filepath to the sound
	std::string GetSoundPathByID(Sint32 ID);

	///	\brief Returns the Mix_Chunk of the sound
	///	\param ID of the soudn
	///	\return Mix_Chunk pointer to the sound
	Mix_Chunk* GetSoundByID(Sint32 ID);

	///	\brief Prints the path to loaded sounds
	void PrintLoadedSounds();

	///	\brief Plays a sound from the start
	///	\param ID of the sound
	///	\param Number of loops, -1 to loop infinitely.
	///	\returns Channel of the playing sound, or -1 if sound could not be played.
	int PlayFromStart(int ID, int loops = 0);

	///	\brief Plays a sound from a certain point
	///	\param ID of the sound
	///	\param Number of loops, -1 to loop infinitely.
	///	\param Channel to play the sound
	///	\returns Channel of the playing sound, or -1 if sound could not be played.
	int Play(int ID, int seconds, int loops = 0);

	///	\brief Pause a sound
	///	\param ID of the sound
	void Pause(int ID);

	///	\brief Resume a sound
	///	\param ID of the sound
	void Resume(int ID);

	///	\brief Stop a sound
	///	\param ID of the sound
	///	\return 0 if all went well, -1 if something fails
	int Stop(int ID);

	///	\brief Set the volume of the sound to a certain value
	///	\param Channel of the sound (-1 for all channels)
	///	\param Volume to set (0 to 128, or negative value to get the current volume of the channel)
	///	\return Previous volume. If the volume is -1, returns the current volume. If "channel" is -1, returns the average of all channels.
	int SetVolume(int channel, int volume);

	///	\brief Singleton instance getter
	///	\return Singleton instance
	static SoundManager* GetInstance() {
		if (_pInstance == NULL) {
			_pInstance = new SoundManager();
		}
		return _pInstance;
	}

protected:
	SoundManager();

private:
	///	\brief Loads from disc and adds a sound to the SoundManager
	///	\param Filepath to the graphic
	///	\return -1 if there's an error when loading
	Sint32 AddSound(const char* file);

	///	\brief Searches the first NULL in _soundsVector and updates _firstFreeSlot to store its position
	void UpdateFirstFreeSlotGraphic();
};