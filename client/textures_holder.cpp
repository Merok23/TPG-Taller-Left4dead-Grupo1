#include "textures_holder.h"


TexturesHolder::TexturesHolder(SdlWindow &window) {
    textures_holder[SOLDIER_IDF][AN_IDLE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Idle.png", window));
    textures_holder[SOLDIER_IDF][AN_SHOOT] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Shoot_1.png", window));
    textures_holder[SOLDIER_IDF][AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Run.png", window));
    textures_holder[SOLDIER_IDF][AN_DIE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Dead.png", window));
    textures_holder[SOLDIER_IDF][AN_RELOAD] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_IDF/Recharge.png", window));


    textures_holder[SOLDIER_SCOUT][AN_IDLE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_Scout/Idle.png", window));
    textures_holder[SOLDIER_SCOUT][AN_SHOOT] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_Scout/Shoot_1.png", window));
    textures_holder[SOLDIER_SCOUT][AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_Scout/Run.png", window));
    textures_holder[SOLDIER_SCOUT][AN_DIE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_Scout/Dead.png", window));
    textures_holder[SOLDIER_SCOUT][AN_RELOAD] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_Scout/Recharge.png", window));

    textures_holder[SOLDIER_P90][AN_IDLE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_P90/Idle.png", window));
    textures_holder[SOLDIER_P90][AN_SHOOT] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_P90/Shoot_1.png", window));
    textures_holder[SOLDIER_P90][AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_P90/Run.png", window));
    textures_holder[SOLDIER_P90][AN_DIE] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_P90/Dead.png", window));
    textures_holder[SOLDIER_P90][AN_RELOAD] = std::shared_ptr<SdlTexture>(new SdlTexture("../../assets/Soldier_P90/Recharge.png", window));
}


std::map<AnimationName, std::shared_ptr<SdlTexture>> TexturesHolder::find_textures(EntityType entity_type) {
    //nbuscar como asegurarme que entity_type es uno de los EntityType
    return this->textures_holder.find(entity_type)->second;
}