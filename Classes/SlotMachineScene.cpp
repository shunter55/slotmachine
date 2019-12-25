//
//  SlotMachineScene.cpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#include <iostream>
#include "ui/CocosGUI.h"

#include "Symbols.hpp"
#include "SlotMachineScene.hpp"
#include "Utils.hpp"
#include "Board.hpp"
#include "Lines.hpp"
#include "Line.hpp"
#include "LineValue.hpp"
#include "Properties.h"

#define WCP 0.25
#define GWCP 0.1

USING_NS_CC;

Scene* SlotMachine::createScene() {
    return SlotMachine::create();
}

static std::vector<Sprite *> drawnSprites;

Sprite *addSprite(SlotMachine *slotMachine, std::string filename, Vec2 pos) {
    Sprite *sprite = Sprite::create(filename);
    if (sprite == nullptr) {
        Utils::problemLoading(filename);
        return nullptr;
    } else {
        // position the sprite on the center of the screen
        sprite->setPosition(pos);
        
        slotMachine->addChild(sprite, 0);
        return sprite;
    }
}

Sprite *addBackground(SlotMachine *slotMachine) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    return addSprite(
        slotMachine,
        "background.png",
        Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
}

cocos2d::ui::Button *SlotMachine::addSpinButton() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto spinButton = ui::Button::create("spin_button.png");
    spinButton->setPosition(Vec2(visibleSize.width / 2 + origin.x + 85, visibleSize.height / 2 + origin.y - 74));
    spinButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                spin();
                break;
            default:
                break;
        }
    });
    
    this->addChild(spinButton);
    
    return spinButton;
}

bool SlotMachine::init() {
    if ( !Scene::init() ) {
        return false;
    }
    
    Utils::setRandom();
    
    Sprite *background = addBackground(this);

    auto spinButton = addSpinButton();
    
    if (background == nullptr || spinButton == nullptr) {
        return false;
    }

    spin();
    
    return true;
}

void SlotMachine::spin() {
    
    for (int i = 0; i < drawnSprites.size(); i++) {
        drawnSprites.at(i)->removeFromParentAndCleanup(true);
    }
    drawnSprites.clear();

    Board *board = new Board();
    board->init(WCP, GWCP, &symbols, &lines);
    
    LineValue *lineValue = board->score(&symbols, &lines);
    if (lineValue == nullptr) {
        std::cout << "Score: 0" << std::endl;
    } else {
        std::cout << "Score: " << lineValue->value << std::endl;
    }
    
    drawSymbols(board);
    drawLines(board);
    
    delete board;
}

void SlotMachine::drawSymbols(Board *board) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    for (int y = 0; y < board->height; y++) {
        for (int x = 0; x < board->width; x++) {
            float startX = visibleSize.width / 2 + origin.x - 80;
            float startY = visibleSize.height / 2 + origin.y + 38;
            Vec2 pos = Vec2(startX + 40 * x, startY - 31 * y);
            
            drawnSprites.push_back(addSprite(this, board->get(&symbols, x, y)->image, pos));
        }
    }
}

void SlotMachine::drawLines(Board *board) {
    std::vector<Line *> linesToDraw;
    
    std::vector<LineValue *> *lineValues = board->checkLines(&symbols, &lines);
    for (int i = 0; i < lineValues->size(); i++) {
        LineValue *lineValue = lineValues->at(i);
        linesToDraw.push_back(lineValue->line);
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    for (int i = 0; i < linesToDraw.size(); i++) {
        Line *line = linesToDraw.at(i);
        
        Sprite *addedSprite = addSprite(this, line->image, Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        addedSprite->setLocalZOrder(5);
        drawnSprites.push_back(addedSprite);
    }
}












