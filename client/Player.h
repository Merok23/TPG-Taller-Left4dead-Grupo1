#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "graphics_entity.h"

#include <yaml-cpp/yaml.h>
#define DEFAULT_PATH_FROM_EXECUTABLE_TO_CONFIG "../../client/client_config.yaml"

#define X_PLAYER_DATA 50
#define HEART_SIZE 35
#define BAR_SIZE 30

class Player : public GraphicsEntity{
public:
    Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, const SdlWindow &window, 
            uint32_t id, int32_t x_position, int32_t y_position, int width, int height,
            int32_t hit_points, int32_t ammo, uint8_t lives, 
            std::map<AnimationName, Mix_Chunk*>& sound_effects, 
            int y_player_data, int available_audio_channel);
    ~Player();
    VisualBar &get_ammo();
    VisualBar &get_health_bar();

    void update(float dt, Entity* entity) override;
    void render() override;

    bool is_dead();

private:
    VisualBar health_bar;
    VisualBar ammo;
    uint8_t lives;
    std::unique_ptr<Animation> life_an;

    YAML::Node config;

    std::map<AnimationName, Mix_Chunk*>& sound_effects;
    int y_player_data;
    int available_audio_channel;
};

#endif // __PLAYER_H__
