#ifndef __GRAPHICSENTITYHOLDER_H__
#define __GRAPHICSENTITYHOLDER_H__

#include <memory>
#include <map>
#include <vector>
#include "SdlWindow.h"
#include "Player.h"
#include "game_state.h"
#include "textures_holder.h"

class GraphicsEntityHolder {
public:
    GraphicsEntityHolder(GameState *gs, TexturesHolder textures_holder, SdlWindow &window);
    ~GraphicsEntityHolder();

    std::shared_ptr<Player> getMainPlayer();
    void get_new_coordenates_center(int32_t *x, int32_t *y);
    void update_x(int32_t x); 

    void update(float& dt, GameState *gs);
    void render();
    

private:
    std::shared_ptr<Player> add_player(Entity *entity);
    
    SdlWindow &window;
    TexturesHolder textures_holder;
    std::map<uint32_t, std::shared_ptr<Player>> entities;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Player> MainPlayer;
};

#endif // __GRAPHICSENTITYHOLDER_H__