#include "graphics.h"


GraphicsEntityHolder start_main_player(GameState *gs, SdlWindow &window) {
    std::map<AnimationName, std::shared_ptr<SdlTexture>> textures;

    //vamos a tener que reemplazar el ../../ por una funcion que levante de la configuracion el path
    textures[AN_IDLE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_1/Idle.png", window));
    textures[AN_SHOOT] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_1/Shot_1.png", window));
    textures[AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_1/Run.png", window));
    textures[AN_DIE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_1/Dead.png", window));

    return GraphicsEntityHolder(gs, std::move(textures));
}

void Graphics::run(GameState *gs){
    try {
        SdlWindow window(CAMARA_WIDTH, BACKGROUND_HEIGTH-200); //creo la ventana
        SdlTexture im("../../assets/backgrounds/War1/Bright/War.png", window);
        Area destArea(0, 0, CAMARA_WIDTH, BACKGROUND_HEIGTH-200); //x, y, width, height

        GraphicsEntityHolder gr_entity_holder = start_main_player(gs, window);

        //Gameloop - handle event, update game, render new screen
        bool running = true;
        while (running) {
            running = handleEvents(gr_entity_holder);
            update(gr_entity_holder, FRAME_RATE);
            render(window, gr_entity_holder, im, destArea);

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
bool Graphics::handleEvents(GraphicsEntityHolder &gr_entity_holder) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT: //tocaron la tecla de izquierda
                        gr_entity_holder.getMainPlayer()->moveLeft();
                        break;
                    case SDLK_RIGHT: //tocaron la tecla de derecha
                        gr_entity_holder.getMainPlayer()->moveRigth();
                        break;
                    case SDLK_UP: //tocaron la tecla de izquierda
                        gr_entity_holder.getMainPlayer()->moveUp();
                        break;
                    case SDLK_DOWN: //tocaron la tecla de derecha
                        gr_entity_holder.getMainPlayer()->moveDown();
                        break;
                    case SDLK_d: case SDLK_SPACE: //tocaron la d o la barra especiadora
                        gr_entity_holder.getMainPlayer()->shoot();
                        break;
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
                    case SDLK_LEFT: case SDLK_RIGHT:
                        gr_entity_holder.getMainPlayer()->stopMovingX();
                        break;
                    case SDLK_UP: case SDLK_DOWN:
                        gr_entity_holder.getMainPlayer()->stopMovingY();
                        break;
                    case SDLK_d: case SDLK_SPACE:
                        gr_entity_holder.getMainPlayer()->stopShooting();
                        break;
                }
            }
                break; //FIN KEY_UP
        } //fin switch
    } //fin while(SDL_PollEvents)
    return true;
}

void Graphics::render(SdlWindow &window, GraphicsEntityHolder &gr_entity_holder, SdlTexture &im, Area &destArea) {
    window.fill(); //lleno con el background gris
    int cameraX = CAMARA_START_X;
    // if (gr_entity_holder.getMainPlayer()->getX() <= SCROLL_THREASHOLD - 100) {
    //     cameraX = gr_entity_holder.getMainPlayer()->getX() + ( CAMARA_WIDTH / 220);
    //     if (cameraX < 0)
    //         cameraX = 0;
    // }
        
    // if (gr_entity_holder.getMainPlayer()->getX() >= CAMARA_WIDTH - SCROLL_THREASHOLD) {
    //     cameraX = gr_entity_holder.getMainPlayer()->getX() - ( CAMARA_WIDTH / 2);
    //     if (cameraX > BACKGROUND_WIDTH - CAMARA_WIDTH)
    //         cameraX = BACKGROUND_WIDTH - CAMARA_WIDTH;
    // }
    Area srcArea(cameraX, 200, CAMARA_WIDTH, BACKGROUND_HEIGTH-200);
    im.render(srcArea, destArea, SDL_FLIP_NONE);

    gr_entity_holder.render(); //le delego al player la responsabilidad de saber renderizarse
    window.render();
}

void Graphics::update(GraphicsEntityHolder &gr_entity_holder, float dt) {
    gr_entity_holder.update(dt);
}