#include "audio_holder.h"

#include <iostream>

AudioHolder::AudioHolder() {
    if (Mix_Init(MIX_INIT_OGG) != (MIX_INIT_OGG)) {
        //SDL_Quit();
        throw std::runtime_error("Failed to initialize SDL_mixer: " + std::string(Mix_GetError()));
    }

    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) < 0) { //REVISAR
        // Error handling: Failed to initialize SDL_mixer
        throw std::runtime_error("Failed to initialize SDL_mixer: " + std::string(Mix_GetError()));
    }
    std::string path("../../assets/Audio/Music");
    create_background_music(path);

    path.replace(0, path.length(), "../../assets/Audio/SoundEffects");
    create_sound_effects(path);

    Mix_VolumeMusic(MIX_MAX_VOLUME);  // Set the volume to 50% (half of the maximum)
}


void AudioHolder::create_sound_effects(const std::string &path) {
    sound_effects_holder[SOLDIER_IDF][AN_SHOOT] = Mix_LoadWAV("../../assets/Audio/SoundEffects/fast_shot.wav");
    //sound_effects_holder[SOLDIER_IDF][AN_EXPLOSION] = Mix_LoadWAV("../../assets/Audio/SoundEffects/fast_shot.wav");
    //sound_effects_holder[SOLDIER_IDF][AN_SMOKE] = Mix_LoadWAV("../../assets/Audio/SoundEffects/fast_shot.wav");
}
/*
    Creadits for the background music:
    https://www.youtube.com/channel/UCxmng6_DMIayDwkiWGVzVRQ?view_as=subscriber 
    Alexandr Zhelanov https://soundcloud.com/alexandr-zhelanov 

*/
void AudioHolder::create_background_music(const std::string &path) {
    std::string track("Battle_1.ogg");
    //music_holder[SURVIVAL] = Mix_LoadMUS(path+track);
    music_holder[SURVIVAL] = Mix_LoadMUS("../../assets/Audio/Music/Battle_1.ogg");
    music_holder[CLEAR_THE_ZONE] = Mix_LoadMUS("../../assets/Audio/Music/Raiders.ogg");
    music_holder[TESTING] = Mix_LoadMUS("../../assets/Audio/Music/Raiders.ogg");
    
    bool exit = false;
    if (music_holder[SURVIVAL] == nullptr) {
        std::cout << "Entre al primer if" << std::endl;
        Mix_FreeMusic(music_holder[SURVIVAL]);
        exit = true;
    }
    if (music_holder[CLEAR_THE_ZONE] == nullptr) {
        std::cout << "Entre al segundo if" << std::endl;
        Mix_FreeMusic(music_holder[CLEAR_THE_ZONE]);
        exit = true;
    }
    if (music_holder[TESTING] == nullptr) {
        std::cout << "Entre al tercer if" << std::endl;
        Mix_FreeMusic(music_holder[TESTING]);
        exit = true;
    }

    //si exit es true que hago?
    if (exit)
        std::cout << "Hubo un fallo al cargar alguna de las pistas de audio, que deberia hacer aca?" << std::endl;

    /*
        Para mi esta cancion pega mejor en la parte de qt
    */
    // Mix_Music* music = Mix_LoadMUS("../../assets/Audio/Music/Futuristic_ambient_1.ogg");
    // if (!music) {
    //     // Error handling: Failed to load the music
    //     throw std::runtime_error("Failed to load music: " + std::string(Mix_GetError()));
    // }
    

}

Mix_Music* AudioHolder::find_music(GameMode game_mode) {
    return this->music_holder.find(game_mode)->second;
}

std::map<AnimationName, Mix_Chunk*> AudioHolder::find_sound_effects(EntityType entity_type) {
    if (entity_type == SOLDIER_IDF ||
        entity_type == SOLDIER_P90 ||
        entity_type == SOLDIER_SCOUT)
        return this->sound_effects_holder.find(SOLDIER_IDF)->second;
    else
        return this->sound_effects_holder.find(ZOMBIE)->second;
}

AudioHolder::~AudioHolder() {
    for (auto& pair : music_holder) {
        Mix_FreeMusic(pair.second);
    }
    Mix_Quit();
}