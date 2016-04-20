//
//  Game.cpp
//  GreedySnake
//
//  Created by Yiha on 16/4/10.
//
//

#include <iostream>

#include "Game.h"
//#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "RectSprite.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;



const string Game::TOP = "top";
const string Game::DOWN = "down";
const string Game::RIGHT = "right";
const string Game::LEFT = "left";

Scene* Game::createScene()
{
    auto scene = Scene::create();
    auto layer = Game::create();
    
    scene->addChild(layer);
    return scene;
}

bool Game::init()
{
    if (!Layer::init())
    {
        return false;
    };
    
    Size sceneSize = Size(this->gapSize + (Game::width+this->gapSize)*this->size, this->gapSize + (Game::height+this->gapSize)*this->size);
    Rect s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    gameLayer = LayerColor::create(Color4B(255, 255, 255, 255));
    gameLayer->setContentSize(sceneSize);
    cout << gameLayer->getContentSize().width << endl;
    gameLayer->setPosition(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
    this->addChild(gameLayer);
    
    gameLayer->ignoreAnchorPointForPosition(false); //Layer和Sprite有不同，layer要设置锚点，必须先：ignoreAnchorPointForPosition(false);
    
    this->addRectToGame(this->rect(Vec2(this->size+this->gapSize, 0)));
    this->addRectToGame(this->rect(Vec2(0, 0)));
    
    auto touchLayer = Layer::create();
    this->addChild(touchLayer);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, touchLayer);
    
    this->moverDirection = "right";
    schedule(CC_SCHEDULE_SELECTOR(Game::move), this->sp);
    if (squareArr[1][2] == nullptr) {
        cout << "squareArr[1][2]" << endl;
    }
    
    return true;
    
}

void Game::addRectToGame(Node *rectSprite)
{
    rectArr.pushBack(rectSprite);
    gameLayer->addChild(rectSprite);
}

LayerColor* Game::rect(const cocos2d::Vec2 &position)
{
    LayerColor* rect = RectSprite::create(Color4B(0,0,0,255));
    rect->setContentSize(Size(this->size, this->size));
    rect->setPosition(position);
    return rect;
}

void Game::move(float dt)
{
//    codeLayer->runAction( Sequence::create(MoveBy::create(0, Vec2(this->size+this->gapSize,0)),nullptr,nullptr));
    if (this->moveOver()) {
        unschedule(CC_SCHEDULE_SELECTOR(Game::move));
    }
}

bool Game::moveOver()
{
    
    Node * r = rectArr.at(0);
    float gW = gameLayer->getContentSize().width;
    float gH = gameLayer->getContentSize().height;
    
    
    if (this->moverDirection == Game::TOP) {
        float rX = r->getPositionX()+this->size*2+this->gapSize;
        if (rX>gW) {
            return true;
        }
    }
    else if (this->moverDirection == Game::DOWN) {
        float rX = r->getPositionX()+this->size*2+this->gapSize;
        if (rX>gW) {
            return true;
        }
    }
    else if (this->moverDirection == Game::RIGHT) {
        float rX = r->getPositionX()+this->size*2+this->gapSize;
        if (rX>gW) {
            return true;
        }else
        {
            for (Node*rs : rectArr) {
                rs->setPositionX(rs->getPositionX()+this->size+this->gapSize);
            }
        }
    }
    else if (this->moverDirection == Game::LEFT) {
        float rX = r->getPositionX()+this->size*2+this->gapSize;
        if (rX>gW) {
            return true;
        }
    }
    return false;
}

bool Game::onTouchBegan(Touch *touch, Event *event)
{
    cout << "began" << endl;
    return true;
}

void Game::onTouchEnded(Touch *touch, Event *event)
{
    cout << "ended" << endl;
}

void Game::onTouchMoved(Touch* touch, Event *event)
{
    
    cout << touch->getLocation().x << endl;
    this->moverDirection = Game::TOP;
}
