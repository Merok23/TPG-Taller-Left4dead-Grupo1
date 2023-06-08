#include "graphics.h"
#include <cmath>

bool Graphics::game_loop(const int &it, GraphicsEntityHolder &gr_entity_holder, Camera &camera, Queue<command_t> &queue_comandos, Queue<std::shared_ptr<GameState>> &game_states, SdlWindow &window) {
    int delta_its = it - this->last_it;

    bool running = handleEvents(gr_entity_holder, queue_comandos);
    usleep(0.01); //si queremos emular mala comunicacion, emulo que el dibujado es ree lento
    update(gr_entity_holder, FRAME_RATE * delta_its, game_states);
    render(window, gr_entity_holder, camera);

    last_it = it;
    return running;
}

void Graphics::run(std::shared_ptr<GameState> gs, Queue<command_t> &queue_comandos, Queue<std::shared_ptr<GameState>> &game_states){
    try {
        SdlWindow window(WINDOW_WIDTH, WINDOW_HEIGTH); //tamanio de la ventana correcto
        Camera camera(window);

        TexturesHolder textures_holder(window);
        GraphicsEntityHolder gr_entity_holder =  GraphicsEntityHolder(gs, std::move(textures_holder), window);

        //Gameloop - handle event, update game, render new screen

        //bool running = true;
        // while (running) {
        //     running = handleEvents(gr_entity_holder, queue_comandos);
        //     update(gr_entity_holder, FRAME_RATE, game_states);
        //     render(window, gr_entity_holder, camera);

        //     usleep(FRAME_RATE);
        // }

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
                it += floor(lost/FRAME_RATE); //int(lost // FRAME_RATE); //floor division
            }

            usleep(rest);
            t1 += FRAME_RATE;
            it += 1;
        }
        


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
    //bool static reloading = false;
    
    COMMANDS command;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT: {
                        if (!moving_left){
                            //std::string command("move -1 0");
                            queue_comandos.push(command.setDirectionOfMovement(-1, 0));
                            moving_left = true;
                        }
                        break;
                    }  
                    case SDLK_RIGHT: {
                        if (!moving_right){
                            //std::string command("move 1 0");
                            queue_comandos.push(command.setDirectionOfMovement(1, 0));
                            moving_right = true;
                        }
                        break;
                    }
                    case SDLK_UP: {
                        if (!moving_up){
                            //std::string command("move 0 -1");
                            queue_comandos.push(command.setDirectionOfMovement(0, 1));
                            moving_up = true;
                        }
                        break;
                    }
                    case SDLK_DOWN: {
                        if (!moving_down){
                            //std::string command("move 0 1");
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
                        //gr_entity_holder.getMainPlayer()->shoot();
                        
                    case SDLK_r: {
                        //if (!reloading) {
                        //    std::cout << "Recibi un reload" << std::endl;
                            queue_comandos.push(command.setReloading(true));
                        //    reloading = true;
                        //}
                        break;
                    }
                        // gr_entity_holder.getMainPlayer()->recharge();
                        // break;
                    case SDLK_h: //le "pegaron"
                        gr_entity_holder.getMainPlayer()->hurt();
                        break; 
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
                            //std::string command("move 0 0");
                            //queue_comandos.push(command);
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
                        //if (reloading) {
                            queue_comandos.push(command.setReloading(false));
                        //    reloading = false;
                        //}
                        break;
                    }
                        // gr_entity_holder.getMainPlayer()->stopShooting();
                        // break;
                }
            }
                break; //FIN KEY_UP
        } //fin switch
    } //fin while(SDL_PollEvents)
    return true;
}

void Graphics::update(GraphicsEntityHolder &gr_entity_holder, float dt, Queue<std::shared_ptr<GameState>> &game_states) {
    std::shared_ptr<GameState> gs = NULL;
    while (game_states.try_pop(gs));
    gr_entity_holder.update(dt, gs);
}

void Graphics::render(SdlWindow &window, GraphicsEntityHolder &gr_entity_holder, Camera &camera) {
    camera.render(gr_entity_holder);
    gr_entity_holder.render();
    window.render();
}
