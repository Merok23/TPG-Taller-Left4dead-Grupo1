#ifndef __GRAPHICSENTITYHOLDER_H__
#define __GRAPHICSENTITYHOLDER_H__

#include <memory>
#include <map>
#include "SdlWindow.h"
#include "Player.h"
#include "game_state.h"
#include "textures_holder.h"

class GraphicsEntityHolder {
public:
    //GraphicsEntityHolder(GameState *gs, std::map<EntityType, std::map<AnimationName, std::shared_ptr<SdlTexture>>> textures_holder, SdlWindow &window);
    GraphicsEntityHolder(GameState *gs, TexturesHolder textures_holder, SdlWindow &window);
    ~GraphicsEntityHolder();

    std::shared_ptr<Player> getMainPlayer();

    void update(float& dt, GameState *gs);
    void render();
    

private:
    std::shared_ptr<Player> add_player(Entity *entity);
    
    SdlWindow &window;
    //std::map<EntityType, std::map<AnimationName, std::shared_ptr<SdlTexture>>> textures_holder;
    TexturesHolder textures_holder;
    std::map<uint32_t, std::shared_ptr<Player>> entities;
    std::shared_ptr<Player> MainPlayer;
};

#endif // __GRAPHICSENTITYHOLDER_H__