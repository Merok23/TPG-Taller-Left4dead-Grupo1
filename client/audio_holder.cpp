#include "audio_holder.h"

#include <iostream>

AudioHolder::AudioHolder() {
    if (Mix_Init(MIX_INIT_OGG) != (MIX_INIT_OGG)) {
        throw std::runtime_error("Failed to initialize SDL_mixer: " + std::string(Mix_GetError()));
    }

    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        // Error handling: Failed to initialize SDL_mixer
        Mix_Quit();
        throw std::runtime_error("Failed to open audio in SDL_mixer: " + std::string(Mix_GetError()));
    }

    const char* envVar = std::getenv("LEFT4DEAD_CLIENT_CONFIG_FILE");
    std::string configFile;
    if (!envVar) {
        std::cout << "Environment variable LEFT4DEAD_CLIENT_CONFIG_FILE not set. Using default value" << std::endl;
        configFile = DEFAULT_PATH_FROM_EXECUTABLE_TO_CONFIG;
    } else {
        std::cout << "Environment variable LEFT4DEAD_CLIENT_CONFIG_FILE set. Using it" << std::endl;
        configFile = envVar;
    }

    this->config = YAML::LoadFile(configFile);

    create_background_music(config["music_path"].as<std::string>());
    create_sound_effects(config["sound_effects_path"].as<std::string>());
    Mix_VolumeMusic(config["volumne_music"].as<int>());
}


void AudioHolder::create_sound_effects(const std::string &path) {
    std::string track("normal_shot.wav");
    sound_effects_holder[SOLDIER_IDF][AN_SHOOT] = Mix_LoadWAV((path + track).c_str());

    track.replace(0, track.length(), "rifle_shot.wav");
    sound_effects_holder[SOLDIER_SCOUT][AN_SHOOT] = Mix_LoadWAV((path + track).c_str());
    
    //sound_effects_holder[SOLDIER_IDF][AN_EXPLOSION] = Mix_LoadWAV("../../assets/Audio/SoundEffects/fast_shot.wav");
    //sound_effects_holder[SOLDIER_IDF][AN_SMOKE] = Mix_LoadWAV("../../assets/Audio/SoundEffects/fast_shot.wav");
}
/*
    Creadits for the background music:
    https://www.youtube.com/channel/UCxmng6_DMIayDwkiWGVzVRQ?view_as=subscriber 
    Alexandr Zhelanov https://soundcloud.com/alexandr-zhelanov 

    Szymon Matuszewski

*/
void AudioHolder::create_background_music(const std::string &path) {
    std::string track("Szymon_Matuszewski_-_Patient Zero.mp3");
    music_holder[TESTING] = Mix_LoadMUS((path + track).c_str());

    track.replace(0, track.length(), "Battle1.mp3");
    music_holder[SURVIVAL] = Mix_LoadMUS((path + track).c_str());

    track.replace(0, track.length(), "Light_battle.ogg");
    music_holder[CLEAR_THE_ZONE] = Mix_LoadMUS((path + track).c_str());
    
    if (music_holder[SURVIVAL] == nullptr || music_holder[CLEAR_THE_ZONE] == nullptr || music_holder[TESTING] == nullptr) {
        Mix_FreeMusic(music_holder[SURVIVAL]);
        Mix_FreeMusic(music_holder[CLEAR_THE_ZONE]);
        Mix_FreeMusic(music_holder[TESTING]);
        std::cout << "Hubo un fallo al cargar alguna de las pistas de audio, que deberia hacer aca?" << std::endl;
    }
}

Mix_Music* AudioHolder::find_music(GameMode game_mode) {
    return this->music_holder.find(game_mode)->second;
}

std::map<AnimationName, Mix_Chunk*>& AudioHolder::find_sound_effects(EntityType entity_type) {
    if (entity_type == SOLDIER_IDF ||
        entity_type == SOLDIER_P90)
        return this->sound_effects_holder.find(SOLDIER_IDF)->second;
    else if (entity_type == SOLDIER_SCOUT)
        return this->sound_effects_holder.find(SOLDIER_SCOUT)->second;
    else
        return this->sound_effects_holder.find(ZOMBIE)->second;
}

AudioHolder::~AudioHolder() {
    for (auto& pair : music_holder) {
        Mix_FreeMusic(pair.second);
    }
    Mix_Quit();
}