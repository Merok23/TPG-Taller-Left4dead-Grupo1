#ifndef __GRAPHICSENTITYHOLDER_H__
#define __GRAPHICSENTITYHOLDER_H__

#include <memory>
#include <map>
#include "../libs/SdlTexture.h"
#include "Player.h"

class GraphicsEntityHolder {
public:
    GraphicsEntityHolder(std::map<AnimationName, SdlTexture *> textures);
    ~GraphicsEntityHolder();

    std::shared_ptr<Player> getMainPlayer();
    

private:
    std::shared_ptr<Player> MainPlayer;
};

#endif // __GRAPHICSENTITYHOLDER_H__