#include "GraphicsEntityHolder.h"
#include <iostream>

GraphicsEntityHolder::GraphicsEntityHolder(GameState *gs, std::map<AnimationName, std::shared_ptr<SdlTexture>> textures) {
        std::cout << "gs is " << gs << std::endl;
            
     std::cout << "Estoy en el constructor de GraphicsEntityHolder" << std::endl;
        for (auto& pair : gs->entities) {
            std::cout << "Estoy en el for de gs->entities" << std::endl;
            if (pair.second->getType() == "player") {
                std::cout << "Encontre un player en el std::map entities" << std::endl;
                std::cout << "getPositionX() = " << pair.second->getPositionX() << std::endl;
                std::cout << "getPositionY() = " << pair.second->getPositionY() << std::endl;
                std::cout << "getHitPoints() = " << pair.second->getHitPoints() << std::endl;
                std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            std::move(textures),
                                                            pair.second->getPositionX(),
                                                            pair.second->getPositionY(),
                                                            pair.second->getHitPoints());  
                entities[pair.second->getId()] = player;
                MainPlayer = player;
                std::cout << "MainPLayer vale " << MainPlayer << std::endl;
                std::cout << "player vale " << player << std::endl;
                if (entities.find(pair.second->getId()) == entities.end()) {
                    std::cout << "No esta la entity que acabo de meter D:" << std::endl;
                }
            }
        }
    }

std::shared_ptr<Player> GraphicsEntityHolder::getMainPlayer() {
    return MainPlayer;
}

void GraphicsEntityHolder::update(float& dt) {
    MainPlayer->update(dt);
    // for (const auto& pair : entities)
    //     pair.second->update(dt);
}

void GraphicsEntityHolder::render() {
    MainPlayer->render();
    // for (const auto& pair : entities)
    //     pair.second->render();
}

GraphicsEntityHolder::~GraphicsEntityHolder() {}