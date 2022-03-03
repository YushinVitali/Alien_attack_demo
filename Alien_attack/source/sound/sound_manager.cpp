/// @file sound_manager.cpp
/// @brief Implementation of the sound system.
#include <sound/sound_manager.hpp>

#include <functional>

#include <logger.hpp>


namespace Engine {

SoundManager* SoundManager::m_instance{ nullptr };


SoundManager::SoundManager() {
	constexpr int32_t frequency{ 22050 };
	constexpr int32_t channels{ 2 };
	constexpr int32_t chunkSize{ 4096 };
	Mix_OpenAudio(frequency, AUDIO_S16, channels, chunkSize);
	Mix_VolumeMusic(m_volumeMusic);
}


SoundManager::~SoundManager() {
	Clean();

	Mix_CloseAudio();
}


SoundManager* SoundManager::Instance() {
	if(!m_instance) {
		m_instance = new SoundManager();
	}
	return m_instance;
}


bool SoundManager::Load(const std::string &filename,
						const std::string &id,
						SoundType type) {
	switch(type) {
		case SoundType::Sfx:
			return LoadSoundFile(filename, id);
		case SoundType::Music:
			return LoadMusicFile(filename, id);
	}

	return false;
}


void SoundManager::PlaySound(const std::string& id, int32_t loop) {
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}


void SoundManager::PlayMusic(const std::string& id, int32_t loop) {
	Mix_PlayMusic(m_music[id], loop);
}


void SoundManager::Clean() {
	for(auto& music : m_music) {
		Mix_FreeMusic(music.second);
	}
	m_music.clear();

	for(auto& sound : m_sfxs) {
		Mix_FreeChunk(sound.second);
	}
	m_sfxs.clear();
}


bool SoundManager::LoadSoundFile(const std::string& filename,
								 const std::string& id) {
	Mix_Chunk* sound{ Mix_LoadWAV(filename.c_str()) };
	if(!sound) {
		lout(LOG_TYPE::ERROR,
			 std::string{ "An error occurred while loading the sound! " } + Mix_GetError());
		return false;
	}

	m_sfxs[id] = sound;
	return true;
}


bool SoundManager::LoadMusicFile(const std::string& filename,
								 const std::string& id) {
	Mix_Music* music{ Mix_LoadMUS(filename.c_str()) };
	if(!music) {
		lout(LOG_TYPE::ERROR,
			 std::string{ "An error occurred while loading the music! " } + Mix_GetError());
		return false;
	}

	m_music[id] = music;
	return true;
}

} // namespace Engine
