//
//  RectSprite.cpp
//  GreedySnake
//
//  Created by Yiha on 16/4/15.
//
//

#include "RectSprite.h"
#include "cocos2d.h"

USING_NS_CC;

RectSprite::RectSprite()
{
    
}

RectSprite::~RectSprite()
{
    
}

void RectSprite::setRectOrderInTheSanke(uint i)
{
    this->_snakeOrder = i;
}