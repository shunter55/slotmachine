//
//  Utils.hpp
//  slotmachine-mobile
//
//  Created by Stephen Kobata on 12/23/19.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>

class Utils {
public:
    static void problemLoading(std::string& filename);
    static int random(int low, int high);
    static void setRandom();
};

#endif /* Utils_hpp */
