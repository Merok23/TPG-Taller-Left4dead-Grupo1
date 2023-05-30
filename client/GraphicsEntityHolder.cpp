#include "GraphicsEntityHolder.h"

GraphicsEntityHolder::GraphicsEntityHolder(GameState *gs, std::map<AnimationName, std::shared_ptr<SdlTexture>> textures) :
    MainPlayer(new Player(std::move(textures))) {

        if (!gs) {
            //error
        }
            
        //tengo que crear el player con las texturas que me pasaron y la data del gs
        //le delego a gs el create player?
        //o le pido que me de cada uno de los elementos y los creo yo?

        entities[0] = MainPlayer; //por ahora hardcodeo que el mainPLayer tiene id 0
        //mas adelante recibire ese par'ametro del servidor
    }

std::shared_ptr<Player> GraphicsEntityHolder::getMainPlayer() {
    return MainPlayer;
}

void GraphicsEntityHolder::update(float& dt) {
    for (const auto& pair : entities)
        pair.second->update(dt);
}

void GraphicsEntityHolder::render() {
    for (const auto& pair : entities)
        pair.second->render();
}

GraphicsEntityHolder::~GraphicsEntityHolder() {}