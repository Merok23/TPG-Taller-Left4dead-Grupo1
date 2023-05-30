#include "main.h"

#include "Player.h"

#define BACKGROUND_WIDTH 1920
#define BACKGROUND_HEIGTH 1080

#define CAMARA_START_X 300
#define CAMARA_WIDTH 1320 //300 pixels to the left and 300 pixels to the right start hidden
#define CAMARA_MAX_X 1920-CAMARA_WIDTH

#define SCROLL_THREASHOLD 350



static bool handleEvents(Player &player);
static void render(SdlWindow &window, Player &player, SdlTexture &im, Area &destArea);
static void update(Player &player, float dt);


int main(int argc, char** argv){
    try {

        SdlWindow window(CAMARA_WIDTH, BACKGROUND_HEIGTH-200); //creo la ventana
        SdlTexture im("assets/backgrounds/War1/Bright/War.png", window);
        Area destArea(0, 0, CAMARA_WIDTH, BACKGROUND_HEIGTH-200); //x, y, width, height



        std::map<AnimationName, SdlTexture*> textures;

        SdlTexture s1_idle("assets/Soldier_1/Idle.png", //path de la imagen
                    window  //donde lo meto
                    );
        textures[AN_IDLE] = &s1_idle;
        std::cout << "Pude agregar el s1_idle" << std::endl;

        SdlTexture s1_run("assets/Soldier_1/Run.png", //path de la imagen
                    window //donde lo meto
                    );
        textures[AN_RUN] = &s1_run;
        std::cout << "Pude agregar el s1_run" << std::endl;
        
        SdlTexture s1_shot1("assets/Soldier_1/Shot_1.png", //path de la imagen
                    window  //donde lo meto
                    );
        textures[AN_SHOOT] = &s1_shot1;
        std::cout << "Pude agregar el s1_shot1" << std::endl;
        
        SdlTexture s1_die("assets/Soldier_1/Dead.png", //path de la imagen
                    window  //donde lo meto
                    );
        textures[AN_DIE] = &s1_die;
        std::cout << "Pude agregar el s1_die" << std::endl;


        Player player_1(textures);
        std::cout << "Pude crear el jugador" << std::endl;

        //Gameloop - handle event, update game, render new screen
        bool running = true;
        while (running) {
            running = handleEvents(player_1);
            update(player_1, FRAME_RATE);
            render(window, player_1, im, destArea);

            // la cantidad de segundos que debo dormir se debe ajustar en función
            // de la cantidad de tiempo que demoró el handleEvents y el render
            usleep(FRAME_RATE);
        }

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

/**
 * Va a tomar un evento de teclado, y actualizará el modelo en función de los eventos que lleguen.
 * En un juego real no se tomará de a un evento por vuelta del gameloop, sino que se deberán tomar TODOS
 * o N eventos por vuelta
 */
static bool handleEvents(Player &player) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT: //tocaron la tecla de izquierda
                        player.moveLeft();
                        break;
                    case SDLK_RIGHT: //tocaron la tecla de derecha
                        player.moveRigth();
                        break;
                    case SDLK_UP: //tocaron la tecla de izquierda
                        player.moveUp();
                        break;
                    case SDLK_DOWN: //tocaron la tecla de derecha
                        player.moveDown();
                        break;
                    case SDLK_d: case SDLK_SPACE: //tocaron la d o la barra especiadora
                        player.shoot();
                        break;
                    case SDLK_h: //le "pegaron"
                        player.hurt();
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
                        player.stopMovingX();
                        break;
                    case SDLK_UP: case SDLK_DOWN:
                        player.stopMovingY();
                        break;
                    case SDLK_d: case SDLK_SPACE:
                        player.stopShooting();
                        break;
                }
            }
                break; //FIN KEY_UP
        } //fin switch
    } //fin while(SDL_PollEvents)
    return true;
}

static void render(SdlWindow &window, Player &player, SdlTexture &im, Area &destArea) {
    window.fill(); //lleno con el background gris
    int cameraX = CAMARA_START_X;
    if (player.getX() <= SCROLL_THREASHOLD - 100) {
        cameraX = player.getX() + ( CAMARA_WIDTH / 220);
        if (cameraX < 0)
            cameraX = 0;
    }
        
    if (player.getX() >= CAMARA_WIDTH - SCROLL_THREASHOLD) {
        cameraX = player.getX() - ( CAMARA_WIDTH / 2);
        if (cameraX > BACKGROUND_WIDTH - CAMARA_WIDTH)
            cameraX = BACKGROUND_WIDTH - CAMARA_WIDTH;
    }
    Area srcArea(cameraX, 200, CAMARA_WIDTH, BACKGROUND_HEIGTH-200);
    im.render(srcArea, destArea, SDL_FLIP_NONE);

    player.render(); //le delego al player la responsabilidad de saber renderizarse
    window.render();
}

static void update(Player &player, float dt) {
    player.update(dt);
}