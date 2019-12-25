//
//  SlotMachineScene.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#ifndef SlotMachineScene_hpp
#define SlotMachineScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Lines.hpp"
#include "Symbols.hpp"
#include "Board.hpp"

class SlotMachine : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    Lines lines = Lines();
    Symbols symbols = Symbols();
    
    void spin();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SlotMachine);

private:
    cocos2d::ui::Button *addSpinButton();
    void drawSymbols(Board *board);
    void drawLines(Board *board);
};


#endif
