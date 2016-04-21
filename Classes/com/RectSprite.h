//
//  RectSprite.h
//  GreedySnake
//
//  Created by Yiha on 16/4/15.
//
//

#ifndef RectSprite_h
#define RectSprite_h
#include <iostream>

#include <stdio.h>

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class RectSprite : public LayerColor
{
public:
    RectSprite();
    ~RectSprite();
    
    static RectSprite* create();
    static RectSprite* create(const Color4B& color);
    
    void setContentSize(const Size & size);
    uint getRectOrderInTheSanke(){return _snakeOrder;};
    void setRectOrderInTheSanke(uint i);
    
    void setMoveDirection(string &str);
    string getMoveDirection(){ return moveDirection;};
    void move();
    
private:
    bool initWithColor(const Color4B& color);
    
private:
    LayerColor* internalLayerColor = nullptr;
    uint _snakeOrder = -1;
    string moveDirection = "right";
    
    
};

#endif /* RectSprite_h */
