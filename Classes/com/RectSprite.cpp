//
//  RectSprite.cpp
//  GreedySnake
//
//  Created by Yiha on 16/4/15.
//
//
#include <iostream>

#include "RectSprite.h"
#include "cocos2d.h"
#include "Game.h"

USING_NS_CC;
using namespace std;

RectSprite::RectSprite()
{
    
}

RectSprite::~RectSprite()
{
    
}

RectSprite* RectSprite::create()
{
    RectSprite* rs = new (std::nothrow) RectSprite;
    if (rs->init())
    {
        rs->autorelease();
        return rs;
    }
    CC_SAFE_DELETE(rs);
    return nullptr;
}


RectSprite * RectSprite::create(const Color4B& color)
{
    RectSprite* rs = new (std::nothrow) RectSprite;
    if(rs && rs->initWithColor(color))
    {
        rs->autorelease();
        return rs;
    }
    CC_SAFE_DELETE(rs);
    return nullptr;
}

bool RectSprite::initWithColor(const Color4B& color)
{
    if (LayerColor::init()) {
        internalLayerColor = LayerColor::create(color);
        this->addChild(internalLayerColor);
        internalLayerColor->setPositionX(1);
        internalLayerColor->setPositionY(1);
        return true;
    }
    return false;
}

void RectSprite::setContentSize(const Size & size)
{
    LayerColor::setContentSize(size);
    if (internalLayerColor) {
        float w = float(size.width-2.0);
        float h = float(size.height-2.0);
        internalLayerColor->setContentSize(Size(w, h));
    }
}

void RectSprite::setRectOrderInTheSanke(uint i)
{
    this->_snakeOrder = i;
}

void RectSprite::setMoveDirection(string &str)
{
    this->moveDirection = str;
}

void RectSprite::move()
{
    if (this->moveDirection == Game::TOP)
    {
        this->setPositionY(this->getPositionY() + Game::SIZE);
    }
    else if (this->moveDirection == Game::DOWN)
    {
        this->setPositionY(this->getPositionY() - Game::SIZE);
    }
    else if (this->moveDirection == Game::RIGHT)
    {
        this->setPositionX(this->getPositionX() + Game::SIZE);
    }
    else if (this->moveDirection == Game::LEFT)
    {
        this->setPositionX(this->getPositionX() - Game::SIZE);
    }
}