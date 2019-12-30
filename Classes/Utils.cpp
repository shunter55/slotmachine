//
//  Utils.cpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#include <iostream>
#include "Utils.hpp"
#include "ui/CocosGUI.h"
#include <ctime>

// Print useful error message instead of segfaulting when files are not there.
void Utils::problemLoading(std::string& filename) {
    std::cout << "Error while loading: " << filename << std::endl;
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void Utils::setRandom() {
    srand((unsigned)time(NULL));
}

int Utils::random(int low, int high) {
    return rand() % (high - low + 1) + low;
}

Sprite *Utils::addSprite(Scene *scene, std::string filename, Vec2 pos) {
    Sprite *sprite = Sprite::create(filename);
    if (sprite == nullptr) {
        Utils::problemLoading(filename);
        return nullptr;
    } else {
        sprite->setPosition(pos);
        
        scene->addChild(sprite, 0);
        return sprite;
    }
}
