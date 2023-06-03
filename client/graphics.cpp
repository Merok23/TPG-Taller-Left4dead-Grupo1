#include "graphics.h"

GraphicsEntityHolder start_main_player(GameState *gs, SdlWindow &window) {


    std::map<EntityType, std::map<AnimationName, std::shared_ptr<SdlTexture>>> textures_holder;

    textures_holder[SOLDIER_IDF][AN_IDLE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Idle.png", window));
    textures_holder[SOLDIER_IDF][AN_SHOOT] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Shoot_1.png", window));
    textures_holder[SOLDIER_IDF][AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Run.png", window));
    textures_holder[SOLDIER_IDF][AN_DIE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Dead.png", window));
    textures_holder[SOLDIER_IDF][AN_RELOAD] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Recharge.png", window));

    return GraphicsEntityHolder(gs, std::move(textures_holder), window);
}
void Graphics::run(GameState *gs, Queue<std::string> &queue_comandos, Queue<GameState*> &game_states){
    try {
        SdlWindow window(CAMARA_WIDTH, BACKGROUND_HEIGTH-200); //creo la ventana
        SdlTexture im("../../assets/backgrounds/War1/Bright/War.png", window);
        Area destArea(0, 0, CAMARA_WIDTH, BACKGROUND_HEIGTH-200); //x, y, width, height

        GraphicsEntityHolder gr_entity_holder = start_main_player(gs, window);

        HealthBar hb(300, window);

        //Gameloop - handle event, update game, render new screen
        bool running = true;
        while (running) {
            running = handleEvents(gr_entity_holder, queue_comandos);
            update(gr_entity_holder, FRAME_RATE, game_states);
            render(window, gr_entity_holder, im, destArea, hb);

            // la cantidad de segundos que debo dormir se debe ajustar en función
            // de la cantidad de tiempo que demoró el handleEvents y el render
            usleep(FRAME_RATE);
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
bool Graphics::handleEvents(GraphicsEntityHolder &gr_entity_holder, Queue<std::string> &queue_comandos) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT: {
                        std::string command("move -1 0");
                        queue_comandos.push(command);
                        //gr_entity_holder.getMainPlayer2()->moveLeft();
                        break;
                    }
                        
                    case SDLK_RIGHT: {
                        std::string command("move 1 0");
                        queue_comandos.push(command);
                        //gr_entity_holder.getMainPlayer2()->moveRigth();
                        break;
                    }
                    case SDLK_UP: {
                        std::string command("move 0 -1");
                        queue_comandos.push(command);
                        //gr_entity_holder.getMainPlayer2()->moveUp();
                        break;
                    }
                    case SDLK_DOWN: {
                        std::string command("move 0 1");
                        queue_comandos.push(command);
                        //gr_entity_holder.getMainPlayer2()->moveDown();
                        break;
                    }
                    case SDLK_d: case SDLK_SPACE: //tocaron la d o la barra especiadora
                        //gr_entity_holder.getMainPlayer()->shoot();
                        break;
                    case SDLK_h: //le "pegaron"
                        //gr_entity_holder.getMainPlayer()->hurt();
                        break; 
                    case SDLK_ESCAPE: case SDLK_q:
                        return false; //tocaron tecla para salir, me voy
                }
            }
                break; //FIN KEY_DOWN
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT: case SDLK_RIGHT: {
                        std::string command("move 0 0");
                        queue_comandos.push(command);
                        break;
                    }
                    case SDLK_UP: case SDLK_DOWN: {
                        std::string command("move 0 0");
                        queue_comandos.push(command);
                        break;
                    }
                    case SDLK_d: case SDLK_SPACE:
                        //gr_entity_holder.getMainPlayer()->stopShooting();
                        break;
                }
            }
                break; //FIN KEY_UP
        } //fin switch
    } //fin while(SDL_PollEvents)
    return true;
}

void Graphics::render(SdlWindow &window, GraphicsEntityHolder &gr_entity_holder, SdlTexture &im, Area &destArea,
                HealthBar &hb) {
    window.fill(); //lleno con el background gris
    int cameraX = CAMARA_START_X;
    Area srcArea(cameraX, 200, CAMARA_WIDTH, BACKGROUND_HEIGTH-200);
    im.render(srcArea, destArea, SDL_FLIP_NONE);

    gr_entity_holder.render();
    window.render();
}

void Graphics::update(GraphicsEntityHolder &gr_entity_holder, float dt, Queue<GameState*> &game_states) {
    GameState* gs = NULL;
    int i = 0;
    while (gs == NULL && i < 20) {
        game_states.try_pop(gs);
        i++;
    }
    gr_entity_holder.update(dt, gs);
}