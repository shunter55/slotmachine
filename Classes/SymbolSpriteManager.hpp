//
//  SymbolSpriteManager.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/26/19.
//

#ifndef SymbolSpriteManager_hpp
#define SymbolSpriteManager_hpp

#include <stdio.h>
#include "Symbols.hpp"
#include "Symbol.hpp"

USING_NS_CC;

class SymbolSpriteManager {
public:
    SymbolSpriteManager(Scene *scene, Symbols *symbols, Size visibleSize, Vec2 origin);
    void spinTo(int numToSpin, int wheelIdx, Symbol *top, Symbol *mid, Symbol *bot, Symbols *symbols);
    void update(int wheelIdx);
    void addSymbolOnScreen(int wheelIdx, int idx, Symbol *symbol);
    bool hasSymbols();
    
private:
    Scene *scene;
    Symbols *symbols;
    Size visibleSize;
    Vec2 origin;
    
    int spins[5];
    Symbol *toSymbols[5][3];
    std::vector<Sprite *> wheels[5];
    Sprite *addSymbolOffScreen(int wheelIdx, int idx, Symbol *symbol);
    void slideTo(int wheelIdx, Symbol *top, Symbol *mid, Symbol *bot);
    Vec2 getPos(int wheelIdx, int idx);
};

#endif /* SymbolSpriteManager_hpp */
