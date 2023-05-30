#ifndef __GRAPHICSENTITYHOLDER_H__
#define __GRAPHICSENTITYHOLDER_H__

#include <memory>
#include <map>
#include "SdlTexture.h"
#include "Player.h"

class GraphicsEntityHolder {
public:
    GraphicsEntityHolder(std::map<AnimationName, SdlTexture *> textures);
    ~GraphicsEntityHolder();

    std::shared_ptr<Player> getMainPlayer();

    void update(float& dt);
    void render();
    

private:
    std::map<uint32_t, std::shared_ptr<Player>> entities;
    std::shared_ptr<Player> MainPlayer;
};

#endif // __GRAPHICSENTITYHOLDER_H__