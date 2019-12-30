//
//  Utils.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>

USING_NS_CC;


class Utils {
public:
    static void problemLoading(std::string& filename);
    static int random(int low, int high);
    static void setRandom();
    
    static Sprite *addSprite(Scene *scene, std::string filename, Vec2 pos);
};

#endif /* Utils_hpp */
