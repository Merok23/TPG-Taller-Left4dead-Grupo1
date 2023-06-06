#ifndef __TEXTURES_HOLDER_H_
#define __TEXTURES_HOLDER_H_

#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "Player.h"
#include "SdlTexture.h"
#include "SdlWindow.h"

enum EntityType {
    SOLDIER_IDF,
    SOLDIER_P90,
    SOLDIER_SCOUT,

    JUMPER,
    VENOM,
    SPEAR,
    WITCH,
    ZOMBIE
};

class TexturesHolder {
    public:
    TexturesHolder(SdlWindow &window);
    std::map<AnimationName, std::shared_ptr<SdlTexture>> find_textures(EntityType entity_type);

    private:
    void create_soldier(EntityType entity_type, std::string path);
    void create_infected(EntityType entity_type, std::string path);

    void create_zombie(std::string path);
    void create_venom(std::string path);
    void create_jumper(std::string path);
    void create_witch(std::string path);
    void create_spear(std::string path);

    SdlWindow &window;
    std::map<EntityType, std::map<AnimationName, std::shared_ptr<SdlTexture>>> textures_holder;
};

#endif // __TEXTURES_HOLDER_H_