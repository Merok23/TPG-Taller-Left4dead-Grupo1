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
    for (const auto& pair : entities) { //loopeo mis entidades
        uint32_t id = pair.second->getId();
        auto it_entity = gs->entities.find(id); //busco al elemento en el mapa de entities de gs
        if (it_entity != gs->entities.end()) { //lo encontre, lo tengo que actualizar
            pair.second->update(dt, it_entity->second);
            gs->entities.erase(id); //saco el elemento de gs->entities
        } else { //no esta el elemento en gs->entities, no tiene data nueva
            pair.second->update(dt, NULL); //actualizo igual los grame
        }
    }
    //cuando termine de revisar y actualizar todos los mios, puede ser que me hayan quedado elementos en 
    //gs->entities sin matchear (porque son entities nuevas)
    //si gs->entities esta vacio, todo lo que me mandaron era para actualizar y ya saque todo del hash.
    //si gs->entities no esta vacio, es porque habia elementos que no matchearon con ningun id de mi hash de entities --> son nuevos --> hay que crearlos

    //la condicion de este for me deberia kickear al toque si no hay elementos restantes
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