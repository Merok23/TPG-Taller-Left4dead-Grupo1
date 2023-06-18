#ifndef __TEXTURES_HOLDER_H_
#define __TEXTURES_HOLDER_H_

#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "Player.h"
#include "SdlTexture.h"
#include "SdlWindow.h"

class TexturesHolder {
    public:
    explicit TexturesHolder(SdlWindow &window);
    std::map<AnimationName, std::shared_ptr<SdlTexture>> find_textures(EntityType entity_type);

    private:
    void create_soldier(EntityType entity_type, const std::string &path);
    void create_infected(EntityType entity_type, const std::string &path);
    void create_obstacle(const std::string &path);
    void create_projectiles(const std::string &path);

    
    void create_zombie(const std::string &path);
    void create_venom(const std::string &path);
    void create_jumper(const std::string &path);
    void create_witch(const std::string &path);
    void create_spear(const std::string &path);

    SdlWindow &window;
    std::map<EntityType, std::map<AnimationName, std::shared_ptr<SdlTexture>>> textures_holder;
};

#endif // __TEXTURES_HOLDER_H_
