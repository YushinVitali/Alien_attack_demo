/// @file sound_manager.hpp
/// @brief Description of the sound system.
#pragma once

#ifndef __SOUND_MANAGER_HPP__
#define __SOUND_MANAGER_HPP__


#include <string>
#include <unordered_map>

#include <SDL_mixer.h>


namespace Engine {

/// @brief Types of loaded sounds.
enum class SoundType {
	Music	= 0,
	Sfx		= 1
}; // enum class SoundType


/// @brief Sound System.
class SoundManager {
public:
	~SoundManager();

	static SoundManager* Instance();

	bool Load(const std::string& filename,
			  const std::string& id,
			  SoundType type);

	void PlaySound(const std::string& id, int32_t loop);
	void PlayMusic(const std::string& id, int32_t loop);

	void Clean();

private:
	SoundManager();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	bool LoadSoundFile(const std::string& filename,
					   const std::string& id);
	bool LoadMusicFile(const std::string& filename,
					   const std::string& id);

private:
	static SoundManager* m_instance;

	std::unordered_map<std::string, Mix_Chunk*> m_sfxs;
	std::unordered_map<std::string, Mix_Music*> m_music;

	int8_t m_volumeMusic{ 50 };
}; // class SoundManager

} // namespace Engine


#endif // !defined(__SOUND_MANAGER_HPP__)
