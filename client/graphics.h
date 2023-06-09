#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


#include <iostream>
#include <exception>
#include <unistd.h>

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Animation.h"
#include <map>

#include "GraphicsEntityHolder.h"
#include "game_state.h"
#include "visual_bar.h"
#include "../common/queue.h"
#include "camera.h"
#include "client_protocol.h" //deberia estar aca la definicion de command?

#include "audio_holder.h"

typedef struct {
    std::shared_ptr<GameState> last_gs;
    bool user_won;
    GameMode game_mode;

} EndingInfo;


class Graphics {
    public:
    Graphics();
    EndingInfo run(std::shared_ptr<GameState> gs, GameMode game_mode,
            Queue<command_t> &queue_comandos, Queue<std::shared_ptr<GameState>> &game_states);

    ~Graphics();
    private:
    bool game_loop(EndingInfo* ending_info, const int &it, GraphicsEntityHolder &gr_entity_holder, Camera &camera, Queue<command_t> &queue_comandos, Queue<std::shared_ptr<GameState>> &game_states, SdlWindow &window);
    bool handleEvents(GraphicsEntityHolder &gr_entity_holder, Queue<command_t> &queue_comandos);
    bool update(EndingInfo* ending_info, GraphicsEntityHolder &gr_entity_holder, float dt, Queue<std::shared_ptr<GameState>> &game_states, bool* continue_render);
    void render(SdlWindow &window, GraphicsEntityHolder &gr_entity_holder, Camera &camera);

    int last_it;
};

#endif // __GRAPHICS_H__
