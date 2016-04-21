//
//  Game.h
//  GreedySnake
//
//  Created by Yiha on 16/4/10.
//
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include "cocos2d.h"

#include "RectSprite.h"

using namespace std;
USING_NS_CC;

class Game : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
public:
    static const string TOP;
    static const string DOWN;
    static const string RIGHT;
    static const string LEFT;

    static size_t SIZE;
    
    
private:
    void bugMe(Node* node=nullptr);
    void move(float dt);
    RectSprite* rect(const cocos2d::Vec2 &position);
    void addRectToGame(RectSprite *rect);
    
    bool moveOver();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    
    void setRectMoveDirection(string &str);
private:
    static const size_t width = 10;
    static const size_t height = 10;
    size_t sp = 1;
    string moverDirection = "right";
    
    LayerColor* codeLayer = nullptr;
    LayerColor* gameLayer = nullptr;
    RectSprite* squareArr[width][height];
    Node* MainScene = nullptr;
    Vector<RectSprite *> rectArr;
    
    Vec2 recordTouchBeganLocation;
    
    
    CREATE_FUNC(Game);
};

#endif /* Game_h */
