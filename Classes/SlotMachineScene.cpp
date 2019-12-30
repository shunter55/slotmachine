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

#include "BoardTest.hpp"

#define WCP 0.25
#define GWCP 0.1

#define SCORE_DELAY 3.3
#define SCALED true
#define SHOULD_TEST true

USING_NS_CC;

Scene* SlotMachine::createScene() {
    return SlotMachine::create();
}

static std::vector<Sprite *> drawnSprites;

Sprite *createSprite(std::string filename, Vec2 pos) {
    Sprite *sprite = Sprite::create(filename);
    if (sprite == nullptr) {
        Utils::problemLoading(filename);
        return nullptr;
    } else {
        // position the sprite on the center of the screen
        sprite->setPosition(pos);
        return sprite;
    }
}

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

Sprite *SlotMachine::addBackground() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite *back = addSprite(
        this,
        "background.png",
        Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    if (SCALED) {
        scaleBy = Vec2(visibleSize.width / back->getContentSize().width, (visibleSize.height + 2) / back->getContentSize().height);
    } else {
        scaleBy = Vec2(1, 1);
    }
    back->setScale(scaleBy.x, scaleBy.y);
    
    Sprite *front = addSprite(
        this,
        "background_front.png",
        Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    front->setLocalZOrder(4);
    front->setScale(scaleBy.x, scaleBy.y);

    return back;
}

cocos2d::ui::Button *SlotMachine::addSpinButton() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto spinButton = ui::Button::create("spin_button.png");
    spinButton->setPosition(Vec2(visibleSize.width / 2 + origin.x + 85 * scaleBy.x, visibleSize.height / 2 + origin.y - 74 * scaleBy.y));
    spinButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                spin();
                break;
            default:
                break;
        }
    });
    spinButton->setScale(scaleBy.y);
    spinButton->setLocalZOrder(5);
    
    this->addChild(spinButton);
    
    return spinButton;
}

bool SlotMachine::init() {
    if (SHOULD_TEST) {
        BoardTest::test();
    }
    
    if ( !Scene::init() ) {
        return false;
    }
    
    Utils::setRandom();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->symbolManager = new SymbolSpriteManager(this, &symbols, visibleSize, origin);
    
    Sprite *background = addBackground();

    auto spinButton = addSpinButton();
    
    scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 9);
    scoreLabel->setTextColor(Color4B::BLACK);
    scoreLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x + 23 * scaleBy.x, visibleSize.height / 2 + origin.y - 73 * scaleBy.y));
    this->addChild(scoreLabel);
    scoreLabel->setLocalZOrder(6);
    
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
    
    // Update the score.
    Vector<FiniteTimeAction *> actions;
    actions.pushBack(DelayTime::create(SCORE_DELAY));
    int score;
    if (lineValue == nullptr) {
        score = 0;
    } else {
        score = lineValue->value;
    }
    actions.pushBack(CallFunc::create([&, score]()->void {
        this->updateScore(score);
    }));
    auto updateScoreAction = Sequence::create(actions);
    this->runAction(updateScoreAction);
    
    for (int x = 0; x < Board::width; x++) {
        symbolManager->spinTo(
            5 + 2 * x,
            x,
            board->get(&symbols, x, 0),
            board->get(&symbols, x, 1),
            board->get(&symbols, x, 2),
            &symbols);
    }
    
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
            
            Sprite *addedSprite = addSprite(this, board->get(&symbols, x, y)->image, pos);
            addedSprite->setLocalZOrder(3);
            
            drawnSprites.push_back(addedSprite);
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
        
        Sprite *createdSprite = addSprite(this, line->image, Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        createdSprite->setScale(scaleBy.x, scaleBy.y);
        createdSprite->setLocalZOrder(5);
        
        Vector<FiniteTimeAction *> actions;
        if (symbolManager->hasSymbols()) {
            actions.pushBack(ToggleVisibility::create());
            actions.pushBack(DelayTime::create(SCORE_DELAY));
        }
        actions.pushBack(ToggleVisibility::create());
//        if (i >= linesToDraw.size() - 1) {
//            int score = board->score(&symbols, &lines)->value;
//            actions.pushBack(CallFunc::create([&, score]()->void {
//                this->updateScore(score);
//            }));
//        }
        auto delayIn = Sequence::create(actions);
        createdSprite->runAction(delayIn);
        
        drawnSprites.push_back(createdSprite);
    }
}

void SlotMachine::updateScore(int score) {
    scoreLabel->setString(std::to_string(score));
}












