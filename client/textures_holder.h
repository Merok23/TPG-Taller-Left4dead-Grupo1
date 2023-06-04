#ifndef __TEXTURES_HOLDER_H_
#define __TEXTURES_HOLDER_H_

#include <SDL2/SDL.h>
#include <map>

#include "Player.h"
#include "SdlTexture.h"
#include "SdlWindow.h"

enum EntityType {
    SOLDIER_IDF,
    SOLDIER_P90,
    SOLDIER_SCOUT
};

class TexturesHolder {
    public:
    TexturesHolder(SdlWindow &window);
    std::map<AnimationName, std::shared_ptr<SdlTexture>> find_textures(EntityType entity_type);

    private:
    std::map<EntityType, std::map<AnimationName, std::shared_ptr<SdlTexture>>> textures_holder;
};

#endif // __TEXTURES_HOLDER_H_
