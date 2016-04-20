//
//  RectSprite.h
//  GreedySnake
//
//  Created by Yiha on 16/4/15.
//
//

#ifndef RectSprite_h
#define RectSprite_h

#include <stdio.h>

#include "cocos2d.h"

USING_NS_CC;

class RectSprite : public LayerColor
{
public:
    RectSprite();
    ~RectSprite();
    uint getRectOrderInTheSanke(){return _snakeOrder;};
    void setRectOrderInTheSanke(uint i);
    
private:
    uint _snakeOrder = -1;
    
};

#endif /* RectSprite_h */
