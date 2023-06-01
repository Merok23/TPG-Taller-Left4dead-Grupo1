#include "GraphicsEntityHolder.h"
#include <iostream>

GraphicsEntityHolder::GraphicsEntityHolder(GameState *gs, std::map<AnimationName, std::shared_ptr<SdlTexture>> textures, SdlWindow &window) :
    window(window)
{
        for (auto& pair : gs->entities) {
            if (pair.second->getType() == "player") {
                std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            std::move(textures),
                                                            window,
                                                            pair.second->getId(),
                                                            pair.second->getPositionX(),
                                                            pair.second->getPositionY(),
                                                            pair.second->getHitPoints());  
                entities[pair.second->getId()] = player;
                MainPlayer = player;
            }
        }
    }

std::shared_ptr<Player> GraphicsEntityHolder::getMainPlayer() {
    return MainPlayer;
}

void GraphicsEntityHolder::update(float& dt, GameState *gs) {
    for (const auto& pair : entities) {
        uint32_t id = pair.second->getId();
        // chequeo en gs->entities si est'a el id de pair.second->getId()
        auto it = entities.find(id);
        if (it != entities.end()) {
            //lo encontre --> actualizo el elemento
            //pair.second->update(dt, it->second); //aca deberia mandar el entity
        }
        // si esta, tengo que actualizar uno de los mios. Le mando esa data para actualizar a mi pair.second->update y saco ese elemento del hash
        // si no esta, no tengo que actualizar uno de los mios con nueva data, solo tengo que actualizar las animations. Llamdo a update sin esa data
        pair.second->update(dt, gs);
    }
    //cuando termine de revisar y actualizar todos los mios, puede ser que me hayan quedado elementos en gs->entities sin matchear (porque son entities nuevas)
    //si gs->entities esta vacio, todo lo que me mandaron era para actualizar y ya saque todo del hash.
    //si gs->entities no esta vacio, es porque habia elementos que no matchearon con ningun id de mi hash de entities --> son nuevos --> hay que crearlos

    //for (const auto& pair : gs->entities) {
        //tengo que crear la nueva entity y agregarla al mapa
        //algo como entities.add_entity(pair.second) o algo asi
    //}    
}

void GraphicsEntityHolder::render() {
    for (const auto& pair : entities)
        pair.second->render();
}

GraphicsEntityHolder::~GraphicsEntityHolder() {}