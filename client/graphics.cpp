#include "graphics.h"
#include <cmath>

#define MOVE_LEFT -1
#define MOVE_RIGHT 1
#define MOVE_UP 1
#define MOVE_DOWN -1
#define STILL 0


Graphics::Graphics() : last_it(0) {}

bool Graphics::game_loop(EndingInfo* ending_info, const int &it, GraphicsEntityHolder &gr_entity_holder, Camera &camera, Queue<command_t> &queue_comandos, Queue<std::shared_ptr<GameState>> &game_states, SdlWindow &window) {
    int delta_its = it - this->last_it;

    bool player_doesnt_quit = handleEvents(gr_entity_holder, queue_comandos);
    //usleep(0.01); //si queremos emular mala comunicacion, emulo que el dibujado es ree lento
    bool continue_render = false;
    bool continue_playing = update(ending_info, gr_entity_holder, FRAME_RATE * delta_its, game_states, &continue_render);
    if (continue_render)
        render(window, gr_entity_holder, camera);

    last_it = it;
    return player_doesnt_quit && continue_playing;
}

EndingInfo Graphics::run(std::shared_ptr<GameState> gs, GameMode game_mode, Queue<command_t> &queue_comandos, Queue<std::shared_ptr<GameState>> &game_states){
    EndingInfo ending_info;
    ending_info.last_gs = NULL;
    ending_info.user_won = false;
    ending_info.game_mode = game_mode;

    try {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
            throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
        }

        int imgFlags = IMG_INIT_PNG;  // Adjust flags based on the image formats you're using
        if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
            Mix_Quit();
            SDL_Quit();
            throw std::runtime_error("Failed to initialize SDL_image: " + std::string(IMG_GetError()));
        }

        AudioHolder audio_holder;
        std::cout << "game mode is " << game_mode << std::endl;
        Mix_Music* music = audio_holder.find_music(game_mode);
        if (Mix_PlayMusic(music, -1) == -1) { //REVISAR
            // Error handling: Failed to play the music
            throw std::runtime_error("Failed to play music: " + std::string(Mix_GetError()));
        }

        SdlWindow window(WINDOW_WIDTH, WINDOW_HEIGTH);

        TexturesHolder textures_holder(window);
        GraphicsEntityHolder gr_entity_holder = GraphicsEntityHolder(gs, std::move(textures_holder), window, audio_holder);
        Camera camera(window, 1700, 400);

        time_t t1 = time(0);
        int it = 0;
        this->last_it = 0;

        bool running = true;
        while (running) {
            running = game_loop(&ending_info, it, gr_entity_holder, camera, queue_comandos, game_states, window);
            
            time_t t2 = time(0);
            int rest = FRAME_RATE - (t2-t1);
            if (rest < 0) {
                int behind = -rest; //always positive
                rest = FRAME_RATE - behind % FRAME_RATE;
                int lost = behind + rest;
                t1 += lost;
                it += floor(lost/FRAME_RATE);
            }

            usleep(rest);
            t1 += FRAME_RATE;
            it += 1;
        }

        IMG_Quit();
        SDL_Quit();

        return ending_info;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return ending_info;
}

/**
 * Va a tomar un evento de teclado, y actualizará el modelo en función de los eventos que lleguen.
 * En un juego real no se tomará de a un evento por vuelta del gameloop, sino que se deberán tomar TODOS
 * o N eventos por vuelta
 */
