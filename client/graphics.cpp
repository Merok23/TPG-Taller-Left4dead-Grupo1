#include "graphics.h"
#include <cmath>

bool Graphics::game_loop(const int &it, GraphicsEntityHolder &gr_entity_holder, Camera &camera, Queue<command_t> &queue_comandos, Queue<std::shared_ptr<GameState>> &game_states, SdlWindow &window) {
    int delta_its = it - this->last_it;

    bool player_doesnt_quit = handleEvents(gr_entity_holder, queue_comandos);
    //usleep(0.01); //si queremos emular mala comunicacion, emulo que el dibujado es ree lento
    bool conection_ok = update(gr_entity_holder, FRAME_RATE * delta_its, game_states);
    render(window, gr_entity_holder, camera);

    last_it = it;
    return player_doesnt_quit && conection_ok;
}

void Graphics::run(std::shared_ptr<GameState> gs, Queue<command_t> &queue_comandos, Queue<std::shared_ptr<GameState>> &game_states){
    try {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
        }

        int imgFlags = IMG_INIT_PNG;  // Adjust flags based on the image formats you're using
        if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
            throw std::runtime_error("Failed to initialize SDL_image: " + std::string(IMG_GetError()));
        }

        SdlWindow window(WINDOW_WIDTH, WINDOW_HEIGTH);
        Camera camera(window);

        TexturesHolder textures_holder(window);
        GraphicsEntityHolder gr_entity_holder =  GraphicsEntityHolder(gs, std::move(textures_holder), window);

        time_t t1 = time(0);
        int it = 0;
        int rest = 0;
        this->last_it = 0;

        bool running = true;
        while (running) {
            running = game_loop(it, gr_entity_holder, camera, queue_comandos, game_states, window);
            
            time_t t2 = time(0);
            rest = FRAME_RATE - (t2-t1);
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
    
        // Clean up SDL_image
        IMG_Quit();

        // Clean up SDL
        SDL_Quit();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

/**
 * Va a tomar un evento de teclado, y actualizará el modelo en función de los eventos que lleguen.
 * En un juego real no se tomará de a un evento por vuelta del gameloop, sino que se deberán tomar TODOS
 * o N eventos por vuelta
 */
bool Graphics::handleEvents(GraphicsEntityHolder &gr_entity_holder, Queue<command_t> &queue_comandos) {
    SDL_Event event;
    bool static moving_left = false;
    bool static moving_right = false;
    bool static moving_up= false;
    bool static moving_down = false;
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
                        if (!moving_left){
                            queue_comandos.push(command.setDirectionOfMovement(-1, 0));
                            moving_left = true;
                        }
                        break;
                    }  
                    case SDLK_RIGHT: {
                        if (!moving_right){
                            queue_comandos.push(command.setDirectionOfMovement(1, 0));
                            moving_right = true;
                        }
                        break;
                    }
                    case SDLK_UP: {
                        if (!moving_up){
                            queue_comandos.push(command.setDirectionOfMovement(0, 1));
                            moving_up = true;
                        }
                        break;
                    }
                    case SDLK_DOWN: {
                        if (!moving_down){
                            queue_comandos.push(command.setDirectionOfMovement(0, -1));
                            moving_down = true;
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
                    case SDLK_LEFT: case SDLK_RIGHT: case SDLK_UP: case SDLK_DOWN: {
                        if (moving_right || moving_left || moving_up || moving_down) {
                            queue_comandos.push(command.setDirectionOfMovement(0, 0));

                            moving_down = moving_left = moving_right = moving_up = false;
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

bool Graphics::update(GraphicsEntityHolder &gr_entity_holder, float dt, Queue<std::shared_ptr<GameState>> &game_states) {
    std::shared_ptr<GameState> gs = NULL;
    while (game_states.try_pop(gs));
    if (gs) {
        if (gs->lost_connection) {
            std::cout << "Se perdio la conexion con el server" << std::endl;
            return false;
        }
            
        if (gs->game_over) {
            std::cout << "El juego termino, perdimos :(" << std::endl;
            return false;
        }

        if (gs->players_won) {
            std::cout << "El juego termino, ganamos! :D" << std::endl;
            return false;
        }
    }  

    gr_entity_holder.update(dt, gs);
    return true;
}

void Graphics::render(SdlWindow &window, GraphicsEntityHolder &gr_entity_holder, Camera &camera) {
    SDL_Renderer* renderer = window.getRenderer();

    camera.render(gr_entity_holder);
    gr_entity_holder.render(camera.get_x_left(), camera.get_x_right());
    window.render();
    
    SDL_RenderPresent(renderer);
}
