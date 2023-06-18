#ifndef __AUDIO_HOLDER_H_
#define __AUDIO_HOLDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <map>
#include <string>

#include "Player.h"
#include "SdlTexture.h"
#include "SdlWindow.h"

class AudioHolder {
    public:
    explicit AudioHolder();
    ~AudioHolder();
    Mix_Music* find_music(GameMode game_mode);
    std::map<AnimationName, Mix_Chunk*> find_sound_effects(EntityType entity_type);


    private:
    void create_background_music(const std::string &path);
    void create_sound_effects(const std::string &path);

    std::map<GameMode, Mix_Music *> music_holder;
    std::map<EntityType, std::map<AnimationName, Mix_Chunk*>> sound_effects_holder;
};

#endif // __AUDIO_HOLDER_H_
