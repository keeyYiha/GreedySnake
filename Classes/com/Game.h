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
    
    
private:
    void bugMe(Node* node=nullptr);
    void move(float dt);
    LayerColor* rect(const cocos2d::Vec2 &position);
    void addRectToGame(Node *rect);
    
    bool moveOver();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
private:
    static const string TOP;
    static const string DOWN;
    static const string RIGHT;
    static const string LEFT;
    static const size_t width = 10;
    static const size_t height = 10;
    size_t size = 25;
    size_t gapSize = 1;
    size_t sp = 1;
    string moverDirection = "right";
    
    LayerColor* codeLayer = nullptr;
    LayerColor* gameLayer = nullptr;
    LayerColor* squareArr[width][height];
    Node* MainScene = nullptr;
    Vector<Node *> rectArr;
    
    
    CREATE_FUNC(Game);
};

#endif /* Game_h */
