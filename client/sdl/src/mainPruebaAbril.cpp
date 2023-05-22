#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <unistd.h>

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Animation.h"
#include "Player.h"

static bool handleEvents(Player &player);
static void render(SdlWindow &window, Player &player, SdlTexture &im, Area &srcArea, Area &destArea);
static void update(Player &player, float dt);

int main(int argc, char** argv){
    try {

        SdlWindow window(1920, 1080); //creo la ventana

        SdlTexture s1_idle("assets/Soldier_1/Idle.png", //path de la imagen
                    window,  //donde lo meto
                    Color{0x11, 0x11, 0x11}); //no se que es esto

        SdlTexture s1_run("assets/Soldier_1/Run.png", //path de la imagen
                    window,  //donde lo meto
                    Color{0x11, 0x11, 0x11}); //no se que es esto
        
        SdlTexture s1_shot1("assets/Soldier_1/Shot_1.png", //path de la imagen
                    window,  //donde lo meto
                    Color{0x11, 0x11, 0x11}); //no se que es esto
        
        SdlTexture im("assets/backgrounds/War1/Bright/War.png", window);
        Area srcArea(0, 0, 1980, 1080);
        Area destArea(0, 0, 1800, 1000);

        Player player_1(s1_idle, s1_run, s1_shot1);

        //Gameloop - handle event, update game, render new screen
        bool running = true;
        while (running) {
            running = handleEvents(player_1);
            update(player_1, FRAME_RATE);
            render(window, player_1, im, srcArea, destArea);

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

static void render(SdlWindow &window, Player &player, SdlTexture &im, Area &srcArea, Area &destArea) {
    window.fill(); //lleno con el background gris
    im.render(srcArea, destArea, SDL_FLIP_NONE);
    player.render(); //le delego al player la responsabilidad de saber renderizarse
    window.render();
}

static void update(Player &player, float dt) {
    player.update(dt);
}