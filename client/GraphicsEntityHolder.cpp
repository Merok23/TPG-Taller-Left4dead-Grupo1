#include "GraphicsEntityHolder.h"

GraphicsEntityHolder::GraphicsEntityHolder(GameState *gs, std::map<AnimationName, std::shared_ptr<SdlTexture>> textures) :
    MainPlayer(new Player(std::move(textures), 360, 670, 100)) {
        // if (!gs) {
        //     //error
        // }
            
           //     if (!gs) {
    //         //error
    //     }
        
    // std::cout << "Estoy en el constructor de GraphicsEntityHolder" << std::endl;
    //     for (auto& pair : gs->entities) {
    //     std::cout << "Estoy en el for de gs->entities" << std::endl;
    //         if (pair.second->getType() == "player") {
    //             std::shared_ptr<Player> player = std::make_shared<Player>(
    //                                                         std::move(textures),
    //                                                         pair.second->getPositionX(),
    //                                                         pair.second->getPositionY(),
    //                                                         pair.second->getHitPoints()
    //                                                         );  
    //             entities[pair.second->getId()] = player;
    //             std::cout << "Acabo de ingresar un nuevo elemento a mi vector de entidades" << std::endl;
    //         }
    //     }


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