//
//  SymbolSpriteManager.cpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/26/19.
//

#include "SymbolSpriteManager.hpp"
#include "SlotMachineScene.hpp"
#include "Symbols.hpp"
#include "Board.hpp"
#include "Utils.hpp"

#define animationTime 0.2

SymbolSpriteManager::SymbolSpriteManager(Scene *scene, Symbols *symbols, Size visibleSize, Vec2 origin) {
    this->scene = scene;
    this->symbols = symbols;
    this->visibleSize = visibleSize;
    this->origin = origin;
}

void SymbolSpriteManager::update(int wheelIdx) {
    if (spins[wheelIdx] > 0) {
        slideTo(wheelIdx,
                symbols->symbols[Utils::random(0, Symbols::NUM_SYMBOLS - 1)],
                symbols->symbols[Utils::random(0, Symbols::NUM_SYMBOLS - 1)],
                symbols->symbols[Utils::random(0, Symbols::NUM_SYMBOLS - 1)]);
    } else if (spins[wheelIdx] == 0) {
        slideTo(wheelIdx, toSymbols[wheelIdx][0], toSymbols[wheelIdx][1], toSymbols[wheelIdx][2]);
    }
    spins[wheelIdx] = spins[wheelIdx] - 1;
}

bool SymbolSpriteManager::hasSymbols() {
    return wheels[0].size() > 0;
}

// This would be better with a callback.
void SymbolSpriteManager::spinTo(int numToSpin, int wheelIdx, Symbol *top, Symbol *mid, Symbol *bot, Symbols *symbols) {
    if (wheels[wheelIdx].size() <= 0) {
        addSymbolOnScreen(wheelIdx, 0, top);
        addSymbolOnScreen(wheelIdx, 1, mid);
        addSymbolOnScreen(wheelIdx, 2, bot);
    } else {
        spins[wheelIdx] = numToSpin;
        toSymbols[wheelIdx][0] = top;
        toSymbols[wheelIdx][1] = mid;
        toSymbols[wheelIdx][2] = bot;
        update(wheelIdx);
    }
}

void SymbolSpriteManager::slideTo(int wheelIdx, Symbol *top, Symbol *mid, Symbol *bot) {
    float scaleY = ((SlotMachine *)scene)->scaleBy.y;
    Symbol *arr[3] = {top, mid, bot};
    
    if (wheels[wheelIdx].size() <= 0) {
        addSymbolOnScreen(wheelIdx, 0, top);
        addSymbolOnScreen(wheelIdx, 1, mid);
        addSymbolOnScreen(wheelIdx, 2, bot);
    } else {
        
        for (int i = (int)wheels[wheelIdx].size() - 1; i >= 0; i--) {
            Sprite *symbol = wheels[wheelIdx].at(i);
            
            // Move existing off.
            Vector<FiniteTimeAction *> actions;
            actions.pushBack(MoveBy::create(animationTime, Vec2(0, -94 * scaleY)));
            actions.pushBack(RemoveSelf::create(true));
            auto moveOff = Sequence::create(actions);
            
            symbol->runAction(moveOff);
        }
        
        wheels[wheelIdx].clear();
        
        // Create new and move on.
        for (int y = Board::height - 1; y >= 0; y--) {
            Sprite *sprite = addSymbolOffScreen(wheelIdx, y, arr[y]);
            
            Vector<FiniteTimeAction *> actions;
            actions.pushBack(MoveTo::create(animationTime, getPos(wheelIdx, y)));
            if (y == 0) {
                actions.pushBack(CallFunc::create([&, wheelIdx]()->void {
                    this->update(wheelIdx);
                }));
            }
            auto moveOn = Sequence::create(actions);
            sprite->runAction(moveOn);
            wheels[wheelIdx].push_back(sprite);
        }
    }
}

void SymbolSpriteManager::addSymbolOnScreen(int wheelIdx, int idx, Symbol *symbol) {
    Sprite *sprite = Utils::addSprite(scene, symbol->image, getPos(wheelIdx, idx));
    sprite->setLocalZOrder(3);
    sprite->setScale(((SlotMachine *)scene)->scaleBy.x, ((SlotMachine *)scene)->scaleBy.y);
    wheels[wheelIdx].push_back(sprite);
}

Sprite *SymbolSpriteManager::addSymbolOffScreen(int wheelIdx, int idx, Symbol *symbol) {
    float scaleX = ((SlotMachine *)scene)->scaleBy.x;
    float scaleY = ((SlotMachine *)scene)->scaleBy.y;
    
    Vec2 pos = getPos(wheelIdx, idx);
    pos.y += 94 * scaleY;
    
    Sprite *sprite = Utils::addSprite(scene, symbol->image, pos);
    sprite->setScale(scaleX, scaleY);
    sprite->setLocalZOrder(3);
    return sprite;
}

Vec2 SymbolSpriteManager::getPos(int wheelIdx, int idx) {
    float scaleX = ((SlotMachine *)scene)->scaleBy.x;
    float scaleY = ((SlotMachine *)scene)->scaleBy.y;
    
    float startX = visibleSize.width / 2 + origin.x - 80 * scaleX;
    float startY = visibleSize.height / 2 + origin.y + 38 * scaleY;
    int x = wheelIdx, y = idx;
    return Vec2(startX + 40 * scaleX * x, startY - 31 * scaleY * y);
}
