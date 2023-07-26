#include "visual_bar.h"
#include "Player.h"
#include "SdlTexture.h"

#include <iostream>

Player::Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, const SdlWindow &window, 
            uint32_t id, int32_t x_position, int32_t y_position, int width, int height,
            int32_t hit_points, int32_t ammo, uint8_t lives, 
            std::map<AnimationName, Mix_Chunk*>& sound_effects, 
            int y_player_data, int available_audio_channel,
            std::string name) :
    GraphicsEntity(textures, id, x_position, y_position, width, height),
    health_bar(hit_points, window, 67, 2, 7, 107, 4, 14), ammo(ammo, window, 204, 119, 34, 254, 190, 0), lives(lives),
    sound_effects(sound_effects), 
    y_player_data(y_player_data), available_audio_channel(available_audio_channel),
    name(name)
{
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

    Color color_key = {0xFF, 0xFF, 0xFF};
    std::shared_ptr<SdlTexture> tex_life = std::make_shared<SdlTexture>(config["player_hearts_texture_path"].as<std::string>(), window, color_key);
    life_an = std::unique_ptr<Animation>(new Animation(tex_life));
}

/*
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Player::update(float dt, Entity* entity) {
    GraphicsEntity::update(dt, entity);

    if (entity) {
        health_bar.update(entity->getHitPoints());
        ammo.update(entity->getAmmoLeft());
        lives = entity->getLives();
    }
}

bool Player::is_dead() {
    return (lives == 0);
}

void Player::render() {
    GraphicsEntity::render();
    for (int i = 0; i < lives; i++) {
        Area destArea(X_PLAYER_DATA + i * 25, y_player_data, 25, 25);
        life_an->render(destArea, SDL_FLIP_NONE);
    }
    health_bar.render(X_PLAYER_DATA, y_player_data + HEART_SIZE); //estas posiciones me las tendria que haber dicho el graphics_entity_holder
    ammo.render(X_PLAYER_DATA, y_player_data + HEART_SIZE + BAR_SIZE); //estas posiciones me las tendria que haber dicho el graphics_entity_holder
    //name.render()
    
    if (current_animation == AN_SHOOT) {
        Mix_PlayChannel(available_audio_channel, sound_effects[AN_SHOOT], -1);
    } else {
        Mix_HaltChannel(available_audio_channel);
    }
}

VisualBar& Player::get_ammo() {
    return this->ammo;
}
VisualBar& Player::get_health_bar() {
    return this->health_bar;
}

Player::~Player() {
}