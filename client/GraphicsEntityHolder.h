#ifndef __GRAPHICSENTITYHOLDER_H__
#define __GRAPHICSENTITYHOLDER_H__

#include <memory>
#include <map>
#include "SdlTexture.h"
#include "Player.h"
#include "game_state.h"

class GraphicsEntityHolder {
public:
    GraphicsEntityHolder(GameState *gs, std::map<AnimationName, std::shared_ptr<SdlTexture>> textures);
    ~GraphicsEntityHolder();

    std::shared_ptr<Player> getMainPlayer();

    void update(float& dt, GameState *gs);
    void render();
    

private:
    std::map<uint32_t, std::shared_ptr<Player>> entities;
    std::shared_ptr<Player> MainPlayer;
};

#endif // __GRAPHICSENTITYHOLDER_H__