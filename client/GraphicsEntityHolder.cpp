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
    for (auto i = entities.begin(); i != entities.end();) {
        uint32_t id = i->second->getId();
        // chequeo en gs->entities si est'a el id de pair.second->getId()
        auto it_entity = entities.find(id);
        if (it_entity != entities.end()) {
            // si esta, tengo que actualizar uno de los mios. Le mando esa data para actualizar a mi pair.second->update y saco ese elemento del hash
            //i->second->update(dt, it_entity->second); //aca deberia mandar el entity
            //y saco el elemento del hash
            //i = entities.erase(i);
        } else {
            // si no esta, no tengo que actualizar uno de los mios con nueva data, solo tengo que actualizar las animations. Llamdo a update sin esa data
            //i->second->update(dt, NULL);
            //i++;
        }
        i->second->update(dt, gs);
        i++;
    }
    
    {// for (const auto& pair : entities) {
    //     uint32_t id = pair.second->getId();
    //     // chequeo en gs->entities si est'a el id de pair.second->getId()
    //     auto it = entities.find(id);
    //     if (it != entities.end()) {
    //         //lo encontre --> actualizo el elemento
    //         //pair.second->update(dt, it->second); //aca deberia mandar el entity
    //         //y saco el elemento del hash
    //         //
    //     } else {
    //         //no lo encontre, le paso un null porque solo necesito actualizar los frames
    //         //pair.second->update(dt, NULL);
    //     }
    //     // si esta, tengo que actualizar uno de los mios. Le mando esa data para actualizar a mi pair.second->update y saco ese elemento del hash
    //     // si no esta, no tengo que actualizar uno de los mios con nueva data, solo tengo que actualizar las animations. Llamdo a update sin esa data
    //     pair.second->update(dt, gs);
    // }
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