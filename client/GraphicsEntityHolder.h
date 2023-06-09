#ifndef __GRAPHICSENTITYHOLDER_H__
#define __GRAPHICSENTITYHOLDER_H__

#include <memory>
#include <map>
#include <vector>
#include "SdlWindow.h"
#include "Player.h"
#include "game_state.h"
#include "textures_holder.h"
#include "audio_holder.h"

#define Y_PLAYER_NEEDED 150

class GraphicsEntityHolder {
public:
    GraphicsEntityHolder(std::shared_ptr<GameState> gs, TexturesHolder textures_holder, SdlWindow &window, AudioHolder& audio_holder);
    //GraphicsEntityHolder(std::shared_ptr<GameState> gs, TexturesHolder textures_holder, SdlWindow &window);
    
    ~GraphicsEntityHolder();

    std::shared_ptr<Player> getMainPlayer();
    void get_new_coordenates_center(int *x, int *y);
    void update_x(int32_t delta_x, int32_t delta_y); 

    void update(float& dt, std::shared_ptr<GameState> gs);
    void render(int x_left, int x_right);
    

private:
    void add_player(Entity* entity);
    std::shared_ptr<Player> createSoldier(Entity* entity, EntityType type, AudioHolder& audio_holder);
    std::shared_ptr<GraphicsEntity> createInfected(Entity* entity, EntityType type);

    
    
    SdlWindow &window;
    TexturesHolder textures_holder;
    AudioHolder& audio_holder;
    std::map<uint32_t, std::shared_ptr<GraphicsEntity>> entities;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Player> MainPlayer;

    int y_player_data;
    int available_audio_channel;
};

#endif // __GRAPHICSENTITYHOLDER_H__