bool Graphics::handleEvents(GraphicsEntityHolder &gr_entity_holder, Queue<command_t> &queue_comandos) {
    SDL_Event event;
    int static moving_x = STILL;
    int static moving_y = STILL;

    bool static shooting = false;
    
    COMMANDS command;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: {
                const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
                if (keyboardState[SDL_SCANCODE_LSHIFT] || keyboardState[SDL_SCANCODE_RSHIFT]) {
                    if (keyboardState[SDL_SCANCODE_H]) {
                        std::cout << "Cheat: max health" << std::endl;
                        queue_comandos.push(command.cheatInfiniteHitpoints());
                    }
                    if (keyboardState[SDL_SCANCODE_Z]){
                        std::cout << "Cheat: spwan new zombie" << std::endl;
                        queue_comandos.push(command.cheatSpawnCommonInfected());
                    }
                    if (keyboardState[SDL_SCANCODE_C]){
                        std::cout << "Cheat: clear zone of infected" << std::endl;
                        queue_comandos.push(command.cheatKillAllInfected());
                    }
                }
                
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT: {
                        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP] && moving_x != MOVE_LEFT) {
                            moving_x = MOVE_LEFT;
                            moving_y = MOVE_UP;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        } else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN] && moving_x != MOVE_LEFT) {
                            moving_x = MOVE_LEFT;
                            moving_y = MOVE_DOWN;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        } else if (moving_x != MOVE_LEFT){
                            moving_x = MOVE_LEFT;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        }
                        break;
                    }
                    case SDLK_RIGHT: {
                        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP] && moving_x != MOVE_RIGHT) {
                            moving_x = MOVE_RIGHT;
                            moving_y = MOVE_UP;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        } else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN] && moving_x != MOVE_RIGHT) {
                            moving_x = MOVE_RIGHT;
                            moving_y = MOVE_DOWN;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        } else if (moving_x != MOVE_RIGHT){
                            moving_x = MOVE_RIGHT;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        }
                        break;
                    }
                    case SDLK_UP: {
                        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT] && moving_y != MOVE_UP) {
                            moving_x = MOVE_LEFT;
                            moving_y = MOVE_UP;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        } else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT] && moving_y != MOVE_UP) {
                            moving_x = MOVE_RIGHT;
                            moving_y = MOVE_UP;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        } else if (moving_y != MOVE_UP){
                            moving_y = MOVE_UP;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        }
                        break;
                    }
                    case SDLK_DOWN: {
                        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT] && moving_y != MOVE_DOWN) {
                            moving_x = MOVE_LEFT;
                            moving_y = MOVE_DOWN;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        } else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT] && moving_y != MOVE_DOWN) {
                            moving_x = MOVE_RIGHT;
                            moving_y = MOVE_DOWN;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        } else if (moving_y != MOVE_DOWN){
                            moving_y = MOVE_DOWN;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        }
                        break;
                    }
                    
                    case SDLK_d: case SDLK_SPACE: {
                        if (!shooting) {
                            queue_comandos.push(command.setShooting(true));
                            shooting = true;
                        }
                        break;
                    }
                        
                    case SDLK_r: {
                            queue_comandos.push(command.setReloading(true));
                        break;
                    }
                    case SDLK_ESCAPE: case SDLK_q:
                        return false; //tocaron tecla para salir, me voy
                }
            }
                break; //FIN KEY_DOWN
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT: case SDLK_RIGHT: {
                        if (moving_x != STILL) {
                            moving_x = STILL;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                            
                        }
                        break;
                    }
                    case SDLK_UP: case SDLK_DOWN: {
                        if (moving_y != STILL) {
                            moving_y = STILL;
                            queue_comandos.push(command.setDirectionOfMovement(moving_x, moving_y));
                        }
                        break;
                    }
                    case SDLK_d: case SDLK_SPACE: {
                        if (shooting) {
                            queue_comandos.push(command.setShooting(false));
                            shooting = false;
                        }
                        break;
                    }
                    case SDLK_r: {
                        queue_comandos.push(command.setReloading(false));
                        break;
                    }
                }
            }
                break; //FIN KEY_UP
        } //fin switch
    } //fin while(SDL_PollEvents)
    return true;
}

bool Graphics::update(EndingInfo* ending_info, GraphicsEntityHolder &gr_entity_holder, float dt, Queue<std::shared_ptr<GameState>> &game_states, bool* continue_render) {
    std::shared_ptr<GameState> gs = NULL;
    while (game_states.try_pop(gs));
    if (gs) {
        if (gs->lost_connection) {
            std::cout << "Conexion to server down" << std::endl;
            ending_info->user_won = false;
            ending_info->last_gs = gs;
            return false;
        }
            
        if (gs->game_over) {
            if (gs->players_won) {
                std::cout << "The game ended, we won! :D" << std::endl;
                ending_info->user_won = true;
                ending_info->last_gs = gs;
                return false;
            }
            else {
                std::cout << "The game ended, we lost D:" << std::endl;
                ending_info->user_won = false;
                ending_info->last_gs = gs;
                return false;
            }
        }
        gr_entity_holder.update(dt, gs);
        *continue_render = true;
    }
    return true;
}

void Graphics::render(SdlWindow &window, GraphicsEntityHolder &gr_entity_holder, Camera &camera) {
    SDL_Renderer* renderer = window.getRenderer();

    camera.render(gr_entity_holder);
    gr_entity_holder.render(camera.get_x_left(), camera.get_x_right());
    window.render();
    
    SDL_RenderPresent(renderer);
}
