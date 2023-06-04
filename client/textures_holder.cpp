#include "textures_holder.h"


void TexturesHolder::create_soldier(EntityType entity_type, std::string path) {
    std::string img("Idle.png");
    textures_holder[entity_type][AN_IDLE] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Shoot_1.png");
    textures_holder[entity_type][AN_SHOOT] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Walk.png");
    textures_holder[entity_type][AN_WALK] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Run.png");
    textures_holder[entity_type][AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Dead.png");
    textures_holder[entity_type][AN_DIE] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Hurt.png");
    textures_holder[entity_type][AN_HURT] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Recharge.png");
    textures_holder[entity_type][AN_RELOAD] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));
}

TexturesHolder::TexturesHolder(SdlWindow &window) : window(window){
    std::string path("../../assets/Soldier_IDF/");
    create_soldier(SOLDIER_IDF, path);

    path.replace(0, path.length(), "../../assets/Soldier_Scout/");
    create_soldier(SOLDIER_SCOUT, path);

    path.replace(0, path.length(), "../../assets/Soldier_P90/");
    create_soldier(SOLDIER_P90, path);
}


std::map<AnimationName, std::shared_ptr<SdlTexture>> TexturesHolder::find_textures(EntityType entity_type) {
    //buscar como asegurarme que entity_type es uno de los EntityType
    return this->textures_holder.find(entity_type)->second;
}