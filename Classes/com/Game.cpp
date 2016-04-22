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
size_t Game::SIZE = 25;
size_t Game::GAP_SIZE = 1;

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
    
    Size sceneSize = Size(Game::GAP_SIZE + (Game::width*Game::SIZE), Game::GAP_SIZE + (Game::height*Game::SIZE));
    Rect s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    gameLayer = LayerColor::create(Color4B(255, 255, 255, 255));
    gameLayer->setContentSize(sceneSize);
    cout << gameLayer->getContentSize().width << endl;
    gameLayer->setPosition(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
    this->addChild(gameLayer);
    
    //Layer和Sprite有不同，layer要设置锚点，必须先：ignoreAnchorPointForPosition(false);
    gameLayer->ignoreAnchorPointForPosition(false); 
    
    this->addRectToGame(this->rect(Vec2(Game::SIZE, 0)));
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

void Game::addRectToGame(RectSprite *rectSprite)
{
    rectArr.pushBack(rectSprite);
    gameLayer->addChild(rectSprite);
}

RectSprite* Game::rect(const cocos2d::Vec2 &position)
{
    RectSprite* rect = RectSprite::create(Color4B(0,0,0,255));
    rect->setContentSize(Size(Game::SIZE, Game::SIZE));
    rect->setPosition(position);
    return rect;
}

void Game::move(float dt)
{
//    codeLayer->runAction( Sequence::create(MoveBy::create(0, Vec2(this->size+this->gapSize,0)),nullptr,nullptr));
    if (this->moveOver()) {
        unschedule(CC_SCHEDULE_SELECTOR(Game::move));
        return;
    }
    for (RectSprite* rs : rectArr) {
        rs->move();
    }
}

bool Game::moveOver()
{
    
    RectSprite* r = rectArr.at(0);
    float gW = gameLayer->getContentSize().width;
    float gH = gameLayer->getContentSize().height;
    
    
    if (this->moverDirection == Game::TOP) {
        float rY = r->getPositionY() + Game::SIZE*2;
        if ( rY > gH ) {
            return true;
        }
    }
    else if (this->moverDirection == Game::DOWN) {
        float rY = r->getPositionY() - Game::SIZE;
        if ( rY < 0 ) {
            return true;
        }
    }
    else if (this->moverDirection == Game::RIGHT) {
        float rX = r->getPositionX() + Game::SIZE*2;
        if ( rX > gW ) {
            return true;
        }
    }
    else if (this->moverDirection == Game::LEFT) {
        float rX = r->getPositionX() - Game::SIZE;
        if ( rX < 0 ) {
            return true;
        }
    }
    setRectMoveDirection(this->moverDirection);
    return false;
}

bool Game::onTouchBegan(Touch *touch, Event *event)
{
    recordTouchBeganLocation = touch->getLocation();
    cout << "began" << endl;
    return true;
}

void Game::onTouchEnded(Touch *touch, Event *event)
{
    if(fabs(recordTouchBeganLocation.x-touch->getLocation().x) > fabs(recordTouchBeganLocation.y - touch->getLocation().y))
    {
        int touchMoveX = recordTouchBeganLocation.x-touch->getLocation().x;
        if ( touchMoveX > 0 && this->moverDirection != Game::RIGHT) {
            this->moverDirection = Game::LEFT;
        }
        if ( touchMoveX < 0 && this->moverDirection != Game::LEFT) {
            this->moverDirection = Game::RIGHT;
        }
    }
    else
    {
        int touchMoveY = recordTouchBeganLocation.y-touch->getLocation().y;
        if ( touchMoveY > 0 && this->moverDirection != Game::TOP) {
            this->moverDirection = Game::DOWN;
        }
        if ( touchMoveY < 0 && this->moverDirection != Game::DOWN) {
            this->moverDirection = Game::TOP;
        }
    }
    cout << touch->getLocation().x << endl;
    cout << "ended" << endl;
}

void Game::onTouchMoved(Touch* touch, Event *event)
{
    
//    cout << touch->getLocation().x << endl;
//    this->moverDirection = Game::TOP;
}

void Game::setRectMoveDirection(string &str)
{
    for (int i=(rectArr.size()-1); i>0; i--) {
        string mstr = rectArr.at(i-1)->getMoveDirection();
        rectArr.at(i)->setMoveDirection(mstr);
    }
    rectArr.at(0)->setMoveDirection(str);
}
